#include "widget.h"
#include "ui_widget.h"
#include <QtSql>
#include <QtGui>
#include <QMessageBox>

// ## 退出按钮
void Widget::on_Exit_clicked()
{
     qApp->quit();
}

// ## 关于按钮
void Widget::on_About_clicked()
{
    QMessageBox::about(this, tr("关于酒店管理系统"),
                           tr("<h2>酒店管理系统 2.8 </h2>"
                           "<p>酒店管理系统由2013211303班02组编写。"
                           "组员：吴浩男，钟克难，金东赫，周杰。"
                           "由Mr.Phoebe Coding Studio提供后续服务："
                           "http://blog.csdn.net/u013007900</p>"));
}

// ## 统计按钮
void Widget::on_Statistics_clicked()
{
    QString sql = "select money, num_room, num_people from sum_t";
    QSqlQuery query(sql);
    int price, num_r, num_p;
    if(query.next())
    {
        price = query.value(0).toInt();
        num_r = query.value(1).toInt();
        num_p = query.value(2).toInt();
    }
    QMessageBox::information(this, tr("酒店管理统计系统"),tr("总收入：%1\n现使用房间数：%2\n现入住人数：%3")
                             .arg(price).arg(num_r).arg(num_p));

}


// ## 退出账号按钮
void Widget::on_ExitID_clicked()
{
    initLoginPage();
    initMainPage();
}

void Widget::updatePlanePage()
{
    showplane.updatePlanePage();
}


void Widget::on_Display_clicked()
{
    showplane.showPlanePage();
}


