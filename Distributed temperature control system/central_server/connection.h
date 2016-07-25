#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("Bill.db");
    if(!db.open()){
        QMessageBox::critical(0, "Cannot open database1", "Unable to establish a database connection.", QMessageBox::Cancel);
        return false;
    }

    //没有判断是否存在，如果执行失败，没有错误判断
    QSqlQuery query;
    query.exec("create table room1("
               "year int,"
               "month int,"
               "day int,"
               "hour int,"
               "minute int,"
               "second int,"
               "cur_temp double,"
               "windspeed int,"
               "temp double,"
               "statement int)");
    query.exec("create table room2("
               "year int,"
               "month int,"
               "day int,"
               "hour int,"
               "minute int,"
               "second int,"
               "cur_temp double,"
               "windspeed int,"
               "temp double,"
               "statement int)");
    query.exec("create table room3("
               "year int,"
               "month int,"
               "day int,"
               "hour int,"
               "minute int,"
               "second int,"
               "cur_temp double,"
               "windspeed int,"
               "temp double,"
               "statement int)");
    query.exec("create table room4("
               "year int,"
               "month int,"
               "day int,"
               "hour int,"
               "minute int,"
               "second int,"
               "cur_temp double,"
               "windspeed int,"
               "temp double,"
               "statement int)");
    query.exec("create table room5("
               "year int,"
               "month int,"
               "day int,"
               "hour int,"
               "minute int,"
               "second int,"
               "cur_temp double,"
               "windspeed int,"
               "temp double,"
               "statement int)");


/*    query.exec("insert into room1 values(1, 1, 1.1, 1, 1.1)");
    query.exec("insert into room1 values(2, 2, 2.1, 2, 2.1)");
    query.exec("insert into room1 values(3, 3, 3.1, 3, 3.1)");

    query.exec("insert into room2 values(4, 4, 1.1, 1, 1.1)");
    query.exec("insert into room2 values(5, 5, 2.1, 2, 2.1)");
    query.exec("insert into room2 values(6, 6, 3.1, 3, 3.1)");

    query.exec("insert into room3 values(7, 4, 1.1, 1, 1.1)");
    query.exec("insert into room3 values(8, 5, 2.1, 2, 2.1)");
    query.exec("insert into room3 values(9, 6, 3.1, 3, 3.1)");

    query.exec("insert into room4 values(10, 4, 1.1, 1, 1.1)");
    query.exec("insert into room4 values(11, 5, 2.1, 2, 2.1)");
    query.exec("insert into room4 values(12, 6, 3.1, 3, 3.1)");

    query.exec("insert into room5 values(13, 4, 1.1, 1, 1.1)");
    query.exec("insert into room5 values(14, 5, 2.1, 2, 2.1)");
    query.exec("insert into room5 values(15, 6, 3.1, 3, 3.1)");
*/
    return true;
}
#endif // CONNECTION_H
