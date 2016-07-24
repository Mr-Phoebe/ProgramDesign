#-------------------------------------------------
#
# Project created by QtCreator 2013-03-02T20:05:24
#
#-------------------------------------------------

QT       += core gui sql

TARGET = HotelManagementSystem
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    Evaluate.cpp \
    Check_in.cpp \
    Check_out.cpp \
    Reserve.cpp \
    Login.cpp \
    Room.cpp \
    Menu.cpp \
    Plane.cpp \
    Set.cpp \
    Time.cpp

HEADERS  += widget.h \
    connection.h \
    plane.h

FORMS    += widget.ui \
    plane.ui

RESOURCES += \
    res.qrc

win32:RC_FILE = main.rc
