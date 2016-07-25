#include "answerdetaildialog.h"
#include "ui_answerdetaildialog.h"
#include "totalclass.h"
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

AnswerDetailDialog::AnswerDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnswerDetailDialog)
{
    m = itemnumber;
    n = itemnumber;
    ui->setupUi(this);
    QString temp0=QString::fromLocal8Bit("回答")+QString::number(AId,10)+": \n"+SumAnswerList[itemnumber].getBasicContent();
    ui->textEdit->setText(temp0);
    ui->textEdit->setReadOnly(true);

    QString temp1=QString::fromLocal8Bit("创建者: ")+SumAnswerList[itemnumber].getCreatUserId();
    ui->label_2->setText(temp1);

    QString temp2=QString::fromLocal8Bit("创建时间: ")+SumAnswerList[itemnumber].getCreatTime();
    ui->label_3->setText(temp2);

    int a=SumAnswerList[itemnumber].getPasiseNum();
    QString temp4=QString::number(a,10);
    QString temp3=QString::fromLocal8Bit("点赞数: ")+temp4;
    ui->label_4->setText(temp3);
    ui->focusButton->setText(QString::fromLocal8Bit("关注该用户"));
    ui->praiseButton->setText(QString::fromLocal8Bit("点赞"));
    for(int j=0;j<AnswerPriseList.size();j++)
        if(AnswerPriseList[j]==itemnumber)
        {
            ui->praiseButton->setText(QString::fromLocal8Bit("已赞"));
            ui->praiseButton->setEnabled(false);
            break;
        }
    UserFocusList=MainUser.getUserFocuslist();
    if(SumAnswerList[itemnumber].getCreatUserId()==MainUser.getUserId())
        ui->focusButton->setEnabled(false);
    for(int j=0;j<UserFocusList.size();j++)
        if(UserFocusList[j]==SumAnswerList[itemnumber].getCreatUserId())
        {
             ui->focusButton->setText(QString::fromLocal8Bit("已关注该用户"));
             ui->focusButton->setEnabled(false);
             break;
        }
    connect(ui->praiseButton,SIGNAL(clicked()),this,SLOT(showDetail()));
    connect(ui->focusButton,SIGNAL(clicked()),this,SLOT(focus()));
}

AnswerDetailDialog::~AnswerDetailDialog()
{
    delete ui;
}

void AnswerDetailDialog::showDetail()
{
    int s=SumAnswerList[m].getPasiseNum()+1;
    QString praise=QString::number(s,10);
    ui->praiseButton->setText(QString::fromLocal8Bit("已赞"));
    ui->praiseButton->setEnabled(false);
    ui->label_4->setText(QString::fromLocal8Bit("点赞数: ")+praise);
    SumAnswerList[m].setPraiseNum(s);
    AnswerPriseList.push_back(m);

    for(int h=0;h<SumUserList.size();h++)
        if(SumUserList[h].getUserId()==MainUser.getUserId())
        {
            MainUser.setPriseList(AnswerPriseList);
            SumUserList[h].setPriseList(AnswerPriseList);
        }

    this->sendMessage();
}

void AnswerDetailDialog::focus()
{
    ui->focusButton->setText(QString::fromLocal8Bit("已关注该用户"));
    ui->focusButton->setEnabled(false);
    for(int i=0;i<UserFocusList.size();i++)
        if(UserFocusList[i]==SumAnswerList[n].getCreatUserId())
            return;
    UserFocusList.push_back(SumAnswerList[n].getCreatUserId());
    for(int h=0;h<SumUserList.size();h++)
        if(SumUserList[h].getUserId()==MainUser.getUserId())
        {
            MainUser.setFocuslist(UserFocusList);
            SumUserList[h].setFocuslist(UserFocusList);
        }
}

void AnswerDetailDialog::sendMessage()
{
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);

    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);

    out << ANSWER << SumAnswerList.size();
    for(int i = 0; i < SumAnswerList.size(); i++)
    {
        out << SumAnswerList[i].getBasicInfoId();
        out << SumAnswerList[i].getCreatUserId();
        out << SumAnswerList[i].getCreatTime();
        out << SumAnswerList[i].getPasiseNum();
        out << SumAnswerList[i].getBasicContent();
    }
    client->write(data);
}
