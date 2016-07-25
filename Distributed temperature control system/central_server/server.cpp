#include "server.h"
#include "mainwindow.h"
#include "billshow.h"
#include "connection.h"

extern int wind_speed[6];
extern int inwork[6];
extern int power[6];
extern int servertime[6];
extern double start_time;//获取系统开机的时间
const int dispatch_limit = 3;//调度上限

Server::Server(QObject *parent,int port)
    :QTcpServer(parent)
{
    listen(QHostAddress::Any,6666);
    qDebug()<<"进入socket";
}

void Server::incomingConnection(qintptr socketDescriptor)               //来一个新连接
{
    qDebug()<<"来了一个连接";
    TcpClient *tcpClientSocket = new TcpClient(this);
    //connect(tcpClientSocket,SIGNAL(updateClients(QString,int)),this,SLOT(updateClients(QString,int)));
    connect(tcpClientSocket,SIGNAL(disconnected(int)),this,SLOT(slotDisconnected(int)));

    tcpClientSocket->setSocketDescriptor(socketDescriptor);
    //pack.

    tcpClientSocketList.append(tcpClientSocket);

}


void Server::slotDisconnected(int descriptor)
{
    int cnt = tcpClientSocketList.count();
    for(int i = 0; i < cnt; i++)
    {
        TcpClient *item = tcpClientSocketList.at(i);
        TcpClient *temp = item;
        if(item->socketDescriptor() == descriptor)
        {
            tcpClientSocketList.removeAt(i);
            temp->stoptime();
            return;
        }
    }
    return;
}

bool cmp(const int s1, const int s2)          //开机在前，风速大在前，服务时间在前
{
    if(power[s1] != power[s2])
        return power[s1] > power[s2];
    if(wind_speed[s1] != wind_speed[s2])
        return wind_speed[s1] > wind_speed[s2];
    else
        return servertime[s1] < servertime[s2];
}


void Server::dispatch(int kind)
{
    int cnt = tcpClientSocketList.count();
    static int number[6];
    if(!kind)                    //按照风速从大到小排序，按照使用时长从短到长排序
    {
        for(int i = 0; i < cnt; i++)
        {
            number[i] = tcpClientSocketList.at(i)->Number;
        }
        qSort(number, number+cnt, cmp);

        for(int i = dispatch_limit; i < cnt; i++)
        {
            inwork[number[i]] = 0;
        }
        for(int i = 0; i < cnt && i <= dispatch_limit-1; i++)
        {
            inwork[number[i]] = 1;
        }
    }
    else                    //时间片轮转
    {
        int num = 0;
        for(int i = 0; i < cnt; i++)
            if(power[tcpClientSocketList.at(i)->Number])
                num++;
        if(num <= dispatch_limit)
        {
            for(int i = 0; i < cnt; i++)
                if(power[tcpClientSocketList.at(i)->Number])
                    inwork[tcpClientSocketList.at(i)->Number] = 1;
        }
        else
        {
            for(int i = 0; i < cnt; i++)
            {
                number[i] = inwork[tcpClientSocketList.at(i)->Number];
            }
            for(int i = 0; i < cnt; i++)
            {
                inwork[tcpClientSocketList.at(i)->Number] = number[(i+1)%cnt];
            }
        }

    }
}
