#-------------------------------------------------
#
# Project created by QtCreator 2016-07-01T11:16:20
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ReportBuilder
TEMPLATE = app

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    qssStyle.cpp

HEADERS  += \
    mainwindow.h \
    qssStyle.h

FORMS    += \
    mainwindow.ui

RESOURCES = \
    resources/resources.qrc

TRANSLATIONS = translation.ru.ts
