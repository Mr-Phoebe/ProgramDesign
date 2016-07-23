#include "widget.h"
#include "ui_widget.h"
#include <QtSql>
#include <QtGui>
#include <QDialog>

bool Widget::ExecuteUpdateRoomTable(const QString& roomno, const int& status)
{

    QMessageBox box;
    box.setWindowTitle(tr("入住管理"));
    box.setIcon(QMessageBox::Information);
    box.setText(tr("是否设置折扣"));
    box.addButton(tr("确定"), QMessageBox::AcceptRole);
    box.addButton(tr("取消"),QMessageBox::RejectRole);
    if(box.exec() == QMessageBox::AcceptRole)
    {
        bool ok = false;
        double discount = QInputDialog::getDouble(this,tr("入住管理"),tr("请输入折扣"),1.0,0.5,1.0,2,&ok);

        if (ok)
        {
            QSqlQuery query;
            QString sql = QString("update room_t set status = %1 where roomno = %2").arg(status).arg(roomno);
            query.exec(sql);
            sql = QString("update room_t set discount = %1 where roomno = %2").arg(discount).arg(roomno);
            query.exec(sql);
        }
        else
            return true;
        return false;
    }
    else
    {
        QSqlQuery query;
        QString sql = QString("update room_t set status = %1 where roomno = %2").arg(status).arg(roomno);
        query.exec(sql);
        return false;
    }
    return false;
}

void Widget::ExecuteUpdateStatistic(const int peo)
{
    QString sql = "select money, num_room, num_people from sum_t";
    QSqlQuery query(sql);
    int price, num_r, num_p;
    if(query.next())
    {
        price = query.value(0).toInt();
        num_r = query.value(1).toInt() + 1;
        num_p = query.value(2).toInt() + peo;
    }
    sql = "update sum_t set money = " + QString::number(price) + " where sid = " + QString::number(100000);
    query.exec(sql);
    sql = "update sum_t set num_room = " + QString::number(num_r) + " where sid = " + QString::number(100000);
    query.exec(sql);
    sql = "update sum_t set num_people = " + QString::number(num_p) + " where sid = " + QString::number(100000);
    query.exec(sql);
}


void Widget::ExecuteUpdateCheckInTable(const QString& name,
                               const int& sex,
                               const QString& id,
                               const QString& phone,
                               const QString& roomno)
{
    QSqlQuery query;
    QString sql = QString("insert into checkin_t values(null,'%1', %2, '%3', '%4', '%5', date())").arg(name)
                  .arg(sex).arg(id).arg(phone).arg(roomno);
    query.exec(sql);
}

bool Widget::isValidCheckInCustomer(const QString& name, const QString& id, const QString& phone)//检测输入的用户信息是否合法
{
    if (!name.isEmpty() && id.length() == 18 && phone.length() == 11)                            //身份证以及电话号码长度
        return true;
    return false;
}

bool Widget::isEmptyCheckInCustomer(const QString& name, const QString& id, const QString& phone)//检测输入的用户信息是否为空
{
    if (name.isEmpty() && id.isEmpty() && phone.isEmpty())
        return true;
    return false;
}

// ## 处理入住情况
void Widget::dealCheckInPage()
{
    QString name = ui->cnameLineEdit_2->text();
    QString name2 = ui->cnameLineEdit_3->text();
    QString name3 = ui->cnameLineEdit_4->text();
    int sex = ui->cmaleRadioButton_2->isChecked() ? 0 : 1;
    int sex2 = ui->cmaleRadioButton_3->isChecked() ? 0 : 1;
    int sex3 = ui->cmaleRadioButton_4->isChecked() ? 0 : 1;
    QString id = ui->cidLineEdit_2->text();
    QString id2 = ui->cidLineEdit_3->text();
    QString id3 = ui->cidLineEdit_4->text();
    QString phone = ui->cphoneLineEdit_2->text();
    QString phone2 = ui->cphoneLineEdit_3->text();
    QString phone3 = ui->cphoneLineEdit_4->text();

    QTableWidgetItem * item = ui->roomTableWidget->currentItem();   //根据选定房间信息的位置来进行计算
    if (item == NULL)
    {
        QMessageBox::information(this, tr("入住管理"), tr("没有选定入住的房间"));
    }
    else
    {
        QString roomno = item->text();
        if (item->column() == 0)
        {
            if (isValidCheckInCustomer(name, id, phone))
            {
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name, sex, id, phone, roomno);
                ExecuteUpdateStatistic(1);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else
            {
                QMessageBox::information(this, tr("入住管理"), tr("用户信息不完整"));
            }

        }
        else if (item->column() == 1 || item->column() == 3)
        {
            if (isValidCheckInCustomer(name, id, phone) && isEmptyCheckInCustomer(name2, id2, phone2))
            {
                // ## 这里即一个人住2人间
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name, sex, id, phone, roomno);
                ExecuteUpdateStatistic(1);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else if (isEmptyCheckInCustomer(name, id, phone) && isValidCheckInCustomer(name2, id2, phone2))
            {
                // ## 这里即一个人住2人间
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name2, sex2, id2, phone2, roomno);
                ExecuteUpdateStatistic(1);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else if (isValidCheckInCustomer(name, id, phone) && isValidCheckInCustomer(name2, id2, phone2))
            {
                // ## 这里即住满2个人
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name, sex, id, phone, roomno);
                ExecuteUpdateCheckInTable(name2, sex2, id2, phone2, roomno);
                ExecuteUpdateStatistic(2);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else
            {
                QMessageBox::information(this, tr("入住管理"), tr("用户信息不完整"));
            }

        }
        else if (item->column() == 2)
        {
            bool validCustomer1 = isValidCheckInCustomer(name, id, phone);
            bool validCustomer2 = isValidCheckInCustomer(name2, id2, phone2);
            bool validCustomer3 = isValidCheckInCustomer(name3, id3, phone3);
            bool emptyCustomer1 = isEmptyCheckInCustomer(name, id, phone);
            bool emptyCustomer2 = isEmptyCheckInCustomer(name2, id2, phone2);
            bool emptyCustomer3 = isEmptyCheckInCustomer(name3, id3, phone3);

            if (validCustomer1 && emptyCustomer2 && emptyCustomer3)
            {
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name, sex, id, phone, roomno);
                ExecuteUpdateStatistic(1);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else if (emptyCustomer1 && validCustomer2 && emptyCustomer3)
            {
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name2, sex2, id2, phone2, roomno);
                ExecuteUpdateStatistic(1);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else if (emptyCustomer1 && emptyCustomer2 && validCustomer3)
            {
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name3, sex3, id3, phone3, roomno);
                ExecuteUpdateStatistic(1);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else if (validCustomer1 && validCustomer2 && emptyCustomer3)
            {
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name, sex, id, phone, roomno);
                ExecuteUpdateCheckInTable(name2, sex2, id2, phone2, roomno);
                ExecuteUpdateStatistic(2);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else if (validCustomer1 && emptyCustomer2 && validCustomer3)
            {
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name, sex, id, phone, roomno);
                ExecuteUpdateCheckInTable(name3, sex3, id3, phone3, roomno);
                ExecuteUpdateStatistic(2);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else if (emptyCustomer1 && validCustomer2 && validCustomer3)
            {
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name2, sex2, id2, phone2, roomno);
                ExecuteUpdateCheckInTable(name3, sex3, id3, phone3, roomno);
                ExecuteUpdateStatistic(2);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else if (validCustomer1 && validCustomer2 && validCustomer3)
            {
                while(ExecuteUpdateRoomTable(roomno, 3)){};
                ExecuteUpdateCheckInTable(name, sex, id, phone, roomno);
                ExecuteUpdateCheckInTable(name2, sex2, id2, phone2, roomno);
                ExecuteUpdateCheckInTable(name3, sex3, id3, phone3, roomno);
                ExecuteUpdateStatistic(3);
                QMessageBox::information(this, tr("入住管理"), tr("提交成功"));
            }
            else
            {
                QMessageBox::information(this, tr("入住管理"), tr("用户信息不完整"));
            }

        }
    }
}


// ## 这里根据所选的列来决定激活几块面板
void Widget::processCheckInCustomer(int , int col)
{
    if (col == 0)
    {
        ui->customerGroupBox_3->setVisible(false);
        ui->customerGroupBox_4->setVisible(false);
    }
    else if (col == 1 || col == 3)
    {
        ui->customerGroupBox_3->setVisible(true);
        ui->customerGroupBox_4->setVisible(false);

        ui->cnameLineEdit_3->clear();
        ui->cmaleRadioButton_3->setChecked(true);
        ui->cidLineEdit_3->clear();
        ui->cphoneLineEdit_3->clear();
        ui->ccheckintimeDateEdit_3->setDate(QDate::currentDate());
    }
    else
    {
        ui->customerGroupBox_3->setVisible(true);
        ui->customerGroupBox_4->setVisible(true);

        ui->cnameLineEdit_4->clear();
        ui->cmaleRadioButton_4->setChecked(true);
        ui->cidLineEdit_4->clear();
        ui->cphoneLineEdit_4->clear();
        ui->ccheckintimeDateEdit_4->setDate(QDate::currentDate());
    }
}

void Widget::resetCheckInPage()
{
    ui->cnameLineEdit_2->clear();
    ui->cnameLineEdit_3->clear();
    ui->cnameLineEdit_4->clear();
    ui->cmaleRadioButton_2->setChecked(true);
    ui->cmaleRadioButton_3->setChecked(true);
    ui->cmaleRadioButton_4->setChecked(true);
    ui->cidLineEdit_2->clear();
    ui->cidLineEdit_3->clear();
    ui->cidLineEdit_4->clear();
    ui->cphoneLineEdit_2->clear();
    ui->cphoneLineEdit_3->clear();
    ui->cphoneLineEdit_4->clear();
    ui->ccheckintimeDateEdit_2->setDate(QDate::currentDate());
    ui->ccheckintimeDateEdit_3->setDate(QDate::currentDate());
    ui->ccheckintimeDateEdit_4->setDate(QDate::currentDate());
}

void Widget::updateCheckInPage()
{
    ui->roomTableWidget->clear();

    // ## 查询最多一列的房屋行数
    QString sql = "select count(*) from room_t where status = 1 group by roomtype";
    QSqlQuery query(sql);

    int maxRow = 0;
    while (query.next())
    {
        int roomcount = query.value(0).toInt();
        if (maxRow < roomcount)
            maxRow = roomcount;
    }
    ui->roomTableWidget->setRowCount(maxRow);

    // ## 查询可供预定的房屋总数
    sql = "select roomno, roomtype from room_t where status = 1";
    query.exec(sql);

    int r1 = 0, r2 = 0, r3 = 0 , r4 = 0;
    while (query.next())
    {
        QString roomno = query.value(0).toString();
        int roomtype = query.value(1).toInt() - 1;
        if (roomtype == 0)
            ui->roomTableWidget->setItem(r1++, roomtype, new QTableWidgetItem(roomno));
        else if (roomtype == 1)
            ui->roomTableWidget->setItem(r2++, roomtype, new QTableWidgetItem(roomno));
        else if (roomtype == 2)
            ui->roomTableWidget->setItem(r3++, roomtype, new QTableWidgetItem(roomno));
        else
            ui->roomTableWidget->setItem(r4++, roomtype, new QTableWidgetItem(roomno));
    }

    // ## 设置列名
    QStringList lables;
    lables << tr("单人间(￥240)") << tr("双人间(￥220)") << tr("三人间(￥270)") << tr("豪华间(￥360)");
    ui->roomTableWidget->setHorizontalHeaderLabels(lables);
}


void Widget::on_commitButton_2_clicked()
{
    dealCheckInPage();
    resetCheckInPage();
    updateCheckInPage();
    updatePlanePage();
}
