#include "widget.h"
#include "ui_widget.h"
#include <QtSql>
#include <QtGui>
#include <QDebug>

void Widget::updateRoomInfoPage_2()
{
    if( level != 0 )    return;
    const static QString roomTypes[4] = {tr("单人间"), tr("双人间"), tr("三人间"), tr("豪华间")};
    const static QString roomStatus[3] = {tr("空闲"), tr("已预订"), tr("已入住")};
    QString sql = "select roomtype, roomno, status, price from room_t";
    QSqlQuery query(sql);

    ui->roomInfoTableWidget_2->setRowCount(40);
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

    int row = 0;
    foreach (QStringList roomInfo, roomInfoList)
    {
        for (int col = 0; col < roomInfo.size(); ++col)
            ui->roomInfoTableWidget_2->setItem(row, col, new QTableWidgetItem(roomInfo[col]));
        ++row;
    }
}

void Widget::updateUsersInfoPage()
{
    if( level != 0 )    return;
    QString sql = "select username, password, level from login_t";
    QSqlQuery query(sql);

    //QByteArray ba(sql.toAscii());
    //qWarning("%s",ba.data());

    QList<QStringList> userInfoList;

    int row = 0;
    // ## 这里提取登陆信息
    while (query.next())
    {
        QStringList userInfo;
        userInfo << query.value(0).toString()
                 << query.value(1).toString()
                 << query.value(2).toString();
        userInfoList << userInfo;
        //QByteArray ba(userInfo[0].toAscii());
        //qWarning("%d %s",row,ba.data());
        row++;
    }

    ui->UsersInfoTableWidget->setRowCount(row);

    row = 0;
    foreach (QStringList userInfo, userInfoList)
    {
        for (int col = 0; col < userInfo.size(); ++col)
            ui->UsersInfoTableWidget->setItem(row, col, new QTableWidgetItem(userInfo[col]));
        ++row;
    }
}

void Widget::resetSetPage()
{
    ui->PricelineEdit->clear();
    ui->NamelineEdit->clear();
    ui->PassWordlineEdit->clear();
    ui->LevelcomboBox->setCurrentIndex(0);
    ui->RoomcomboBox->setCurrentIndex(0);

    ui->NamelineEdit->setReadOnly(false);
    ui->PassWordlineEdit->setReadOnly(false);
    ui->LevelcomboBox->setEnabled(true);

    ui->UsersButton->setEnabled(true);
    ui->DeleteUsersButton->setEnabled(false);

    // ## 从数据库中获取信息，更新界面
    updateRoomInfoPage_2();
    updateUsersInfoPage();
}

void Widget::on_RoomButton_clicked()
{
    int row = ui->RoomcomboBox->currentIndex()+1;
    QString newprice = ui->PricelineEdit->text();
    QString sql = QString("update room_t set price = %1 where roomtype = %2").arg(newprice).arg(row);
    QSqlQuery query(sql);
    query.next();
    resetSetPage();
}



void Widget::on_RoombackButton_clicked()
{
    const static int price[4] = {240,220,270,360};

    QString sql;
    QSqlQuery query;

    for(int i = 0; i < 4; ++i )
    {
        sql = QString("update room_t set price = %1 where roomtype = %2").arg(price[i]).arg(i+1);
        query.exec(sql);
    }
    resetSetPage();
}



void Widget::on_UsersButton_clicked()
{
    QString name = ui->NamelineEdit->text();
    QString password = ui->PassWordlineEdit->text();
    int limits = ui->LevelcomboBox->currentIndex();

    QSqlQuery query;
    QString sql = QString("insert into login_t values(null,'%1', '%2', %3)").arg(name).arg(password).arg(limits);
    query.exec(sql);

    resetSetPage();
}

// ## 进入数据库中删除此条数据
void Widget::on_DeleteUsersButton_clicked()
{
    QString name = ui->NamelineEdit->text();
    QString sql = QString("delete from login_t where username = '%1'").arg(name);
    QByteArray aa(sql.toAscii());
    QSqlQuery query;

     // ## 这里应该是必定找得到
    if (query.next())
    {
        query.exec(sql);
        return;
    }
    else
    {
        Q_ASSERT(false);
    }
    resetSetPage();
}

void Widget::on_UsersInfoTableWidget_cellDoubleClicked(int row, int column)
{
    ui->UsersButton->setEnabled(false);
    ui->DeleteUsersButton->setEnabled(true);
    ui->NamelineEdit->setReadOnly(true);
    ui->NamelineEdit->setReadOnly(true);
    ui->LevelcomboBox->setEnabled(false);

    QString name = ui->UsersInfoTableWidget->item(row,0)->text();
    QString password = ui->UsersInfoTableWidget->item(row,1)->text();
    int limits = ui->UsersInfoTableWidget->item(row,2)->text().toInt();

    ui->NamelineEdit->setText(name);
    ui->PassWordlineEdit->setText(password);
    ui->LevelcomboBox->setCurrentIndex(limits);
}


void Widget::on_UsersInfoTableWidget_pressed(const QModelIndex &index)
{
    resetSetPage();
}

