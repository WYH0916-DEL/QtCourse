#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "codeeditor.h"
#include "aboutdialog.h"
#include "finddialog.h"
#include "replacedialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QFontDialog>
#include <QColorDialog>
#include <QInputDialog>
#include <QClipboard>
#include <QMimeData>
#include <QGuiApplication>
#include <QLabel>
#include <QSettings>
#include <QCloseEvent>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      findDlg(nullptr),
      replaceDlg(nullptr)
{
    ui->setupUi(this);
    m_editor = ui->plainTextEdit;

    // 状态栏光标位置标签
    posLabel = new QLabel(this);
    statusBar()->addPermanentWidget(posLabel);
    updateCursorPosition();

    // 初始时剪切/复制/撤销/重做不可用，粘贴是否可用取决于剪贴板
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionPaste->setEnabled(QGuiApplication::clipboard()->mimeData()->hasText());

    // Action 使能状态与编辑状态联动
    connect(m_editor, &QPlainTextEdit::copyAvailable,
            ui->actionCut, &QAction::setEnabled);
    connect(m_editor, &QPlainTextEdit::copyAvailable,
            ui->actionCopy, &QAction::setEnabled);
    connect(m_editor->document(), &QTextDocument::undoAvailable,
            ui->actionUndo, &QAction::setEnabled);
    connect(m_editor->document(), &QTextDocument::redoAvailable,
            ui->actionRedo, &QAction::setEnabled);
    connect(QGuiApplication::clipboard(), &QClipboard::dataChanged,
            this, &MainWindow::clipboardChanged);
    connect(m_editor, &QPlainTextEdit::cursorPositionChanged,
            this, &MainWindow::updateCursorPosition);
    connect(m_editor->document(), &QTextDocument::modificationChanged,
            this, &QWidget::setWindowModified);

    // 定时自动保存
    autoSaveTimer = new QTimer(this);
    autoSaveTimer->setInterval(60 * 1000);
    connect(autoSaveTimer, &QTimer::timeout, this, &MainWindow::autoSaveTick);

    loadSettings();
    setCurrentFile(QString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------------------------------------------------------------------------
// 设置
// ---------------------------------------------------------------------------

void MainWindow::loadSettings()
{
    QSettings s("DGUT", "SimpleTextEditor");

    QFont f = m_editor->font();
    if (s.contains("editor/font") && f.fromString(s.value("editor/font").toString()))
        m_editor->setFont(f);
    else
        m_editor->setFont(QFont("Consolas", 12));

    QColor fc = qvariant_cast<QColor>(s.value("editor/fontColor",
                                              m_editor->palette().color(QPalette::Text)));
    QColor bc = qvariant_cast<QColor>(s.value("editor/bgColor",
                                              m_editor->palette().color(QPalette::Base)));
    QPalette p = m_editor->palette();
    p.setColor(QPalette::Text, fc);
    p.setColor(QPalette::Base, bc);
    m_editor->setPalette(p);

    bool wrap = s.value("view/wrap", true).toBool();
    ui->actionWordWrap->setChecked(wrap);
    m_editor->setLineWrapMode(wrap ? QPlainTextEdit::WidgetWidth : QPlainTextEdit::NoWrap);

    bool line = s.value("view/lineNumber", true).toBool();
    ui->actionLineNumber->setChecked(line);
    m_editor->setLineNumberAreaVisible(line);

    bool bar = s.value("view/toolBar", true).toBool();
    ui->actionToolBar->setChecked(bar);
    ui->mainToolBar->setVisible(bar);

    bool st = s.value("view/statusBar", true).toBool();
    ui->actionStatusBar->setChecked(st);
    statusBar()->setVisible(st);

    bool as = s.value("file/autoSave", false).toBool();
    ui->actionAutoSave->setChecked(as);
    if (as)
        autoSaveTimer->start();

    restoreGeometry(s.value("window/geometry").toByteArray());
}

void MainWindow::saveSettings()
{
    QSettings s("DGUT", "SimpleTextEditor");
    s.setValue("editor/font", m_editor->font().toString());
    s.setValue("editor/fontColor", m_editor->palette().color(QPalette::Text));
    s.setValue("editor/bgColor", m_editor->palette().color(QPalette::Base));
    s.setValue("view/wrap", ui->actionWordWrap->isChecked());
    s.setValue("view/lineNumber", ui->actionLineNumber->isChecked());
    s.setValue("view/toolBar", ui->actionToolBar->isChecked());
    s.setValue("view/statusBar", ui->actionStatusBar->isChecked());
    s.setValue("file/autoSave", ui->actionAutoSave->isChecked());
    s.setValue("window/geometry", saveGeometry());
}

// ---------------------------------------------------------------------------
// 文件操作
// ---------------------------------------------------------------------------

QString MainWindow::shownName() const
{
    return curFile.isEmpty() ? tr("未命名") : QFileInfo(curFile).fileName();
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    m_editor->document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(tr("%1[*] - 简单文本编辑器").arg(shownName()));
}

bool MainWindow::maybeSave()
{
    if (!m_editor->document()->isModified())
        return true;

    const QMessageBox::StandardButton ret =
            QMessageBox::warning(this, tr("简单文本编辑器"),
                                 tr("文档 %1 已被修改，是否保存？")
                                 .arg(shownName()),
                                 QMessageBox::Save | QMessageBox::Discard
                                     | QMessageBox::Cancel,
                                 QMessageBox::Save);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void MainWindow::on_actionNew_triggered()
{
    if (maybeSave()) {
        m_editor->clear();
        setCurrentFile(QString());
    }
}

void MainWindow::on_actionOpen_triggered()
{
    if (!maybeSave())
        return;

    QString fileName = QFileDialog::getOpenFileName(
                this, tr("打开文件"), QDir::homePath(),
                tr("文本文件 (*.txt *.log *.md);;所有文件 (*)"));
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("简单文本编辑器"),
                             tr("无法打开文件 %1：\n%2")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    // 粗略检测：含 NUL 字节的文件视为非文本文件
    if (data.contains('\0')) {
        QMessageBox::warning(this, tr("简单文本编辑器"),
                             tr("文件 %1 不是有效的文本文件（可能是二进制文件）。")
                             .arg(QFileInfo(fileName).fileName()));
        return;
    }

    QTextStream in(&data);
    in.setAutoDetectUnicode(true);  // 自动识别带 BOM 的 UTF-16/32 文件
    in.setCodec("UTF-8");           // 其余情况按 UTF-8 解码

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString text = in.readAll();

    // 若出现替换字符，说明不是 UTF-8 编码，回退到系统本地编码再解一次，
    // 避免用 GBK 等本地编码保存的文件被误读成乱码
    if (text.contains(QChar(0xFFFD))) {
        QTextStream in2(&data);
        in2.setAutoDetectUnicode(true);
        text = in2.readAll();
    }

    m_editor->setPlainText(text);
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("文件已打开"), 2000);

    if (!QFileInfo(fileName).isWritable())
        statusBar()->showMessage(tr("注意：该文件为只读"), 5000);
}

bool MainWindow::save()
{
    if (curFile.isEmpty())
        return saveAs();
    return saveFile(curFile);
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(
                this, tr("另存为"), curFile.isEmpty() ? QDir::homePath() : curFile,
                tr("文本文件 (*.txt);;所有文件 (*)"));
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("简单文本编辑器"),
                             tr("无法写入文件 %1：\n%2")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }

    QTextStream out(&file);
    out.setCodec("UTF-8");

    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << m_editor->toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("文件已保存"), 2000);
    return true;
}

void MainWindow::on_actionSave_triggered()
{
    save();
}

void MainWindow::on_actionSaveAs_triggered()
{
    saveAs();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        saveSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

// ---------------------------------------------------------------------------
// 编辑操作
// ---------------------------------------------------------------------------

void MainWindow::on_actionUndo_triggered()    { m_editor->undo(); }
void MainWindow::on_actionRedo_triggered()    { m_editor->redo(); }
void MainWindow::on_actionCut_triggered()     { m_editor->cut(); }
void MainWindow::on_actionCopy_triggered()    { m_editor->copy(); }
void MainWindow::on_actionPaste_triggered()   { m_editor->paste(); }
void MainWindow::on_actionSelectAll_triggered() { m_editor->selectAll(); }

void MainWindow::clipboardChanged()
{
    ui->actionPaste->setEnabled(QGuiApplication::clipboard()->mimeData()->hasText());
}

void MainWindow::updateCursorPosition()
{
    QTextCursor c = m_editor->textCursor();
    posLabel->setText(tr("行 %1, 列 %2")
                      .arg(c.blockNumber() + 1)
                      .arg(c.columnNumber() + 1));
}

// ---------------------------------------------------------------------------
// 查找 / 替换
// ---------------------------------------------------------------------------

void MainWindow::on_actionFind_triggered()
{
    if (!findDlg)
        findDlg = new FindDialog(this);
    findDlg->show();
    findDlg->raise();
    findDlg->activateWindow();
}

void MainWindow::on_actionReplace_triggered()
{
    if (!replaceDlg)
        replaceDlg = new ReplaceDialog(this);
    replaceDlg->show();
    replaceDlg->raise();
    replaceDlg->activateWindow();
}

// ---------------------------------------------------------------------------
// 格式设置
// ---------------------------------------------------------------------------

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, m_editor->font(), this, tr("选择字体"));
    if (ok) {
        m_editor->setFont(font);
        m_editor->updateLineNumberAreaWidth(0);
        saveSettings();
    }
}

void MainWindow::on_actionFontSize_triggered()
{
    bool ok;
    int size = QInputDialog::getInt(this, tr("字体大小"), tr("字号："),
                                    m_editor->font().pointSize(), 6, 72, 1, &ok);
    if (ok) {
        QFont f = m_editor->font();
        f.setPointSize(size);
        m_editor->setFont(f);
        m_editor->updateLineNumberAreaWidth(0);
        saveSettings();
    }
}

void MainWindow::on_actionFontColor_triggered()
{
    QColor c = QColorDialog::getColor(m_editor->palette().color(QPalette::Text),
                                      this, tr("选择字体颜色"));
    if (c.isValid()) {
        QPalette p = m_editor->palette();
        p.setColor(QPalette::Text, c);
        m_editor->setPalette(p);
        saveSettings();
    }
}

void MainWindow::on_actionBgColor_triggered()
{
    QColor c = QColorDialog::getColor(m_editor->palette().color(QPalette::Base),
                                      this, tr("选择背景颜色"));
    if (c.isValid()) {
        QPalette p = m_editor->palette();
        p.setColor(QPalette::Base, c);
        m_editor->setPalette(p);
        saveSettings();
    }
}

void MainWindow::on_actionWordWrap_triggered(bool checked)
{
    m_editor->setLineWrapMode(checked ? QPlainTextEdit::WidgetWidth
                                      : QPlainTextEdit::NoWrap);
}

void MainWindow::on_actionLineNumber_triggered(bool checked)
{
    m_editor->setLineNumberAreaVisible(checked);
}

void MainWindow::on_actionAutoSave_triggered(bool checked)
{
    if (checked)
        autoSaveTimer->start();
    else
        autoSaveTimer->stop();
    statusBar()->showMessage(checked ? tr("定时自动保存已开启（60 秒）")
                                     : tr("定时自动保存已关闭"), 3000);
}

void MainWindow::autoSaveTick()
{
    if (m_editor->document()->isModified() && !curFile.isEmpty()) {
        if (saveFile(curFile))
            statusBar()->showMessage(tr("已于 %1 自动保存")
                                     .arg(QTime::currentTime().toString("HH:mm:ss")), 3000);
    }
}

// ---------------------------------------------------------------------------
// 视图 / 帮助
// ---------------------------------------------------------------------------

void MainWindow::on_actionToolBar_triggered(bool checked)
{
    ui->mainToolBar->setVisible(checked);
}

void MainWindow::on_actionStatusBar_triggered(bool checked)
{
    statusBar()->setVisible(checked);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg(this);
    dlg.exec();
}
