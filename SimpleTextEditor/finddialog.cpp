#include "finddialog.h"
#include "ui_finddialog.h"
#include "mainwindow.h"
#include "codeeditor.h"

#include <QMessageBox>
#include <QTextDocument>

FindDialog::FindDialog(MainWindow *parent)
    : QDialog(parent),
      ui(new Ui::FindDialog),
      m_main(parent)
{
    ui->setupUi(this);
    setWindowTitle(tr("查找"));

    connect(ui->btnFindNext, &QPushButton::clicked, this, &FindDialog::onFindNext);
    connect(ui->btnClose, &QPushButton::clicked, this, &QDialog::close);

    // 打开对话框时，自动填入编辑器中已选中的文字
    QString selected = m_main->editor()->textCursor().selectedText();
    if (!selected.isEmpty())
        ui->lineEdit->setText(selected);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::onFindNext()
{
    QString str = ui->lineEdit->text();
    if (str.isEmpty()) {
        QMessageBox::information(this, tr("查找"), tr("请输入要查找的内容。"));
        return;
    }

    QTextDocument::FindFlags flags;
    if (ui->checkCase->isChecked())
        flags |= QTextDocument::FindCaseSensitively;

    bool found = m_main->editor()->find(str, flags);

    if (!found && ui->checkLoop->isChecked()) {
        // 已查到文档末尾，回到开头循环查找
        QTextCursor cursor = m_main->editor()->textCursor();
        cursor.movePosition(QTextCursor::Start);
        m_main->editor()->setTextCursor(cursor);
        found = m_main->editor()->find(str, flags);
    }

    if (!found)
        QMessageBox::information(this, tr("查找"), tr("找不到 \"%1\"。").arg(str));
}
