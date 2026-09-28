#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringList>
#include <QFont>
#include <QBrush>
#include <QDate>
#include <QRandomGenerator>
#include <QIcon>

// 学生信息结构体
struct StudentInfo {
    QString id;         // 学号
    QString name;       // 姓名
    QString sex;        // 性别
    QString className;  // 行政班级
    QString dept;       // 院(系)/部
    QString major;      // 专业
    QString nature;     // 修读性质
    QString native;     // 籍贯
};

// ==== 请修改为你自己的学号 ====
const QString MY_STUDENT_ID = "2024414300116"; // 王祎豪
// ==============================

// 学生名单数据（从周一点名册获取，2024软件卓越1班）
static const StudentInfo studentList[] = {
    {"2023423330214", "梁展榕", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省广州市"},
    {"2024414290102", "陈福明", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省深圳市"},
    {"2024414290112", "黄凯",   "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省珠海市"},
    {"2024414300101", "邓凯淇", "女", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省佛山市"},
    {"2024414300102", "邓缘",   "女", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省中山市"},
    {"2024414300103", "高俊",   "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省东莞市"},
    {"2024414300104", "郭碧洳", "女", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省汕头市"},
    {"2024414300105", "黄润深", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省湛江市"},
    {"2024414300106", "柯楷烁", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省茂名市"},
    {"2024414300107", "雷语",   "女", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省肇庆市"},
    {"2024414300110", "林福佳", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省梅州市"},
    {"2024414300111", "林家威", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省揭阳市"},
    {"2024414300112", "卢欢欢", "女", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省潮州市"},
    {"2024414300113", "潘丽萍", "女", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省清远市"},
    {"2024414300116", "王祎豪", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省韶关市"},
    {"2024414300117", "王启盛", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省惠州市"},
    {"2024414300118", "王鑫宇", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省江门市"},
    {"2024414300119", "韦佳慧", "女", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省阳江市"},
    {"2024414300120", "杨晓杭", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省汕尾市"},
    {"2024414300122", "俞基杰", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省潮州市"},
    {"2024414300123", "袁光宇", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省揭阳市"},
    {"2024414300124", "曾佳宁", "女", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省梅州市"},
    {"2024414300125", "曾谞炫", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省肇庆市"},
    {"2024414300126", "张家富", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省茂名市"},
    {"2024414300128", "张旭乐", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省湛江市"},
    {"2024414300129", "赵程程", "女", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省汕头市"},
    {"2024414300130", "郑俊楠", "男", "2024软件卓越1班", "网络空间安全学院", "软件工程", "初修", "广东省东莞市"},
};
static const int studentCount = sizeof(studentList) / sizeof(studentList[0]);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 状态栏原有标签初始化（课本示例自带）
    QLabel *labCellIndex = new QLabel("当前单元格坐标：");
    labCellIndex->setObjectName("labCellIndex");
    labCellIndex->setMinimumWidth(180);
    ui->statusBar->addWidget(labCellIndex);

    QLabel *labCellType = new QLabel("当前单元格类型：0");
    labCellType->setObjectName("labCellType");
    labCellType->setMinimumWidth(180);
    ui->statusBar->addWidget(labCellType);

    QLabel *labStudID = new QLabel("学生ID: 0");
    labStudID->setObjectName("labStudID");
    labStudID->setMinimumWidth(180);
    ui->statusBar->addWidget(labStudID);

    // 新增：状态栏籍贯信息标签
    labNativePlace = new QLabel("籍贯：");
    labNativePlace->setObjectName("labNativePlace");
    labNativePlace->setMinimumWidth(200);
    ui->statusBar->addWidget(labNativePlace);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 1. 设置水平表头
void MainWindow::on_btnSetHeader_clicked()
{
    QStringList headerText;
    headerText<<"姓名"<<"性别"<<"出生日期"<<"民族"<<"分数"<<"是否党员";

    ui->tableInfo->setColumnCount(headerText.size());        // 设置表格列数

    for (int i=0; i<ui->tableInfo->columnCount(); i++)
    {
        QTableWidgetItem *headerItem= new QTableWidgetItem(headerText.at(i));
        QFont font= headerItem->font();
        font.setBold(true);         // 设置为粗体
        font.setPointSize(11);      // 字体大小
        headerItem->setForeground(QBrush(Qt::red)); // 设置文字颜色
        headerItem->setFont(font);  // 设置字体
        ui->tableInfo->setHorizontalHeaderItem(i, headerItem);
    }
}

// 2. 初始化表格数据
void MainWindow::on_btnIniData_clicked()
{
    QDate   birth(2001,4,6);
    ui->tableInfo->clearContents(); // 只清除工作区，不清除表头

    for (int i=0; i<ui->tableInfo->rowCount(); i++)
    {
        QString strName= QString("学生%1").arg(i);
        QString strSex= ((i % 2)==0)? "男":"女";
        bool isParty= ((i % 2)==0)? false:true;
        int score= QRandomGenerator::global()->bounded(60,100);

        createItemsARow(i, strName, strSex, birth,"汉族",isParty,score);
        birth=birth.addDays(20);
    }
}

// 自定义：为一行创建所有单元格
void MainWindow::createItemsARow(int rowNo, QString name, QString sex,
                                 QDate birth, QString nation, bool isPM, int score)
{
    uint studID=202105000;  // 学号基数

    // 姓名
    QTableWidgetItem *item= new QTableWidgetItem(name, MainWindow::ctName);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    studID  += rowNo;
    item->setData(Qt::UserRole,QVariant(studID));
    ui->tableInfo->setItem(rowNo,MainWindow::colName, item);

    // 性别
    QIcon   icon;
    if (sex == "男")
        icon.addFile(":/images/icons/boy.png");
    else
        icon.addFile(":/images/icons/girl.png");
    item= new QTableWidgetItem(sex,MainWindow::ctSex);
    item->setIcon(icon);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    Qt::ItemFlags flags= Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    item->setFlags(flags);
    ui->tableInfo->setItem(rowNo,MainWindow::colSex,item);

    // 出生日期
    QString str= birth.toString("yyyy-MM-dd");
    item= new QTableWidgetItem(str,MainWindow::ctBirth);
    item->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colBirth,item);

    // 民族
    item= new QTableWidgetItem(nation,MainWindow::ctNation);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colNation,item);

    // 是否党员
    item= new QTableWidgetItem("党员",MainWindow::ctPartyM);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    flags= Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    item->setFlags(flags);
    if (isPM)
        item->setCheckState(Qt::Checked);
    else
        item->setCheckState(Qt::Unchecked);
    item->setBackground(QBrush(Qt::yellow));
    ui->tableInfo->setItem(rowNo,MainWindow::colPartyM,item);

    // 分数
    str.setNum(score);
    item= new QTableWidgetItem(str,MainWindow::ctScore);
    item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableInfo->setItem(rowNo,MainWindow::colScore,item);
}

// 3. 当前单元格变化信号
void MainWindow::on_tableInfo_currentCellChanged(int currentRow, int currentColumn,
                                                int previousRow, int previousColumn)
{
    Q_UNUSED(previousRow);
    Q_UNUSED(previousColumn);

    QTableWidgetItem* item= ui->tableInfo->item(currentRow,currentColumn);
    if  (item == nullptr)
        return;

    // 状态栏显示坐标
    QLabel *labCellIndex = findChild<QLabel*>("labCellIndex");
    if (labCellIndex)
        labCellIndex->setText(QString::asprintf("当前单元格坐标：%d 行，%d 列",
                                                currentRow,currentColumn));

    // 状态栏显示单元格类型
    int cellType= item->type();
    QLabel *labCellType = findChild<QLabel*>("labCellType");
    if (labCellType)
        labCellType->setText(QString::asprintf("当前单元格类型：%d",cellType));

    // 取同行姓名列的用户数据（学号或籍贯）
    // 判断当前是哪种表格模式（通过列数判断）
    if (ui->tableInfo->columnCount() == 7) {
        // 学生名单模式：显示籍贯信息
        QTableWidgetItem *nameItem = ui->tableInfo->item(currentRow, colStuName);
        if (nameItem) {
            QString native = nameItem->data(Qt::UserRole).toString();
            labNativePlace->setText(QString("籍贯：%1").arg(native));
        }
        // 学号
        QTableWidgetItem *idItem = ui->tableInfo->item(currentRow, colStuID);
        QLabel *labStudID = findChild<QLabel*>("labStudID");
        if (labStudID && idItem)
            labStudID->setText(QString("学生ID: %1").arg(idItem->text()));
    } else {
        // 原有表格模式
        item= ui->tableInfo->item(currentRow,MainWindow::colName);
        if (item) {
            uint  ID= item->data(Qt::UserRole).toUInt();
            QLabel *labStudID = findChild<QLabel*>("labStudID");
            if (labStudID)
                labStudID->setText(QString::asprintf("学生ID: %d",ID));
        }
        labNativePlace->setText("籍贯：");
    }
}

// 4. 插入行
void MainWindow::on_btnInsertRow_clicked()
{
    int curRow= ui->tableInfo->currentRow();
    ui->tableInfo->insertRow(curRow);
    createItemsARow(curRow, "新学生", "男",
                    QDate::fromString("2002-10-1","yyyy-M-d"),"苗族",true,80);
}

// 添加行
void MainWindow::on_btnAppendRow_clicked()
{
    int curRow= ui->tableInfo->rowCount();
    ui->tableInfo->insertRow(curRow);
    createItemsARow(curRow, "新生", "女",
                    QDate::fromString("2002-6-5","yyyy-M-d"),"满族",false,76 );
}

// 删除当前行
void MainWindow::on_btnDelCurRow_clicked()
{
    int curRow= ui->tableInfo->currentRow();
    ui->tableInfo->removeRow(curRow);
}

// 自动调节行高
void MainWindow::on_btnAutoRowHeight_clicked()
{
    ui->tableInfo->resizeRowsToContents();
}

// 自动调节列宽
void MainWindow::on_btnAutoColWidth_clicked()
{
    ui->tableInfo->resizeColumnsToContents();
}

// 表格可编辑
void MainWindow::on_chkBoxTabEditable_clicked(bool checked)
{
    if (checked)
        ui->tableInfo->setEditTriggers(QAbstractItemView::DoubleClicked
                                        | QAbstractItemView::SelectedClicked);
    else
        ui->tableInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

// 显示水平表头
void MainWindow::on_chkBoxHeaderH_clicked(bool checked)
{
    ui->tableInfo->horizontalHeader()->setVisible(checked);
}

// 显示垂直表头
void MainWindow::on_chkBoxHeaderV_clicked(bool checked)
{
    ui->tableInfo->verticalHeader()->setVisible(checked);
}

// 间隔行底色
void MainWindow::on_chkBoxRowColor_clicked(bool checked)
{
    ui->tableInfo->setAlternatingRowColors(checked);
}

// 单元格选择
void MainWindow::on_rBtnSelectItem_clicked()
{
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectItems);
}

// 行选择
void MainWindow::on_rBtnSelectRow_clicked()
{
    ui->tableInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
}

// 读取表格内容到文本
void MainWindow::on_btnReadToEdit_clicked()
{
    QTableWidgetItem  *item;
    ui->textEdit->clear();

    for (int i=0; i<ui->tableInfo->rowCount(); i++)
    {
        QString str= QString::asprintf("第 %d 行： ",i+1);
        for (int j=0; j<ui->tableInfo->columnCount()-1; j++)
        {
            item= ui->tableInfo->item(i,j);
            if (item)
                str= str+item->text()+"  ";
        }
        item= ui->tableInfo->item(i, ui->tableInfo->columnCount()-1);
        if (item) {
            // 判断是否是党员列（有checkState的情况）
            if (ui->tableInfo->columnCount() == 6) {
                if (item->checkState()==Qt::Checked)
                    str= str +"党员";
                else
                    str= str +"群众";
            } else {
                str= str + item->text();
            }
        }
        ui->textEdit->appendPlainText(str);
    }
}

// 设置行数
void MainWindow::on_btnSetRows_clicked()
{
    ui->tableInfo->setRowCount(ui->spinRowCount->value());
}

// 工具栏按钮：设置学生名单
void MainWindow::on_actionSetStudentList_triggered()
{
    // 1. 设置表头
    QStringList headerText;
    headerText << "学号" << "姓名" << "性别" << "行政班级"
               << "院(系)/部" << "专业" << "修读性质";

    ui->tableInfo->setColumnCount(headerText.size());
    ui->tableInfo->setRowCount(0); // 清空所有行

    for (int i = 0; i < headerText.size(); i++)
    {
        QTableWidgetItem *headerItem = new QTableWidgetItem(headerText.at(i));
        QFont font = headerItem->font();
        font.setBold(true);
        font.setPointSize(11);
        headerItem->setForeground(QBrush(Qt::red));
        headerItem->setFont(font);
        ui->tableInfo->setHorizontalHeaderItem(i, headerItem);
    }

    // 2. 找到自己的学号在名单中的位置
    int myIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (studentList[i].id == MY_STUDENT_ID) {
            myIndex = i;
            break;
        }
    }

    if (myIndex == -1) {
        // 如果没找到，默认用中间位置
        myIndex = studentCount / 2;
    }

    // 3. 计算起始位置（前两行+自己+后两行 = 5行）
    int startIndex = myIndex - 2;
    if (startIndex < 0) startIndex = 0;
    int endIndex = startIndex + 4; // 共5行
    if (endIndex >= studentCount) {
        endIndex = studentCount - 1;
        startIndex = endIndex - 4;
        if (startIndex < 0) startIndex = 0;
    }

    // 4. 填充5行数据
    int row = 0;
    for (int i = startIndex; i <= endIndex && row < 5; i++, row++) {
        ui->tableInfo->insertRow(row);
        const StudentInfo &stu = studentList[i];
        bool isMe = (stu.id == MY_STUDENT_ID);

        // 学号
        QTableWidgetItem *item = new QTableWidgetItem(stu.id);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        if (isMe) {
            QFont font = item->font();
            font.setBold(true);
            item->setFont(font);
            item->setForeground(QBrush(Qt::red));
        }
        ui->tableInfo->setItem(row, colStuID, item);

        // 姓名（同时存储籍贯信息到UserRole）
        item = new QTableWidgetItem(stu.name);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        item->setData(Qt::UserRole, QVariant(stu.native)); // 籍贯存入UserRole
        if (isMe) {
            QFont font = item->font();
            font.setBold(true);
            item->setFont(font);
            item->setForeground(QBrush(Qt::red));
        }
        ui->tableInfo->setItem(row, colStuName, item);

        // 性别
        QIcon icon;
        if (stu.sex == "男")
            icon.addFile(":/images/icons/boy.png");
        else
            icon.addFile(":/images/icons/girl.png");
        item = new QTableWidgetItem(stu.sex);
        item->setIcon(icon);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        Qt::ItemFlags flags = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
        item->setFlags(flags);
        ui->tableInfo->setItem(row, colStuSex, item);

        // 行政班级
        item = new QTableWidgetItem(stu.className);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableInfo->setItem(row, colStuClass, item);

        // 院(系)/部
        item = new QTableWidgetItem(stu.dept);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableInfo->setItem(row, colStuDept, item);

        // 专业
        item = new QTableWidgetItem(stu.major);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableInfo->setItem(row, colStuMajor, item);

        // 修读性质
        item = new QTableWidgetItem(stu.nature);
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        ui->tableInfo->setItem(row, colStuNature, item);
    }

    // 5. 自动调节列宽
    ui->tableInfo->resizeColumnsToContents();
}
