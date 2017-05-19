#-------------------------------------------------
#
# Project created by QtCreator 2017-05-17T16:23:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = Employees
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    employeeitem.cpp \
    employeedatamanagerxml.cpp \
    employeestreemodel.cpp

HEADERS  += mainwindow.h \
    employeeitem.h \
    employeedatamanagerinterface.h \
    employeedatamanagerxml.h \
    employeestreemodel.h \
    defines.h

FORMS    += mainwindow.ui
