#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

namespace Ui {
class FindDialog;
}

class MainWindow;

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(MainWindow *parent = nullptr);
    ~FindDialog();

private slots:
    void onFindNext();

private:
    Ui::FindDialog *ui;
    MainWindow *m_main;
};

#endif // FINDDIALOG_H
