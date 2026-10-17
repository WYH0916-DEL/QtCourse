#include "replacedialog.h"
#include "ui_replacedialog.h"
#include "mainwindow.h"
#include "codeeditor.h"

#include <QMessageBox>
#include <QTextDocument>

ReplaceDialog::ReplaceDialog(MainWindow *parent)
    : QDialog(parent),
      ui(new Ui::ReplaceDialog),
      m_main(parent)
{
    ui->setupUi(this);
    setWindowTitle(tr("替换"));

    connect(ui->btnFindNext, &QPushButton::clicked, this, &ReplaceDialog::onFindNext);
    connect(ui->btnReplace, &QPushButton::clicked, this, &ReplaceDialog::onReplace);
    connect(ui->btnReplaceAll, &QPushButton::clicked, this, &ReplaceDialog::onReplaceAll);
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::close);

    QString selected = m_main->editor()->textCursor().selectedText();
    if (!selected.isEmpty())
        ui->lineEditFind->setText(selected);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

bool ReplaceDialog::findNext()
{
    QString str = ui->lineEditFind->text();
    if (str.isEmpty()) {
        QMessageBox::information(this, tr("替换"), tr("请输入要查找的内容。"));
        return false;
    }

    QTextDocument::FindFlags flags;
    if (ui->checkCase->isChecked())
        flags |= QTextDocument::FindCaseSensitively;

    bool found = m_main->editor()->find(str, flags);

    if (!found && ui->checkLoop->isChecked()) {
        QTextCursor cursor = m_main->editor()->textCursor();
        cursor.movePosition(QTextCursor::Start);
        m_main->editor()->setTextCursor(cursor);
        found = m_main->editor()->find(str, flags);
    }

    if (!found)
        QMessageBox::information(this, tr("替换"), tr("找不到 \"%1\"。").arg(str));

    return found;
}

void ReplaceDialog::onFindNext()
{
    findNext();
}

void ReplaceDialog::onReplace()
{
    QString from = ui->lineEditFind->text();
    QString to = ui->lineEditReplace->text();
    if (from.isEmpty()) {
        QMessageBox::information(this, tr("替换"), tr("请输入要查找的内容。"));
        return;
    }

    CodeEditor *ed = m_main->editor();
    QTextCursor cursor = ed->textCursor();
    Qt::CaseSensitivity cs = ui->checkCase->isChecked() ? Qt::CaseSensitive
                                                        : Qt::CaseInsensitive;

    // 当前选中的内容正好是要找的内容，先替换掉，再继续找下一个
    if (cursor.hasSelection() &&
        cursor.selectedText().compare(from, cs) == 0) {
        cursor.insertText(to);
    }

    findNext();
}

void ReplaceDialog::onReplaceAll()
{
    QString from = ui->lineEditFind->text();
    QString to = ui->lineEditReplace->text();
    if (from.isEmpty()) {
        QMessageBox::information(this, tr("替换"), tr("请输入要查找的内容。"));
        return;
    }

    QTextDocument::FindFlags flags;
    if (ui->checkCase->isChecked())
        flags |= QTextDocument::FindCaseSensitively;

    CodeEditor *ed = m_main->editor();

    QTextCursor cursor = ed->textCursor();
    cursor.movePosition(QTextCursor::Start);
    ed->setTextCursor(cursor);

    // 若替换结果中仍包含被替换的词（如把 a 替换成 aa），查找会无限进行，
    // 用文档长度作为替换次数的上限来兜底
    int count = 0;
    int limit = ed->document()->characterCount() + 1;
    while (count < limit && ed->find(from, flags)) {
        ed->textCursor().insertText(to);
        ++count;
    }

    if (count == 0)
        QMessageBox::information(this, tr("替换"), tr("找不到 \"%1\"。").arg(from));
    else
        QMessageBox::information(this, tr("替换"), tr("共完成 %1 处替换。").arg(count));
}
