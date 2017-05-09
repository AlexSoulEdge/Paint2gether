#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T20:47:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToucyTree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treeitem.cpp \
    treemodel.cpp

HEADERS  += mainwindow.h \
    treeitem.h \
    treemodel.h

FORMS    += mainwindow.ui

RESOURCES += \
    treemodel.qrc
