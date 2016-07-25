#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->aim_tem->setEnabled(false);
    ui->current_tem->setEnabled(false);
    ui->wind_stren->setEnabled(false);
    ui->price->setEnabled(false);
    ui->rate->setEnabled(false);
    ui->start_button->setEnabled(false);
    //tcp
    tcpSocket = new QTcpSocket(this);
    // connect(tcpSocket, SIGNAL(clicked()), this, SLOT(requestNewFortune()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    //新建一个QTimer对象
    //timer = new QTimer();
    //设置定时器每个多少毫秒发送一个timeout()信号
    //timer->setInterval(1000);
    //启动定时器
    //timer->start();
    //信号和槽
    //connect(timer, SIGNAL(timeout()), this, SLOT(onTimerOut()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_start_button_clicked()
{
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    if(!flag)
    {
        flag = 1;
        int a = argument.wind;
        if(a == 0)
        {
            ui->wind_stren->setText("低");
            QPixmap pic(":/low");
            pic = pic.scaled(ui->label_windicon->width(), ui->label_windicon->height(), Qt::KeepAspectRatio);
            ui->label_windicon->setPixmap(pic);
        }
        else if(a == 1)
        {
            ui->wind_stren->setText("中");
            QPixmap pic(":/mid");
            pic = pic.scaled(ui->label_windicon->width(), ui->label_windicon->height(), Qt::KeepAspectRatio);
            ui->label_windicon->setPixmap(pic);
        }
        else
        {
            ui->wind_stren->setText("高");
            QPixmap pic(":/high");
            pic = pic.scaled(ui->label_windicon->width(), ui->label_windicon->height(), Qt::KeepAspectRatio);
            ui->label_windicon->setPixmap(pic);
        }
        ui->rate->setText(QString::number(argument.price));

        //ui->wind_change->show(argument.wind);
        // ui->wind_change->setCurrentText(argument.wind);
        ui->tem_change->setMaximum(argument.max_tem);
        ui->tem_change->setMinimum(argument.min_tem);
        ui->aim_tem->setText(QString::number(argument.tem, 10, 2));
        ui->tem_change->setValue(argument.tem);
        qDebug()<<"wendu:"<<argument.tem;
        signal_com=0;
        out<<START_REQ<<Number;
        sentPackage(message);
        //缺少当前温度和费用
        ui->start_button->setIcon(QIcon(":/on"));
    }
    else
    {
        ui->start_button->setIcon(QIcon(":/off"));
        //in.setVersion(QDataStream::Qt_4_6);//设置数据流版本，这里要和服务器端相同
        out<<SHUTDOWN_REQ<<Number;
        sentPackage(message);
        flag = 0;
    }
}


void MainWindow::on_tem_change_valueChanged(int arg1)
{
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    //in.setVersion(QDataStream::Qt_4_6);//设置数据流版本，这里要和服务器端相同
    if(flag)
    {
        double a = arg1;
        //a=ui->tem_change->value();
        qDebug()<<"目标温度："<<a;
        ui->aim_tem->setText(QString::number(a));
        if(signal_com == 0)            //发送改变后的温度
        {
            out<<TEMP_CHANGE<<Number<<a;
            sentPackage(message);
        }
    }
}

void MainWindow::on_wind_change_activated(int index)
{
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    //in.setVersion(QDataStream::Qt_4_6);//设置数据流版本，这里要和服务器端相同
    if(flag)
    {
        int a = index;
        //a=ui->wind_change->currentText();
        if(a == 0)
        {
            ui->wind_stren->setText("低");
            QPixmap pic(":/low");
            pic = pic.scaled(ui->label_windicon->width(), ui->label_windicon->height(), Qt::KeepAspectRatio);
            ui->label_windicon->setPixmap(pic);
        }
        else if(a == 1)
        {
            ui->wind_stren->setText("中");
            QPixmap pic(":/mid");
            pic = pic.scaled(ui->label_windicon->width(), ui->label_windicon->height(), Qt::KeepAspectRatio);
            ui->label_windicon->setPixmap(pic);
        }
        else
        {
            ui->wind_stren->setText("高");
            QPixmap pic(":/high");
            pic = pic.scaled(ui->label_windicon->width(), ui->label_windicon->height(), Qt::KeepAspectRatio);
            ui->label_windicon->setPixmap(pic);
        }

        qDebug()<<a;
        out<<WIND_CHANGE<<Number<<a;
        sentPackage(message);
    }
}

void MainWindow::initial()
{
    argument.wind = wind; //初始风速大小
    argument.tem = tem;//初始温度
    argument.max_tem = max_tem;//最大温度
    argument.min_tem = min_tem;//最小温度
    argument.price = price;//当前费用
    ui->start_button->setEnabled(true);
    ui->wind_change->setCurrentIndex(wind);
    ui->tem_change->setValue(tem);
    ui->connect_mes->setText("连接成功！");
    if(model)
    {
       QPixmap pic(":/hot");
       pic = pic.scaled(ui->label_modelicon->width(), ui->label_modelicon->height(), Qt::KeepAspectRatio);
        ui->label_modelicon->setPixmap(pic);
    }
    else
    {
        QPixmap pic(":/cold");
        pic = pic.scaled(ui->label_modelicon->width(), ui->label_modelicon->height(), Qt::KeepAspectRatio);
        ui->label_modelicon->setPixmap(pic);
    }
    qDebug()<<argument.wind<< argument.tem<<argument.price;
}

//连接TCP
void MainWindow::requestNewconnect()
{
    blockSize = 0; //初始化其为0
    tcpSocket->abort(); //取消已有的连接
    tcpSocket->connectToHost(ui->lineEdit_host->text(),
                             ui->lineEdit_port->text().toInt());

    qDebug()<<"发出连接的主机："<<ui->lineEdit_host->text()<<"发出的端口号："<< ui->lineEdit_port->text().toInt();

    ui->connect->setEnabled(false);
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_6);
    out<<INI_REQ<<Number;
    qDebug()<<"message:"<<message;
    sentPackage(message);
    qDebug()<<"从机发出了初始包";
}

void MainWindow::on_connect_clicked()
{
    requestNewconnect();
}

//
void MainWindow::readFortune()
{
    QDataStream in(tcpSocket);
    QByteArray message;
    QDataStream out(&message,QIODevice::WriteOnly);
    in.setVersion(QDataStream::Qt_4_6);//设置数据流版本，这里要和服务器端相同
    int type;//判断包头
    int number;//判断返回的编号
    //int current;
    //float double_num;

    while(tcpSocket->bytesAvailable()>0)
    {
        in>>type>>number;
        qDebug()<<"收到的报头"<<type<<"收到的房间号："<<number;
        if(number==Number)
        {
            switch (type)
            {
            case INI_REQ://发连接包，不管
                break;
            case START_REQ://sent the start_up message,regardless
                break;
            case ACK_START://收到开机确认的包
                ui->start_button->setIcon(QIcon(":/on"));
                break;
            case ACK_INI://收到初始化信息
                in>>wind>>tem>>max_tem>>min_tem>>price>>model;//当前费用
                initial();
                qDebug()<<"收到了主机的初始化信息："<<wind<<QString::number(tem, 10, 2)<<max_tem<<min_tem<<price;
                break;
            case WIND_CHANGE://sent the wind_change message
                break;
            case ACK_WIND_CHANGE:
                //ui->wind_change->setCurrentText(wind);
                //qDebug()<<"接收到中央空调的确定风速"<<wind;
                break;
            case TEMP_CHANGE:
                break;
            case ACK_TEMP_CHANGE:
                //in>>tem;
                //ui->aim_tem->setText(QString::number(tem));
                //qDebug()<<"接收到中央空调的确定温度："<<tem;
                break;
            case  SHUTDOWN_REQ:
                break;
            case ACK_SHUNTDOWN:
                ui->start_button->setIcon(QIcon(":/on"));
                break;
            case UPDATE:
                in>>cu_tem>>cu_price;
                ui->current_tem->setText(QString::number(cu_tem, 10, 2));
                ui->price->setText(QString::number(cu_price));
                out<<ACK_UPDATE;
                out<<Number;
                sentPackage(message);
                break;
            case ACK_UPDATE:
                break;
            case POWER_OFF:
                ui->start_button->setIcon(QIcon(":/on"));
                out<<ACK_UPDATE;
                out<<Number;
                sentPackage(message);
                break;
            case ACK_POWER_OFF:
                break;
            }
        }
    }
}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{

    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        close();
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        close();
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        close();
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
        close();
        break;
    }

    ui->connect->setEnabled(true);
    ui->connect_mes->setText("准备连接");
    ui->lineEdit_host->clear();
    ui->lineEdit_port->clear();
    requestNewconnect();
}

void MainWindow::sentPackage(QByteArray block)
{
    tcpSocket->write(block);
}
