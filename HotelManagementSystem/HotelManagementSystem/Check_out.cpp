
#include "widget.h"
#include "ui_widget.h"
#include <QtSql>
#include <QtGui>


void Widget::on_moneyAddButton_clicked()
{
    dealPayPage();
    updatePayPage();
    updatePlanePage();
}

void Widget::dealPayPage()
{
    int row = ui->checkInTableWidget->currentRow();
    if (-1 == row)
    {
        QMessageBox::information(this, tr("退房管理"), tr("尚未选定房间，请先选定一个房间"));
    }
    else
    {
        QString roomno = ui->checkInTableWidget->item(row, 0)->text();
        QString checkin = ui->checkInTableWidget->item(row, 3)->text();
        int pay = ui->checkInTableWidget->item(row, 2)->text().toInt();
        int days = QDate::fromString(checkin, "yyyy-MM-dd").daysTo(QDate::currentDate());

        int totalCost = days * pay;

        QString sql = "select discount from room_t where roomno = " + roomno;
        QSqlQuery  query(sql);
        double discount;
        if(query.next())
            discount = query.value(0).toDouble();
        totalCost *= discount;
        QMessageBox::information(this, tr("退房管理"), tr("一共费用：%1").arg(totalCost));

        int peo = 0;
        for(int i = 4; i <= 6; ++i)
            if(ui->checkInTableWidget->item(row, i)->text()!="")
                peo++;

        // ## 删除顾客信息
        sql = "delete from checkin_t where roomno = " + roomno;
        query.exec(sql);

        // ## 更新房屋信息
        sql = "update room_t set status = 1 where roomno = " + roomno;
        query.exec(sql);

        sql = "update room_t set discount = 1.0 where roomno = " + roomno;
        query.exec(sql);

        // ## 更新统计信息
        sql = "select money, num_room, num_people from sum_t";
        query.exec(sql);
        int price, num_r, num_p;
        if(query.next())
        {
            price = query.value(0).toInt() + totalCost;
            num_r = query.value(1).toInt() - 1;
            num_p = query.value(2).toInt() - peo;
        }
        sql = "update sum_t set money = " + QString::number(price) + " where sid = " + QString::number(100000);
        query.exec(sql);
        sql = "update sum_t set num_room = " + QString::number(num_r) + " where sid = " + QString::number(100000);
        query.exec(sql);
        sql = "update sum_t set num_people = " + QString::number(num_p) + " where sid = " + QString::number(100000);
        query.exec(sql);
    }
}

void Widget::updatePayPage()
{
    const static QString roomTypes[4] = {tr("单人间"), tr("双人间"), tr("三人间"), tr("豪华间")};

    // ## 这里提取入住用户信息
    QString sql = "select count(distinct roomno) from checkin_t";
    QSqlQuery query(sql);
    query.next();
    ui->checkInTableWidget->setRowCount(query.value(0).toInt());

    sql = "select checkin_t.roomno, roomtype, price, checkintime, name from room_t, checkin_t "
          "where room_t.roomno = checkin_t.roomno";
    query.exec(sql);

    QList<QStringList> roomInfoList;
    while (query.next())
    {
        QString roomno = query.value(0).toString();
        QString roomtype = roomTypes[query.value(1).toInt() - 1];
        QString price = query.value(2).toString();
        QString checkin = query.value(3).toString();
        QString name = query.value(4).toString();

        bool isExist = false;
        // ## 先查询这里是否是同一房间的住客
        for (int i = 0; i < roomInfoList.size(); ++i)
        {
            if (roomInfoList[i][0] == roomno)
            {
                if(roomInfoList[i][5] == "")
                    roomInfoList[i][5] = name;
                else
                    roomInfoList[i][6] = name;
                isExist = true;
                break;
            }
        }
        if (isExist)
            continue;

        QStringList roomInfo;
        roomInfo << roomno << roomtype << price << checkin << name << "" << "";
        roomInfoList << roomInfo;
    }

    int row = 0;
    foreach (QStringList roomInfo, roomInfoList)
    {
        for (int col = 0; col < roomInfo.size(); ++col)
            ui->checkInTableWidget->setItem(row, col, new QTableWidgetItem(roomInfo[col]));
        ++row;
    }
}

