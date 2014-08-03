#-------------------------------------------------
#
# Project created by QtCreator 2014-07-31T21:42:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lantern
TEMPLATE = app

SOURCES += main.cpp\
    view/mainwindow.cpp \
    service/serviceclient.cpp \
    presenter/mainwindowpresenter.cpp \
    model/mainwindowmodel.cpp

HEADERS  += \
    view/mainwindow.h \
    service/serviceclient.h \
    presenter/mainwindowpresenter.h \
    model/mainwindowmodel.h \
    view/iviewmain.h \
    model/package.h
    view/mainwindow.h

FORMS    +=
    UI/mainwindow.ui
