#-------------------------------------------------
#
# Project created by QtCreator 2015-03-24T19:05:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_LFLAGS += -static-libgcc -static-libstdc++

TARGET = NLToolkit
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    savedata.cpp

HEADERS  += mainwindow.h \
    savedata.h \
    offsets.h

FORMS    += mainwindow.ui

