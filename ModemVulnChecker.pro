#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T02:31:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ModemVulnChecker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    decompressor.cpp \
    httpclass.cpp \
    fileutil.cpp

HEADERS  += mainwindow.h \
    decompressor.h \
    httpclass.h \
    fileutil.h

FORMS    += mainwindow.ui
CONFIG += c++11

RC_ICONS = modem.ico
