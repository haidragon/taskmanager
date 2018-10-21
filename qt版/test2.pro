#-------------------------------------------------
#
# Project created by QtCreator 2016-06-12T19:20:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test2
TEMPLATE = app


SOURCES += main.cpp\
    head.cpp \
    isyswin.cpp \
    TaskManagerWindow.cpp \
    ProcessWidget.cpp \
    ServiceWidget.cpp \
    PerformanceWidget.cpp \
    SystemWidget.cpp \
    LineChartDialog.cpp \
    infoWindow.cpp \
    InterfaceThread.cpp

HEADERS  += \
    isysinfo.h \
    isyswin.h \
    TaskManagerWindow.h \
    ProcessWidget.h \
    ServiceWidget.h \
    PerformanceWidget.h \
    SystemWidget.h \
    LineChartDialog.h \
    infoWindow.h \
    InterfaceThread.h \
    chooseHead.h

LIBS += libkernel32\
        libpsapi
