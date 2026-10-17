#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent),
      ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowTitle(tr("关于 简单文本编辑器"));

    connect(ui->btnOk, &QPushButton::clicked, this, &QDialog::accept);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
