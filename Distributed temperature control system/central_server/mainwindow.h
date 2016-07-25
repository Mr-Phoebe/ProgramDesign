#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QTimer>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <qtextcodec.h>
#include <qmessagebox.h>
#include <qtimer.h>
#include <QDebug>
#include <QMessageBox>
#include <qdatetime.h>
#include <sys/time.h>
#include "server.h"
#include "tcpclient.h"

#define quick 10

namespace Ui {
class MainWindow;
}

extern enum Package{INI_REQ,START_REQ,ACK_START,ACK_INI,WIND_CHANGE,ACK_WIND_CHANGE,
    TEMP_CHANGE,ACK_TEMP_CHANGE,SHUTDOWN_REQ,ACK_SHUNTDOWN,UPDATE,ACK_UPDATE,POWER_OFF,ACK_POWER_OFF}package;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_putton_setprice_clicked();

    void on_putton_setmodel_clicked();

    void on_pushButton_exit_clicked();

    void on_pushButton_print_clicked();

    void refreshMonitor();

    void on_pushButton_showlog_clicked();

private:
    Ui::MainWindow *ui;
    Server *server;//add the TCP
    //QTcpServer *tcpserver;
    int port;
    void setupsocket();
    QString getInf(int roomnum);
    //MainWindow *newMainWindow;//跳出新窗口使用
};

extern void DataTimeToEvery();


#endif // MAINWINDOW_H
