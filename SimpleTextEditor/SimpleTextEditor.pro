QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimpleTextEditor
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    codeeditor.cpp \
    aboutdialog.cpp \
    finddialog.cpp \
    replacedialog.cpp

HEADERS += \
    mainwindow.h \
    codeeditor.h \
    aboutdialog.h \
    finddialog.h \
    replacedialog.h

FORMS += \
    mainwindow.ui \
    aboutdialog.ui \
    finddialog.ui \
    replacedialog.ui
