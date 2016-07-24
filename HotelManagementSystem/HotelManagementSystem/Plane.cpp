#include "plane.h"
#include "ui_plane.h"
#include <Qtsql>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QFont>

plane::plane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::plane)
{
    ui->setupUi(this);
    ui->gridLayout->setSpacing(3);
    ui->gridLayout->setMargin(3);
    this->setWindowIcon(QIcon(":res/icon.png"));
    this->setWindowTitle(tr("旅馆平面展示图"));
}

plane::~plane()
{
    delete ui;
}

// ## 更新平面界面
void plane::updatePlanePage()
{
    QString sql = "select roomno, status from room_t";
    QSqlQuery query(sql);
    int cnt = 0;
    static int num = 0;
    QLayoutItem *child;
    while((child = ui->gridLayout->takeAt(0)) != 0)
    {
        delete child->widget();
        delete child;
    }
    num++;
    while(query.next())
    {
        QString roomno = query.value(0).toString();
        int status = query.value(1).toInt()-1;
        QLabel *lable = new QLabel();
        QPixmap *pmap1 = new QPixmap(":showback");
        QPixmap *pmap2 = new QPixmap(":peopleback");
        QPainter *painters = new QPainter;
        if(status == 0) // 空闲状态
        {
            painters->begin(pmap1);
            painters->setPen(Qt::black);
            painters->drawText(15,5,30,20,Qt::AlignCenter,roomno);
            painters->end();
            lable->setPixmap(*pmap1);
        }
        else if(status == 1) // 预定状态
        {
            painters->begin(pmap1);
            painters->setPen(Qt::red);
            painters->drawText(15,5,30,20,Qt::AlignCenter,roomno);
            painters->end();
            lable->setPixmap(*pmap1);
        }
        else                // 入住状态
        {
            painters->begin(pmap2);
            painters->setPen(Qt::black);
            painters->drawText(15,5,30,20,Qt::AlignCenter,roomno);
            painters->end();
            lable->setPixmap(*pmap2);
        }
        ui->gridLayout->addWidget(lable,cnt/5,cnt%5);
        cnt ++;
    }
}

// ## 展示平面界面
void plane::showPlanePage()
{
    this->show();
}
