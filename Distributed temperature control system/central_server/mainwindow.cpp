#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "billshow.h"
#include "connection.h"
#include "log_dialog.h"
#include "server.h"
#include "tcpclient.h"

/*---------------获取TCP序列号---------------------------*/
int sequence = 0;
/*-----------------空调主机的初始化参数---------------------*/
int Smodel;//制冷or制热 0 or 1
int Swind;//风速 0，1，2
int Stempmin;//最低温度
int Stempmax;//最高温度
int Sdispatch;//调度策略
double price;//设置的单价
double Stem;//初始目标温度
/*------------------------------------------------------*/

int roomnum;//查询输入的房间号码


/*-----------------主机自行计算的信息-----------------------*/
double current_price[6];//当前需要付款的金额
double current_tem[6]= {19,19,19,19,19,19}; //当前温度（主机进行模拟）
int windtime[6] = {0,0,0,0,0,0};      //修改风速次数
int temptime[6] = {0,0,0,0,0,0};      //修改温度次数
int powertime[6] = {0,0,0,0,0,0};     //开关机次数
int dispatchtime[6] = {0,0,0,0,0,0};  //调度次数
double servertime[6] = {0,0,0,0,0,0}; //服务时长
const int windprice[3] = {5, 6, 7};
/*------------------------------------------------------*/

/*----------------写入数据库需要的信息----------------------*/
int year = 2016;
int month = 6;
int day = 1;
int hour = 0;
int minute = 0;
int second = 0;
int wind_speed[6]= {0,0,0,0,0,0};
double air_tem[6] = {0,0,0,0,0,0};
int power[6] ={0,0,0,0,0,0};
int inwork[6] = {1,1,1,1,1,1};
QTimer *timer;
/*------------------------------------------------------*/

double start_time[6];//获取系统开机的时间

QString room[6];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    room[1] = "房间1";
    room[2] = "房间2";
    room[3] = "房间3";
    room[4] = "房间4";
    room[5] = "房间5";

    //根据状态信息给room1~room5赋值，我这里是特别简单的直接赋值 看一下可读状态信息赋值后分别显示

    ui->textBrowser_room1->setText(room[1]+"\n\n关机");//显示文本一内容，可设置参数为房间状态文本,
    ui->textBrowser_room2->setText(room[2]+"\n\n关机");
    ui->textBrowser_room3->setText(room[3]+"\n\n关机");
    ui->textBrowser_room4->setText(room[4]+"\n\n关机");
    ui->textBrowser_room5->setText(room[5]+"\n\n关机");


    setupsocket();
    port = 6666;

    //新建一个QTimer对象
    timer = new QTimer();
    //设置定时器每个多少毫秒发送一个timeout()信号
    timer->setInterval(60000/quick);
    //启动定时器
    timer->start();
    //信号和槽
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshMonitor()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*---------------------TCP-----------------------------*/

void MainWindow::setupsocket()
{
    server = new Server(this, port);
}

/*---------------------SET-----------------------------*/

void MainWindow::on_putton_setprice_clicked()   //获取单位电价
{
    QString price_text = ui->lineEdit_price_2->text();
    price = price_text.toDouble();
    qDebug()<<price;
}

void MainWindow::on_putton_setmodel_clicked()   //提交初始化参数
{
    Smodel = ui->comboBox_model->currentIndex();
    Swind = ui->comboBox_wind->currentIndex();
    Stempmin = 16 + ui->comboBox_mintem->currentIndex();
    Stempmax = 21 + ui->comboBox_maxtem->currentIndex();
    Sdispatch = ui->comboBox_dispatch->currentIndex();
    Stem = 25.0;
    qDebug()<<Smodel;//可在mian中设置全局变量，在此将点击获得的值赋给对应全局变量
    qDebug()<<Swind;
    qDebug()<<Stempmin;
    qDebug()<<Stempmax;
    qDebug()<<Stem;
}


/*------------------SHOW-------------------------*/

void MainWindow::on_pushButton_print_clicked()
{
    QString room_num = ui->lineEdit_roomnum->text();
    roomnum = room_num.toInt();
    qDebug()<<roomnum;
    Billshow *s = new Billshow(this);

    s->show();
}

void MainWindow::refreshMonitor()
{
    ui->textBrowser_room1->setText(getInf(1));
    ui->textBrowser_room2->setText(getInf(2));
    ui->textBrowser_room3->setText(getInf(3));
    ui->textBrowser_room4->setText(getInf(4));
    ui->textBrowser_room5->setText(getInf(5));

    server->dispatch(Sdispatch);
}


QString MainWindow::getInf(int room_num)
{
    float cur_pay = 0;
    float total_pay = 0;
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
    int pre_wind = 0;
    double temp = 0.0;
    double pre_temp = 0.0;
    QString total_str = room[room_num] + "\n\n";
    QString str_temp;
    QSqlQuery query;
    if(!power[room_num])              //关机
    {
        total_str += "关机";
    }
    else
    {
        if(inwork[room_num])
        {
            total_str += "调度中\n\n";
        }
        else
        {
            total_str += "没有调度\n\n";
        }
        windtime[room_num] = 0;
        temptime[room_num] = 0;
        servertime[room_num] = 0.0;
        QString sql = "select year,month,day,hour,minute,second,windspeed,temp,statement from room" + QString::number(room_num);
        query.exec(sql);
        while(query.next())
        {
            pre_day = cur_day;
            pre_year = cur_year;
            pre_month = cur_month;
            pre_hour = cur_hour;
            pre_minute = cur_minute;
            pre_second = cur_second;
            pre_wind = wind;
            pre_temp = temp;
            cur_year = query.value(0).toInt();
            cur_month = query.value(1).toInt();
            cur_day = query.value(2).toInt();
            cur_hour = query.value(3).toInt();
            cur_minute = query.value(4).toInt();
            cur_second = query.value(5).toInt();
            wind = query.value(6).toInt();
            temp = query.value(7).toDouble();

            if(pre_year > 0 && statement)
            {
                double cur_time = ((cur_year - pre_year) * 8760.0 + (cur_month - pre_month) * 720.0 + (cur_day - pre_day) * 24.0
                                   +(cur_hour - pre_hour) + (cur_minute - pre_minute)/60.0 + (cur_second - pre_second)/3600.0);
                cur_pay = cur_time * windprice[pre_wind] * (1.1 + 0.1 * Smodel) * price;
                if(wind != pre_wind)
                    windtime[room_num] ++;
                if(0.001 <= abs(temp - pre_temp))
                    temptime[room_num] ++;
                servertime[room_num] += cur_time;
            }

            statement = query.value(8).toInt();
            total_pay += cur_pay;
        }
        DataTimeToEvery();
        if(cur_year > 0 && power[room_num] && inwork[room_num])
        {
            double cur_time = ((year - cur_year) * 8760.0 + (month - cur_month) * 720.0 + (day - cur_day) * 24.0
                               +(hour - cur_hour) + (minute - cur_minute)/60.0 + (second - cur_second)/3600.0);
            cur_pay = cur_time * windprice[wind] * (1.1 + 0.1 * Smodel) * price;
            total_pay += cur_pay;
            servertime[room_num] += cur_time;
        }
        str_temp = str_temp.number(current_tem[room_num], 10, 2);
        total_str += "现在温度：" + str_temp;
        total_str += "\n";
        str_temp = str_temp.number(air_tem[room_num], 10, 2);
        total_str += "目标温度：" + str_temp;
        total_str += "\n";
        str_temp = str_temp.number(wind_speed[room_num], 10);
        total_str += "风速：" + str_temp;
        total_str += "\n\n";
        str_temp = str_temp.number(cur_pay, 10, 2);
        total_str += "当前花费：" + str_temp;
        total_str += "\n\n";
        str_temp = str_temp.number(windtime[room_num],10);
        total_str += "修改风速次数：" + str_temp;
        total_str += "\n";
        str_temp = str_temp.number(temptime[room_num],10);
        total_str += "修改温度次数：" + str_temp;
        total_str += "\n";
        str_temp = str_temp.number(powertime[room_num],10);
        total_str += "开关机次数：" + str_temp;
        total_str += "\n";
        total_str += "总消费：";
        str_temp = str_temp.number(total_pay);
        total_str += str_temp;
    }
    return total_str;
}

void DataTimeToEvery()
{
    //获得系统时间
    //转换成所需的结构
    QDate dt = QDate::currentDate();
    year = dt.year();
    month = dt.month();
    day = dt.day();
    QTime current_time = QTime::currentTime();
    hour = current_time.hour();
    minute = current_time.minute();
    second = current_time.second();
}
void MainWindow::on_pushButton_showlog_clicked()
{
    QString room_num = ui->lineEdit_roomnum->text();
    roomnum = room_num.toInt();
    qDebug()<<roomnum;
    if(roomnum >=1 && roomnum <= 5)
    {
        log_Dialog *log_show = new log_Dialog(this);
        log_show->show();
    }
    else
    {
          QMessageBox::information(this, "Error2", "please enter a roomnum(0-5)", QMessageBox::Ignore);
    }
}


/*------------------EXIT-------------------------*/

void MainWindow::on_pushButton_exit_clicked()   //退出系统
{
    close();
}



