#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QDebug>
#include <QPalette>
#include <QPropertyAnimation>
#include <QString>
#include <QTimer>
#include <QDateTime>
#include <QWaitCondition>
#include <fstream>
#include <cstdlib>
#include "structs.h"
#include "control.h"
#include "io.h"
#include "log.h"
#include <QProcess>
#include <QDir>
#define MainWindowHeight 720
#define MainWindowWidth 1080

class MainWidget;
//class ConfigTrackNumDialog;
//class configTrackDialog;
class ManualCtrlDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        //QDateTime* dateTime;
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void configTrack(void);
        void configTrain(void);
        void openLog();
        void onTimeout(void);
        void start();
        void pause();

    signals:
        void updateInfoTextEdit();
        void updatePassengerListWidget(void);
        void selectedPassengerChanged(void);
        void updateTime(void);
        void refresh();

    private:
        bool started = 0;
        void createMenus(void);
        void deletePassenger(int selectedPassenger);

        MainWidget *mainWidget;
        QPushButton* logBtn;
        QTimer * timer;
};

extern MainWindow* w;
#endif // MAINWINDOW_H
