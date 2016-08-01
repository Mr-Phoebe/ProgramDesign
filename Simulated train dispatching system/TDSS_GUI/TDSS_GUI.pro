#-------------------------------------------------
#
# Project created by QtCreator 2016-06-17T11:35:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TDSS_GUI
TEMPLATE = app

SOURCES += main.cpp\
    configTrack.cpp \
    configTrain.cpp \
    control.cpp \
    infoWidget.cpp \
    io.cpp \
    mainWidget.cpp \
    manualCtrlDialog.cpp \
    structs.cpp \
    cmdDialog.cpp \
    displayWidget.cpp \
    mainWindow.cpp \
    log.cpp

HEADERS  += \
    configTrack.h \
    configTrain.h \
    control.h \
    displayWidget.h \
    infoWidget.h \
    io.h \
    mainWidget.h \
    structs.h \
    cmdDialog.h \
    manualCtrlDialog.h \
    mainWindow.h \
    log.h

RESOURCES += \
    TDSS_GUI.qrc

CONFIG += c++11

win32: debug {
CONFIG += console
}

DISTFILES +=

