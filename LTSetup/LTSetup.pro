#-------------------------------------------------
#
# Project created by QtCreator 2014-10-08T13:18:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LTSetup
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    common.cpp \
    filesystem.cpp \
    versiondialog.cpp

HEADERS  += mainwindow.h \
    common.h \
    filesystem.h \
    versiondialog.h

FORMS    += mainwindow.ui \
    versiondialog.ui
