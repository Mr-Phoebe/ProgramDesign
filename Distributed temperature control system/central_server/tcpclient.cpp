#include "tcpclient.h"
#include "mainwindow.h"
#include "billshow.h"
#include "connection.h"


/*--------------初始化信息--------------------------*/
extern int Smodel;//制冷or制热 0 or 1
extern int Swind;//风速 0，1，2
extern int Stempmin;//最低温度
extern int Stempmax;//最高温度
extern double price;//设置的单价
extern double Stem;//初始目标温度


/*--------------各个房间的信息-----------------------*/
extern int wind_speed[6];
extern double air_tem[6];//房间目标温度
extern double current_price[6];//当前需要付款的金额
extern double current_tem[6];  //当前温度（主机进行模拟）
extern int start_time[6];   //获取系统开机的时间
extern int power[6];        //获取从机是否开机
extern int inwork[6];       //是否调度
extern int powertime[6];    //开机关机次数
extern int dispatchtime[6]; //调度次数
/*------------------------------------------------*/
extern int roomnum;//查询输入的房间号码

/*------------------------------------------------------*/

extern int year;
extern int month;
extern int day;
extern int hour;
extern int minute;
extern int second;
extern void DataTimeToEvery();

extern const int windprice[3] = {4, 5, 6};

TcpClient::TcpClient(QObject *parent)
{
    flag = 1;//刚开机，没有初始化
    stop = 0;
    shut = 1;//关机
    connect(this,SIGNAL(readyRead()),this,SLOT(dataReceived()));
    connect(this,SIGNAL(disconnected()),this,SLOT(slotDisconnected()));
}

TcpClient::~TcpClient()
{
    power[Number] = 0;
    if(m_nTimerId != 0)
        killTimer(m_nTimerId);
}

void TcpClient::stoptime()
{
    power[Number] = 0;
    if(m_nTimerId != 0)
        killTimer(m_nTimerId);
}


void TcpClient::timerEvent(QTimerEvent *event)
{
    //qDebug( "timer event, id %d", event->timerId() );
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    current_price[Number] = ShowMeTheMoney(Number);
    getTemperature();
    out<<UPDATE<<Number<<current_tem[Number]<<current_price[Number];//需要模拟房间温度和当前费用赋给这两个值
    dispatchtime[Number] ++;

    writemessage(message);
    //qDebug()<<"\n\n当前的温度啊："<<current_tem[Number]<<"当前的费用啊："<<current_price[Number] <<"\n\n";

}

void TcpClient::dataReceived()
{
    QDataStream in(this);
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_4_6);//设置数据流版本，这里要和服务器端相同

    int type;//判断包头
    while(bytesAvailable()>0)
    {
        in>>type>>Number;
        dispatchtime[Number] ++;
        //qDebug()<<"收到了从机相应的包:"<<"type:"<<type<<"number:"<<Number;
        switch (type)
        {
        case INI_REQ://发连接包
            qDebug()<<"初始化包";
            out<<ACK_INI<<Number<<Swind<<Stem<<Stempmax<<Stempmin<<price<<Smodel;
            writemessage(message);
            qDebug()<<"主机发送的初始信息包："<<Number<<" "<<Swind<<" "<<Stem<<" "<<Stempmin<<" "<<Stempmax<<" "<<price;
            break;
        case ACK_INI://发送确认包
            break;
        case START_REQ://sent the start_up message
            //in>>roomnum;//开机啦啦啦，加入数据库
            out<<ACK_START<<Number;
            //获得系统时间
            DataTimeToEvery();
            //获得风速当前温度和目标温度
            if(shut == 1)
            {
                current_price[Number] = ShowMeTheMoney(Number);
                if(flag == 1)      //关机且没有初始化
                {
                    start_time[Number] = (int)clock();//获取系统开机的时间
                    wind_speed[Number] = Swind;
                    air_tem[Number] = Stem;
                    current_tem[Number] = 19;
                    m_nTimerId = startTimer(60000/quick);     //启动定时器

                    //qDebug()<<"m_nTimerId:"<< m_nTimerId;

                    flag = 0;
                    //初始化完成，空调开机
                    //写入数据库
                    WriteToSQL();
                    writemessage(message);
                }
                shut = 0;
                power[Number] = 1;
                powertime[Number] ++;
            }

            out<<UPDATE<<Number<<current_tem[Number]<<current_price[Number];
            writemessage(message);
            break;
        case ACK_START://发送开机确认的包
            break;
        case WIND_CHANGE://sent the wind_change message
            in>> wind_speed[Number];//数据库，从机改变了风速
            out<<ACK_WIND_CHANGE<<Number;
            //获得系统时间
            DataTimeToEvery();

            //写入数据库
            WriteToSQL();
            start_time[Number]=(int)clock();
            writemessage(message);
            break;
        case ACK_WIND_CHANGE:
            break;
        case TEMP_CHANGE:
            in>> air_tem[Number];//数据库，从机改变了温度
            out<< ACK_TEMP_CHANGE<<Number;
            //获得系统时间
            DataTimeToEvery();

            //写入数据库
            WriteToSQL();

            writemessage(message);
            break;
        case ACK_TEMP_CHANGE:
            break;
        case  SHUTDOWN_REQ:
            //从机关机啦，数据库
            out<<ACK_TEMP_CHANGE<<Number;
            //获得系统时间
            DataTimeToEvery();
            //获得目标温度和当前温度
            //air_tem = Stem;
            //wind_speed = Swind;
            //写入数据库
            shut = 1;//空调关机
            power[Number] = 0;
            WriteToSQL();

            writemessage(message);
            break;
        case ACK_SHUNTDOWN:
            break;
        case UPDATE:
            break;
        case ACK_UPDATE:
            //从机正常工作
            break;
        case POWER_OFF://强制从机关机，暂定
            break;
        case ACK_POWER_OFF:
            //从机关机啦，数据库
            //获得系统时间
            DataTimeToEvery();

            //写入数据库
            shut = 1;//当前从机关机
            power[Number] = 0;
            WriteToSQL();
            break;
        }
    }
    //emit updateClients(msg,length);
}

void TcpClient::slotDisconnected()
{
    emit disconnected(this->socketDescriptor());
}

void TcpClient::writemessage(QByteArray block)//TCP发包
{
    this->write(block);
}

void TcpClient::getTemperature() //模拟温度变化
{
    int cur_time = (int)clock();
    int time;
    time = (cur_time - start_time[Number]) * quick / 60000 ;
    qDebug()<<"time:"<<time;
    if(stop == 0 && shut == 0)//空调正常工作，没有暂停工作，没有关机，且在调度算法内排到前三
    {
        if(Smodel == 0)//制冷
        {

            if(wind_speed[Number] == 0)
            {
                if(time%3 == 0)
                {
                    current_tem[Number] = current_tem[Number]-1;
                }
            }
            else
            {
                if(wind_speed[Number] == 1)
                {
                    if(time%2 == 0)
                        current_tem[Number] = current_tem[Number]-1;
                }
                else
                    current_tem[Number] = current_tem[Number]-1;
            }
            if(current_tem[Number] < air_tem[Number])
            {
                //qDebug()<<"当前温度："<<current_tem[Number]<<"目标温度："<<air_tem[Number];
                stop = 1;//达到目标温度停止工作
                start_time[Number] = (int)clock();
            }
        }
        else
        {
            if(wind_speed[Number] == 0)
            {
                if(time%3 == 0)
                    current_tem[Number] = current_tem[Number]+1;
            }
            else
            {
                if(wind_speed[Number] == 1)
                {
                    if(time%2 == 0)
                        current_tem[Number]=current_tem[Number]+1;
                }
                else
                    current_tem[Number]=current_tem[Number]+1;
            }
            if(current_tem[Number] > air_tem[Number])
            {
                //qDebug()<<"当前温度："<<current_tem[Number]<<"目标温度："<<air_tem[Number];
                stop = 1;//达到目标温度停止工作
                start_time[Number] = (int)clock();
            }
        }
    }
    else
    {
        //qDebug()<<"空调停止工作";
        if(time%2 == 0)
        {
            if(current_tem[Number] < Stem)                  //恢复成室温
                current_tem[Number] = current_tem[Number] + 1;
            else if(current_tem[Number] > Stem)
                current_tem[Number] = current_tem[Number] - 1;
        }
        if(shut == 0 && ((current_tem[Number] <= air_tem[Number] && Smodel == 1) || (current_tem[Number] >= air_tem[Number] && Smodel == 0)))     //开机且等于目标温度，则空调开始运行
        {
            stop = 0;
            start_time[Number] = (int)clock();
        }
    }
    qDebug() << stop << shut;
    qDebug()<<"当前的温度："<<current_tem[Number];
}

double TcpClient::ShowMeTheMoney(int room_num)
{
    QSqlQuery query;
    double cur_pay = 0;
    double total_pay = 0;

    int cur_year = 0;
    int cur_month = 0;
    int cur_day = 0;
    int cur_hour = 0;
    int cur_minute = 0;
    int cur_second = 0;
    int pre_year = 0;
    int pre_month = 0;
    int pre_day = 0;
    int pre_hour = 0;
    int pre_minute = 0;
    int pre_second = 0;
    int wind = 0;
    int statement = 0;

    QString sql = "select year,month,day,hour,minute,second,windspeed,statement from room" + QString::number(room_num);
    if(1 <= room_num && room_num <= 5)
    {
        query.exec(sql);
        while(query.next())
        {
            pre_day = cur_day;
            pre_year = cur_year;
            pre_month = cur_month;
            pre_hour = cur_hour;
            pre_minute = cur_minute;
            pre_second = cur_second;
            cur_year = query.value(0).toInt();
            cur_month = query.value(1).toInt();
            cur_day = query.value(2).toInt();
            cur_hour = query.value(3).toInt();
            cur_minute = query.value(4).toInt();
            cur_second = query.value(5).toInt();

            if(pre_year > 0 && statement)
                cur_pay = ((cur_year - pre_year) * 8760.0 + (cur_month - pre_month) * 720.0 + (cur_day - pre_day) * 24.0
                           +(cur_hour - pre_hour) + (cur_minute - pre_minute)/60.0 + (cur_second - pre_second)/3600.0)
                            * windprice[wind] * (1.1 + 0.1 * Smodel) * price;

            wind = query.value(6).toInt();
            statement = query.value(7).toInt();

            total_pay += cur_pay;
        }
        if(cur_year > 0 && shut == 0 && inwork[Number])
            total_pay += ((year - cur_year) * 8760.0 + (month - cur_month) * 720.0 + (day - cur_day) * 24.0
                          +(hour - cur_hour) + (minute - cur_minute)/60.0 + (second - cur_second)/3600.0)
                            * windprice[wind] * (1.1 + 0.1 * Smodel) * price;
        return total_pay;
    }
    else
    {
        qDebug()<<"出错，请重新输入房间号码！";
        qDebug()<<room_num;
        QMessageBox::critical(0,"Error1","Please input correct room_num!",QMessageBox::Ignore);
        return 0;
    }

}

void TcpClient::WriteToSQL()
{
    qDebug()<<"进入写入数据库函数";
    QSqlQuery query;


    QString sql = "insert into room" + QString::number(Number) + " (year, month, day, hour, minute, second, cur_temp, windspeed, temp, statement)" +
                  " values(:year, :month, :day, :hour, :minute, :second, :cur_temp, :windspeed, :temp, :statement)";
    query.prepare(sql);
    query.bindValue(":year", year);
    query.bindValue(":month", month);
    query.bindValue(":day", day);
    query.bindValue(":hour", hour);
    query.bindValue(":minute", minute);
    query.bindValue(":second", second);
    query.bindValue(":cur_temp", current_tem[Number]);
    query.bindValue(":windspeed", wind_speed[Number]);
    query.bindValue(":temp", air_tem[Number]);
    if(power[Number] && inwork[Number])     //开机且在调度中
        query.bindValue(":statement",1);
    else
        query.bindValue(":statement",0);
    query.exec();

    // query.first();
    // query.exec("select * from room1");
    // qDebug()<<query.value(0).toInt()<<query.value(1).toInt()<<query.value(2).toInt()<<query.value(3).toInt()<<query.value(4).toInt()<<query.value(5).toInt()<<query.value(6).toDouble()<<query.value(7).toInt()<<query.value(8).toDouble();
}



