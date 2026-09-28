#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    // 自定义列号枚举（原有表格）
    enum FieldColNum{
        colName=0,
        colSex,
        colBirth,
        colNation,
        colScore,
        colPartyM
    };

    // 学生名单列号枚举（新表格）
    enum StudentColNum{
        colStuID=0,      // 学号
        colStuName,      // 姓名
        colStuSex,       // 性别
        colStuClass,     // 行政班级
        colStuDept,      // 院(系)/部
        colStuMajor,     // 专业
        colStuNature     // 修读性质
    };

    // 单元格类型枚举
    enum CellType{
        ctName=1000,
        ctSex,
        ctBirth,
        ctNation,
        ctScore,
        ctPartyM
    };

    // 为一行创建单元格的自定义函数（原有）
    void createItemsARow(int rowNo, QString name, QString sex,
                         QDate birth, QString nation, bool isPM, int score);

    // 状态栏籍贯标签
    QLabel *labNativePlace;

private slots:
    // 设置表头
    void on_btnSetHeader_clicked();
    // 初始化表格数据
    void on_btnIniData_clicked();
    // 当前单元格变化
    void on_tableInfo_currentCellChanged(int currentRow, int currentColumn,
                                         int previousRow, int previousColumn);
    // 插入行
    void on_btnInsertRow_clicked();
    // 添加行
    void on_btnAppendRow_clicked();
    // 删除当前行
    void on_btnDelCurRow_clicked();
    // 自动调节行高
    void on_btnAutoRowHeight_clicked();
    // 自动调节列宽
    void on_btnAutoColWidth_clicked();
    // 读取表格到文本
    void on_btnReadToEdit_clicked();
    // 表格可编辑
    void on_chkBoxTabEditable_clicked(bool checked);
    // 显示水平表头
    void on_chkBoxHeaderH_clicked(bool checked);
    // 显示垂直表头
    void on_chkBoxHeaderV_clicked(bool checked);
    // 间隔行底色
    void on_chkBoxRowColor_clicked(bool checked);
    // 单元格选择
    void on_rBtnSelectItem_clicked();
    // 行选择
    void on_rBtnSelectRow_clicked();
    // 设置学生名单（工具栏按钮）
    void on_actionSetStudentList_triggered();
    // 设置行数
    void on_btnSetRows_clicked();
};

#endif // MAINWINDOW_H
