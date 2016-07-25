#include "mainwindow.h"
#include <QApplication>

//测试时使用数据
int wind = 0;//初始风速大小
double tem = 17;//初始温度
int max_tem = 25;//最大温度
int min_tem = 15;//最小温度
double price = 2;//当前费用
int model = 0;
int flag = 0;//the condition is running
int signal_com = 1;

double cu_price;
double cu_tem;

parameter argument;
//start up the programme and inital the slave condition

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
