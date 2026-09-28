/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSetStudentList;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *btnSetHeader;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnSetRows;
    QSpinBox *spinRowCount;
    QPushButton *btnIniData;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnInsertRow;
    QPushButton *btnAppendRow;
    QPushButton *btnDelCurRow;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnAutoRowHeight;
    QPushButton *btnAutoColWidth;
    QPushButton *btnReadToEdit;
    QHBoxLayout *horizontalLayout_5;
    QCheckBox *chkBoxTabEditable;
    QCheckBox *chkBoxRowColor;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *chkBoxHeaderV;
    QCheckBox *chkBoxHeaderH;
    QHBoxLayout *horizontalLayout_7;
    QRadioButton *rBtnSelectRow;
    QRadioButton *rBtnSelectItem;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableInfo;
    QPlainTextEdit *textEdit;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 600);
        actionSetStudentList = new QAction(MainWindow);
        actionSetStudentList->setObjectName(QString::fromUtf8("actionSetStudentList"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/student.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetStudentList->setIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMaximumSize(QSize(280, 16777215));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        btnSetHeader = new QPushButton(groupBox);
        btnSetHeader->setObjectName(QString::fromUtf8("btnSetHeader"));

        verticalLayout->addWidget(btnSetHeader);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnSetRows = new QPushButton(groupBox);
        btnSetRows->setObjectName(QString::fromUtf8("btnSetRows"));

        horizontalLayout_2->addWidget(btnSetRows);

        spinRowCount = new QSpinBox(groupBox);
        spinRowCount->setObjectName(QString::fromUtf8("spinRowCount"));
        spinRowCount->setValue(10);

        horizontalLayout_2->addWidget(spinRowCount);


        verticalLayout->addLayout(horizontalLayout_2);

        btnIniData = new QPushButton(groupBox);
        btnIniData->setObjectName(QString::fromUtf8("btnIniData"));

        verticalLayout->addWidget(btnIniData);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnInsertRow = new QPushButton(groupBox);
        btnInsertRow->setObjectName(QString::fromUtf8("btnInsertRow"));

        horizontalLayout_3->addWidget(btnInsertRow);

        btnAppendRow = new QPushButton(groupBox);
        btnAppendRow->setObjectName(QString::fromUtf8("btnAppendRow"));

        horizontalLayout_3->addWidget(btnAppendRow);


        verticalLayout->addLayout(horizontalLayout_3);

        btnDelCurRow = new QPushButton(groupBox);
        btnDelCurRow->setObjectName(QString::fromUtf8("btnDelCurRow"));

        verticalLayout->addWidget(btnDelCurRow);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btnAutoRowHeight = new QPushButton(groupBox);
        btnAutoRowHeight->setObjectName(QString::fromUtf8("btnAutoRowHeight"));

        horizontalLayout_4->addWidget(btnAutoRowHeight);

        btnAutoColWidth = new QPushButton(groupBox);
        btnAutoColWidth->setObjectName(QString::fromUtf8("btnAutoColWidth"));

        horizontalLayout_4->addWidget(btnAutoColWidth);


        verticalLayout->addLayout(horizontalLayout_4);

        btnReadToEdit = new QPushButton(groupBox);
        btnReadToEdit->setObjectName(QString::fromUtf8("btnReadToEdit"));

        verticalLayout->addWidget(btnReadToEdit);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        chkBoxTabEditable = new QCheckBox(groupBox);
        chkBoxTabEditable->setObjectName(QString::fromUtf8("chkBoxTabEditable"));
        chkBoxTabEditable->setChecked(true);

        horizontalLayout_5->addWidget(chkBoxTabEditable);

        chkBoxRowColor = new QCheckBox(groupBox);
        chkBoxRowColor->setObjectName(QString::fromUtf8("chkBoxRowColor"));
        chkBoxRowColor->setChecked(true);

        horizontalLayout_5->addWidget(chkBoxRowColor);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        chkBoxHeaderV = new QCheckBox(groupBox);
        chkBoxHeaderV->setObjectName(QString::fromUtf8("chkBoxHeaderV"));
        chkBoxHeaderV->setChecked(true);

        horizontalLayout_6->addWidget(chkBoxHeaderV);

        chkBoxHeaderH = new QCheckBox(groupBox);
        chkBoxHeaderH->setObjectName(QString::fromUtf8("chkBoxHeaderH"));
        chkBoxHeaderH->setChecked(true);

        horizontalLayout_6->addWidget(chkBoxHeaderH);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        rBtnSelectRow = new QRadioButton(groupBox);
        rBtnSelectRow->setObjectName(QString::fromUtf8("rBtnSelectRow"));

        horizontalLayout_7->addWidget(rBtnSelectRow);

        rBtnSelectItem = new QRadioButton(groupBox);
        rBtnSelectItem->setObjectName(QString::fromUtf8("rBtnSelectItem"));
        rBtnSelectItem->setChecked(true);

        horizontalLayout_7->addWidget(rBtnSelectItem);


        verticalLayout->addLayout(horizontalLayout_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(groupBox);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableInfo = new QTableWidget(centralWidget);
        if (tableInfo->columnCount() < 6)
            tableInfo->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableInfo->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        tableInfo->setObjectName(QString::fromUtf8("tableInfo"));
        tableInfo->setEditTriggers(QAbstractItemView::DoubleClicked|QAbstractItemView::SelectedClicked);
        tableInfo->setAlternatingRowColors(true);
        tableInfo->setSelectionBehavior(QAbstractItemView::SelectItems);

        verticalLayout_2->addWidget(tableInfo);

        textEdit = new QPlainTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setMaximumSize(QSize(16777215, 200));

        verticalLayout_2->addWidget(textEdit);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        toolBar->addAction(actionSetStudentList);

        retranslateUi(MainWindow);
        QObject::connect(btnSetHeader, SIGNAL(clicked()), MainWindow, SLOT(on_btnSetHeader_clicked()));
        QObject::connect(btnIniData, SIGNAL(clicked()), MainWindow, SLOT(on_btnIniData_clicked()));
        QObject::connect(tableInfo, SIGNAL(currentCellChanged(int,int,int,int)), MainWindow, SLOT(on_tableInfo_currentCellChanged(int,int,int,int)));
        QObject::connect(btnInsertRow, SIGNAL(clicked()), MainWindow, SLOT(on_btnInsertRow_clicked()));
        QObject::connect(btnAppendRow, SIGNAL(clicked()), MainWindow, SLOT(on_btnAppendRow_clicked()));
        QObject::connect(btnDelCurRow, SIGNAL(clicked()), MainWindow, SLOT(on_btnDelCurRow_clicked()));
        QObject::connect(btnAutoRowHeight, SIGNAL(clicked()), MainWindow, SLOT(on_btnAutoRowHeight_clicked()));
        QObject::connect(btnAutoColWidth, SIGNAL(clicked()), MainWindow, SLOT(on_btnAutoColWidth_clicked()));
        QObject::connect(btnReadToEdit, SIGNAL(clicked()), MainWindow, SLOT(on_btnReadToEdit_clicked()));
        QObject::connect(chkBoxTabEditable, SIGNAL(clicked(bool)), MainWindow, SLOT(on_chkBoxTabEditable_clicked(bool)));
        QObject::connect(chkBoxHeaderH, SIGNAL(clicked(bool)), MainWindow, SLOT(on_chkBoxHeaderH_clicked(bool)));
        QObject::connect(chkBoxHeaderV, SIGNAL(clicked(bool)), MainWindow, SLOT(on_chkBoxHeaderV_clicked(bool)));
        QObject::connect(chkBoxRowColor, SIGNAL(clicked(bool)), MainWindow, SLOT(on_chkBoxRowColor_clicked(bool)));
        QObject::connect(rBtnSelectItem, SIGNAL(clicked()), MainWindow, SLOT(on_rBtnSelectItem_clicked()));
        QObject::connect(rBtnSelectRow, SIGNAL(clicked()), MainWindow, SLOT(on_rBtnSelectRow_clicked()));
        QObject::connect(btnSetRows, SIGNAL(clicked()), MainWindow, SLOT(on_btnSetRows_clicked()));
        QObject::connect(actionSetStudentList, SIGNAL(triggered()), MainWindow, SLOT(on_actionSetStudentList_triggered()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QTableWidget\347\232\204\344\275\277\347\224\250", nullptr));
        actionSetStudentList->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\345\255\246\347\224\237\345\220\215\345\215\225", nullptr));
#ifndef QT_NO_TOOLTIP
        actionSetStudentList->setToolTip(QApplication::translate("MainWindow", "\350\256\276\347\275\256\345\255\246\347\224\237\345\220\215\345\215\225", nullptr));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QString());
        btnSetHeader->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\350\241\250\345\244\264", nullptr));
        btnSetRows->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\350\241\214\346\225\260", nullptr));
        btnIniData->setText(QApplication::translate("MainWindow", "\345\210\235\345\247\213\345\214\226\350\241\250\346\240\274\346\225\260\346\215\256", nullptr));
        btnInsertRow->setText(QApplication::translate("MainWindow", "\346\217\222\345\205\245\350\241\214", nullptr));
        btnAppendRow->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\350\241\214", nullptr));
        btnDelCurRow->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\345\275\223\345\211\215\350\241\214", nullptr));
        btnAutoRowHeight->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\350\260\203\350\212\202\350\241\214\351\253\230", nullptr));
        btnAutoColWidth->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250\350\260\203\350\212\202\345\210\227\345\256\275", nullptr));
        btnReadToEdit->setText(QApplication::translate("MainWindow", "\350\257\273\345\217\226\350\241\250\346\240\274\345\206\205\345\256\271\345\210\260\346\226\207\346\234\254", nullptr));
        chkBoxTabEditable->setText(QApplication::translate("MainWindow", "\350\241\250\346\240\274\345\217\257\347\274\226\350\276\221", nullptr));
        chkBoxRowColor->setText(QApplication::translate("MainWindow", "\351\227\264\351\232\224\350\241\214\345\272\225\350\211\262", nullptr));
        chkBoxHeaderV->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\350\241\214\350\241\250\345\244\264", nullptr));
        chkBoxHeaderH->setText(QApplication::translate("MainWindow", "\346\230\276\347\244\272\345\210\227\350\241\250\345\244\264", nullptr));
        rBtnSelectRow->setText(QApplication::translate("MainWindow", "\350\241\214\351\200\211\346\213\251", nullptr));
        rBtnSelectItem->setText(QApplication::translate("MainWindow", "\345\215\225\345\205\203\346\240\274\351\200\211\346\213\251", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableInfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\345\247\223\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableInfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\200\247\345\210\253", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableInfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\345\207\272\347\224\237\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableInfo->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\346\260\221\346\227\217", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableInfo->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\345\210\206\346\225\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableInfo->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\346\230\257\345\220\246\345\205\232\345\221\230", nullptr));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
