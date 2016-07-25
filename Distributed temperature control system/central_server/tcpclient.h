#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QTcpSocket>
#include <QObject>

class TcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    TcpClient(QObject *parent=0);
    ~TcpClient();
    void getTemperature();
    void writemessage(QByteArray block);
    double ShowMeTheMoney(int room_num);
    void WriteToSQL();
    void stoptime();


    int m_nTimerId;
    int Number;//判断房间号
    int flag;//判断是否初始化
    int stop;//判断空调是否工作
    int shut;


signals:
    //void updateClients(QString,int);
    void disconnected(int);
protected slots:
    void dataReceived();
    void slotDisconnected();
    void timerEvent( QTimerEvent *event);
};

#endif // TCPCLIENT_H
