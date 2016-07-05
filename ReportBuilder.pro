#-------------------------------------------------
#
# Project created by QtCreator 2016-07-01T11:16:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReportBuilder
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    ReportDialog.cpp \
    qssStyle.cpp

HEADERS  += \
    mainwindow.h \
    ReportDialog.h \
    qssStyle.h

FORMS    += \
    mainwindow.ui \
    ReportDialog.ui

RESOURCES = \
    resources/resources.qrc

TRANSLATIONS = translation.ru.ts
