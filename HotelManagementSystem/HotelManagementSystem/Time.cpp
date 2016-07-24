#include "widget.h"
#include "ui_widget.h"
#include <QtSql>
#include <QtGui>

void Widget::updateTime()
{
    ti=ti.addSecs(1);
    ui->dateTimeEdit->setDate(thedate);
    ui->dateTimeEdit->setTime(ti);
}

void Widget::initTime()
{
    QString sql = "select thedate, thetime from time_t";
    QSqlQuery query;
    query.exec(sql);
    while(query.next())
    {
        thedate = QDate::fromString(query.value(0).toString(),"yyyy-MM-dd");
        ti = QTime::fromString(query.value(1).toString(),"hh:mm:ss");
    }
    ack = new QTimer;
    connect(ack,SIGNAL(timeout()), this, SLOT(updateTime()));
    ack->start(10);
}
