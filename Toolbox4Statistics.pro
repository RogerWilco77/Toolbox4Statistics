#-------------------------------------------------
#
# Project created by QtCreator 2014-10-06T21:59:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Toolbox4Statistics
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataset.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    dataset.h \
    qcustomplot.h

FORMS    += mainwindow.ui

