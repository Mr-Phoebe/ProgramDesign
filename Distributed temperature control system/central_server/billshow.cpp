#include "billshow.h"
#include "ui_billshow.h"
#include "connection.h"
#include "mainwindow.h"
#include <QDebug>
#include <QFile>

extern int Smodel;
extern int roomnum;
extern int power[6];
extern int windtime[6];
extern int temptime[6];
extern int powertime[6];
extern int dispatchtime[6];
extern int year;
extern int month;
extern int day;
extern int hour;
extern int minute;
extern int second;
extern void DataTimeToEvery();
extern double price;
const int windprice[3] = {4, 5, 6};

double getFileEndNumber(QString FileName)
{
    QFile inputfile(FileName);
    if(!inputfile.open(QIODevice::ReadOnly))
    {
        qDebug()<<"open file faild: "<<inputfile.errorString()<<endl;
    }
    QTextStream fin(&inputfile);
    QString Num;
    double res = 0;
    double tmpnum=0;
    while(!fin.atEnd())//这里是因为文件末尾有个空字符，最后一个读入是那个空字符，而log文件的倒数第二个数据才是目前总收入；
    {
        res = tmpnum;
        fin>>Num;
        tmpnum = Num.toDouble();
        qDebug()<<"tmp: "<<Num<<" "<<Num.toDouble()<<endl;
    }
    inputfile.close();
    return res;
}

Billshow::Billshow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Billshow)
{
    ui->setupUi(this);
    //ui->textBrowser->setText("year    month    day    hour    minute    second  cur_temp  wind  temp  cur_pay   \n");

    QString total_str = "\0", str_temp = "\0";
    total_str=getBillString();
    ui->textBrowser->setText(total_str);

}

QString Billshow::getBillString()
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
    float cur_temp = 0;
    int wind = 0;
    float temp = 0;



    QString total_str = "\0", str_temp = "\0";
    total_str = "date\t\tcur_temp\twind\ttemprture\tcur_pay\n";
    //打开对应报表
    QSqlQuery query;
    if(1<= roomnum && roomnum <= 5)
    {
        QString sql = "select * from room" + QString::number(roomnum);
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
            cur_temp = query.value(6).toFloat();
            wind = query.value(7).toInt();
            temp = query.value(8).toFloat();

            if(pre_year > 2000)
                cur_pay = ((cur_year - pre_year) * 8760.0 + (cur_month - pre_month) * 720.0 + (cur_day - pre_day) * 24.0 +(cur_hour - pre_hour)
                           + (cur_minute - pre_minute)/60.0 + (cur_second - pre_second)/3600.0) * windprice[wind] * (1.1 + 0.1 * Smodel) * price;

            total_pay += cur_pay;

            qDebug()<<cur_year<<" "<<cur_month<<" "<<cur_day<<" "<<cur_hour<<" "<<cur_minute<<" "<<cur_second;
            qDebug()<<cur_pay<<total_pay;
            if(cur_year > 2000)
            {
                str_temp = str_temp.number(cur_year, 10);
                total_str += str_temp;
                total_str += "-";
                str_temp = str_temp.number(cur_month, 10);
                total_str += str_temp;
                total_str += "-";
                str_temp = str_temp.number(cur_day, 10);
                total_str += str_temp;
                total_str += " ";
                str_temp = str_temp.number(cur_hour, 10);
                total_str += str_temp;
                total_str += ":";
                str_temp = str_temp.number(cur_minute, 10);
                total_str += str_temp;
                total_str += ":";
                str_temp = str_temp.number(cur_second, 10);
                total_str += str_temp;
                total_str += "\t";
                str_temp = str_temp.number(cur_temp, 10, 2);
                total_str += str_temp;
                total_str += "\t";
                str_temp = str_temp.number(wind, 10);
                total_str += str_temp;
                total_str += "\t";
                str_temp = str_temp.number(temp, 10, 2);
                total_str += str_temp;
                total_str += "\t";
                str_temp = str_temp.number(cur_pay, 1, 2);
                total_str += str_temp;
                total_str += "\n";
            }
            qDebug()<<total_str;
            //qDebug()<<query.value(0).toInt()<<query.value(1).toInt()<<query.value(2).toFloat()<<query.value(3).toInt()<<query.value(4).toFloat();

        }
        DataTimeToEvery();
        if(cur_year > 0)
            total_pay += ((year - cur_year) * 8760.0 + (month - cur_month) * 720.0 + (day - cur_day) * 24.0
                          +(hour - cur_hour) + (minute - cur_minute)/60 + (second - cur_second)/3600.0)
                            * windprice[wind] * (1.1 + 0.1 * Smodel) * price;


        total_str += "wind change times = ";
        str_temp = str_temp.number(windtime[roomnum]);
        total_str += str_temp + "\n";
        total_str += "temperature change times = ";
        str_temp = str_temp.number(temptime[roomnum]);
        total_str += str_temp + "\n";
        total_str += "tunr on/off times = ";
        str_temp = str_temp.number(powertime[roomnum]);
        total_str += str_temp + "\n";
        total_str += "dispatch times = ";
        str_temp = str_temp.number(dispatchtime[roomnum]);
        total_str += str_temp + "\n";
        total_str += "total pay = ";
        str_temp = str_temp.number(total_pay);
        total_str += str_temp;
    }
    return total_str+"\n";
}

QString Billshow::getLogString(double pre_income = 0)
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
    float cur_temp = 0;
    int wind = 0;
    int statement = 0;
    float temp = 0;

    QString total_str="\0", str_temp="\0";

    //打开对应报表
    QSqlQuery query;
    if(1<= roomnum && roomnum <= 5)
    {
        QString sql = "select * from room" + QString::number(roomnum);
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
            cur_temp = query.value(6).toFloat();
            temp = query.value(8).toFloat();

            if(pre_year > 2000 && statement)
                cur_pay = ((cur_year - pre_year) * 8760.0 + (cur_month - pre_month) * 720.0 + (cur_day - pre_day) * 24.0 +(cur_hour - pre_hour)
                           + (cur_minute - pre_minute)/60.0 + (cur_second - pre_second)/3600.0)
                            * windprice[wind] * (1.1 + 0.1 * Smodel) * price;

            wind = query.value(7).toInt();
            statement = query.value(8).toInt();
            total_pay += cur_pay;

            qDebug()<<cur_year<<" "<<cur_month<<" "<<cur_day<<" "<<cur_hour<<" "<<cur_minute<<" "<<cur_second;
            qDebug()<<cur_pay<<total_pay;
        }
        if(cur_year > 0 && power[roomnum])
            total_pay += ((year - cur_year) * 8760.0 + (month - cur_month) * 720.0 + (day - cur_day) * 24.0
                          +(hour - cur_hour) + (minute - cur_minute)/60.0 + (second - cur_second)/3600.0)
                            * windprice[wind] * (1.1 + 0.1 * Smodel) * price;

        total_str = "dateTime: "+str_temp.number(cur_year)+"-"+str_temp.number(cur_month)+"-"+str_temp.number(cur_day)+" "+str_temp.number(cur_hour)
                +":"+str_temp.number(cur_minute)+":"+str_temp.number(cur_second)+"\t"//时间
                +"RoomNo: "+str_temp.number(roomnum)+"\t"//房间号
                +"pay: "+str_temp.number(total_pay)+"\t"//本次收入
                +"total_income: "+str_temp.number(total_pay+pre_income);//酒店总收入
    }
    else
    {
        qDebug()<<"出错，请重新输入房间号码！";
        QMessageBox::critical(this,"Error2","Please input correct room_num!",QMessageBox::Ignore);
        return "\0";
    }
    return total_str+"\n";
}
void Billshow::deleteTheTable()
{
    if(1<= roomnum && roomnum <=5)
    {
        QString sql = "delete from room" + QString::number(roomnum) + " where year > 0";
        QSqlQuery query(sql);
    }

}

Billshow::~Billshow()
{
    delete ui;
}

void Billshow::writeToLog()
{
    QString logFileName = "log"+QString::number(roomnum)+".txt";
    double pre_income = getFileEndNumber(logFileName);
    qDebug()<<"preincome="<<pre_income;
    QFile logFile(logFileName);
    if(!logFile.open(QIODevice::Append))
    {
        qDebug()<<"cannot open log bill!\n"<<logFile.errorString()<<endl;
        close();
        return;
    }
    QTextStream out1(&logFile);
    QString logMessage = getLogString(pre_income);
    out1<<logMessage;
    logFile.close();
    qDebug()<<"print log succeed!"<<endl;
    deleteTheTable();
}

void Billshow::on_pushButton_clicked()
{
    //打印账单
    //QString billFileName = "roomFile"+QString::number(roomnum)+".txt";
    QFile billFile("bill.txt");
    if(!billFile.open(QIODevice::WriteOnly))
    {
        qDebug()<<"cannot open print bill!\n"<<billFile.error()<<endl<<billFile.errorString()<<endl;
        close();
        return;
    }
    QTextStream out(&billFile);
    out<<"roomNo: "<<roomnum<<endl<<getBillString()<<endl;
    qDebug()<<"print bill succeed!"<<endl;
    billFile.close();
    writeToLog();
    close();

}

void Billshow::on_pushButton_2_clicked()
{
    writeToLog();
    close();
}
