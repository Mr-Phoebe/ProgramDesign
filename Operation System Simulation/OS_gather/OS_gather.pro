#-------------------------------------------------
#
# Project created by QtCreator 2016-04-30T10:19:12
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OS_gather
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    fileSystem.cpp \
    fs_tools.cpp \
    filewindow.cpp \
    task.cpp \
    notepad.cpp \
    m_tools.cpp \
    interface.cpp \
    swap.cpp \
    allocator.cpp \
    tracker.cpp

HEADERS  += mainwindow.h \
    filesystem.h \
    filewindow.h \
    taskmanager.h \
    process.h \
    notepad.h \
    memory.h \
    m_allocator.h \
    m_tracker.h

FORMS    += mainwindow.ui \
    filewindow.ui \
    notepad.ui
