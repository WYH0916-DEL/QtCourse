#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPlainTextEdit;
class QLabel;
class FindDialog;
class ReplaceDialog;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    // 文件
    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionExit_triggered();
    // 编辑
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionSelectAll_triggered();
    // 格式
    void on_actionFont_triggered();
    void on_actionFontSize_triggered();
    void on_actionFontColor_triggered();
    void on_actionBgColor_triggered();
    void on_actionWordWrap_triggered(bool checked);
    // 搜索
    void on_actionFind_triggered();
    void on_actionReplace_triggered();
    // 视图 / 帮助
    void on_actionToolBar_triggered(bool checked);
    void on_actionStatusBar_triggered(bool checked);
    void on_actionAbout_triggered();

    void updateCursorPosition();
    void clipboardChanged();

private:
    void loadSettings();
    void saveSettings();
    bool maybeSave();
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    void loadFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString shownName() const;

    Ui::MainWindow *ui;
    QPlainTextEdit *m_editor;
    QLabel *posLabel;
    QString curFile;
    FindDialog *findDlg;
    ReplaceDialog *replaceDlg;
};

#endif // MAINWINDOW_H
