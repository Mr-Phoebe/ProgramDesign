#ifndef SERVER_H
#define SERVER_H


#include <QTcpServer>
#include <QObject>
#include "tcpclient.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server(QObject *parent=0,int port=0);
    void dispatch(int kind);

    QList<TcpClient*> tcpClientSocketList;
public slots:
    //void updateClients(QString,int);
    void slotDisconnected(int);
private:
    void incomingConnection(qintptr);

};

#endif // SERVER_H
