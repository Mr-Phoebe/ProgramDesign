#-------------------------------------------------
#
# Project created by QtCreator 2016-06-01T21:10:15
#
#-------------------------------------------------

QT       += core gui widgets sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = central_server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    server.cpp \
    tcpclient.cpp \
    billshow.cpp \
    log_dialog.cpp

HEADERS  += mainwindow.h \
    server.h \
    tcpclient.h \
    billshow.h \
    connection.h \
    log_dialog.h

FORMS    += mainwindow.ui \
    billshow.ui \
    log_dialog.ui

RESOURCES += \
    recource.qrc
