#include "widget.h"
#include "ui_widget.h"
#include <QtSql>
#include <QtGui>

void Widget::updateRoomInfoPage()
{
    const static QString roomTypes[4] = {tr("单人间"), tr("双人间"), tr("三人间"), tr("豪华间")};
    const static QString roomStatus[3] = {tr("空闲"), tr("已预订"), tr("已入住")};
    QString sql = "select roomtype, roomno, status, price from room_t";
    QSqlQuery query(sql);

    ui->roomInfoTableWidget->setRowCount(40);
    QList<QStringList> roomInfoList;

    // ## 这里提取房屋信息
    while (query.next())
    {
        QStringList roomInfo;
        roomInfo << roomTypes[query.value(0).toInt()-1]
                 << query.value(1).toString()
                 << roomStatus[query.value(2).toInt()-1]
                 << query.value(3).toString();
        roomInfoList << roomInfo;

    }

    // ## 这里提取预订用户信息
    sql = "select name, roomnos, checkintime from customer_t";
    query.exec(sql);
    while (query.next())
    {
        QStringList roomnos = query.value(1).toString().split(" ");
        foreach (QString roomno, roomnos)
        {
            for (int i = 0; i < roomInfoList.size(); ++i)
            {
                if (roomInfoList[i][1] == roomno)
                {
                    roomInfoList[i] << query.value(2).toString()
                                    << query.value(0).toString();
                }
            }
        }
    }

    // ## 这里提取入住用户信息
    sql = "select name, roomno, checkintime from checkin_t";
    query.exec(sql);
    while (query.next())
    {
        QString roomno = query.value(1).toString();
        for (int i = 0; i < roomInfoList.size(); ++i)
        {
            if (roomInfoList[i][1] == roomno)
            {
                if (roomInfoList[i].size() >=6)
                    roomInfoList[i] << query.value(0).toString();
                else
                    roomInfoList[i] << query.value(2).toString()
                                    << query.value(0).toString();
            }
        }
    }

    int row = 0;
    foreach (QStringList roomInfo, roomInfoList)
    {
        for (int col = 0; col < roomInfo.size(); ++col)
            ui->roomInfoTableWidget->setItem(row, col, new QTableWidgetItem(roomInfo[col]));
        ++row;
    }

    updateRoomInfoPage_2();
}

void Widget::on_roomInfoTableWidget_doubleClicked(const QModelIndex &index)
{
    int colum = index.column();
    // ## 最高权限可以一次性修改所有同一类型的房间价格
    if( colum == 0 && level==0 )
    {
        QString Types = index.data(0).toString();
        int price = ui->roomInfoTableWidget->item(index.row(),3)->text().toInt();
        const static QString roomTypes[4] = {tr("单人间"), tr("双人间"), tr("三人间"), tr("豪华间")};
        QString sql;
        QSqlQuery query;
        bool ok;
        for ( int i = 0; i < 4; ++i )
            if(Types.compare(roomTypes[i]) == 0)
            {
                int newprice = QInputDialog::getInteger(this,Types + tr(" 房价修改"),tr("请输入房价"),price,200,2147483647,10,&ok);
                if( ok )
                {
                    sql = QString("update room_t set price = %1 where roomtype = %2").arg(newprice).arg(i+1);
                    query.exec(sql);
                }
                break;
            }
        updateRoomInfoPage();
        return;
    }
    // ## 次高权限可以修改单个房间价格
    else if( level <=1 && (colum == 1 || colum == 3) )
    {
        QString roomno = ui->roomInfoTableWidget->item(index.row(),1)->text();
        int price = ui->roomInfoTableWidget->item(index.row(),3)->text().toInt();
        QString sql;
        QSqlQuery query;
        bool ok;
        int newprice = QInputDialog::getInteger(this,tr("房价修改"),tr("请输入房价"),price,200,2147483647,10,&ok);
        if( ok )
        {
            sql = QString("update room_t set price = %1 where roomno = %2").arg(newprice).arg(roomno);
            query.exec(sql);
        }
        updateRoomInfoPage();
        return;
    }
    else if( colum < 5)
        return;
     // ## 双击查询
    QString name = index.data(0).toString();
    QString roomno = ui->roomInfoTableWidget->item(index.row(),1)->text();
    QString sql = "select sex, id, phone, checkintime from checkin_t where name='" + name +"' and roomno=" + roomno;
    QSqlQuery query(sql);
    while( query.next())
    {
        QString sex = query.value(0).toBool() ? tr("女") : tr("男");
        QString id = query.value(1).toString();
        QString phone = query.value(2).toString();
        QString checkintime = query.value(3).toString();
        QString text = tr("姓名：") + name + tr("\n性别：") + sex + tr("\n身份证号：") + id +
                       tr("\n联系电话：") + phone + tr("\n入住时间：") + checkintime;
        QMessageBox box;
        box.setWindowTitle(tr("详细信息"));
        box.setText(text);
        box.addButton(tr("确定"), QMessageBox::AcceptRole);
        if(box.exec() == QMessageBox::AcceptRole)
        {
            return;
        }
    }
}


void Widget::on_queryButton_clicked()
{
    QString name = ui->queryLineEdit->text();
    QString sql = "select sex, id, phone, checkintime, roomno from checkin_t where name='" + name +"'";
    QSqlQuery query(sql);
    while( query.next())
    {
        QString sex = query.value(0).toBool() ? tr("女") : tr("男");
        QString id = query.value(1).toString();
        QString phone = query.value(2).toString();
        QString checkintime = query.value(3).toString();
        QString roomno = query.value(4).toString();
        QString text = tr("姓名：") + name + tr("\n性别：") + sex + tr("\n身份证号：") + id +
                tr("\n联系电话：") + phone + tr("\n入住房间：") + roomno + tr("\n入住时间：") + checkintime;
        QMessageBox box;
        box.setWindowTitle(tr("详细信息"));
        box.setText(text);
        box.addButton(tr("确定"), QMessageBox::AcceptRole);
        box.addButton(tr("下一个"),QMessageBox::RejectRole);
        if(box.exec() == QMessageBox::AcceptRole)
        {
            return;
        }
    }
    QMessageBox::information(this,tr("详细信息"),tr("查询结束"));
}



