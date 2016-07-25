#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtNetwork/QTcpSocket>
#include <QMainWindow>
#include<QDebug>
#include<qtextcodec.h>
#include <QDateTime>
#include <QTimer>
#include<qmessagebox.h>

#define Number 3

extern int wind;//初始风速大小
extern double tem;//初始温度
extern int max_tem;//最大温度
extern int min_tem;//最小温度
extern int model;
extern double price;//当前费用

extern double cu_tem;
extern double cu_price;
extern int flag;//the condition is running
extern int signal_com;

extern enum Package{INI_REQ,START_REQ,ACK_START,ACK_INI,WIND_CHANGE,ACK_WIND_CHANGE,
    TEMP_CHANGE,ACK_TEMP_CHANGE,SHUTDOWN_REQ,ACK_SHUNTDOWN,UPDATE,ACK_UPDATE,POWER_OFF,ACK_POWER_OFF}package;

typedef struct Parameter{
    int wind;
    double  tem;
    int max_tem;
    int min_tem;
    double price;
}parameter;

extern parameter argument;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();

    void on_tem_change_valueChanged(int arg1);

   // void on_wind_change_activated(const QString &arg1);
    //tcp
    void requestNewconnect();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);
    void on_connect_clicked();
    void sentPackage(QByteArray);
    //void onTimerOut();
    void initial();
    void on_start_button_clicked();

    //void on_wind_change_currentIndexChanged(int index);

    void on_wind_change_activated(int index);

private:
    quint16 blockSize;
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;//add the TCP
    QTimer timer;
};

#endif // MAINWINDOW_H
