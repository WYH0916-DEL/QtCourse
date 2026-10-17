#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>

namespace Ui {
class ReplaceDialog;
}

class MainWindow;

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(MainWindow *parent = nullptr);
    ~ReplaceDialog();

private slots:
    void onFindNext();
    void onReplace();
    void onReplaceAll();

private:
    bool findNext();

    Ui::ReplaceDialog *ui;
    MainWindow *m_main;
};

#endif // REPLACEDIALOG_H
