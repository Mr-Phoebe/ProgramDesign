#include "mywidget.h"
#include "ui_mywidget.h"
#include "registerdialog.h"
#include "logindialog.h"
#include <QDialog>
#include <QMessageBox>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);
    connect(client, SIGNAL(readyRead()), this, SLOT(readServer()));
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));

    getQuestionInfo();
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::getQuestionInfo()
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << INITQUE;
    client->write(data);
}

void MyWidget::getAnswerInfo()
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << INITANS;
    client->write(data);
}

void MyWidget::getUserInfo()
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << INITUSER;
    client->write(data);
}

void MyWidget::on_RegisterButton_clicked()
{
    RegisterDialog *re = new RegisterDialog();
    re->show();
    this->close();
}

void MyWidget::on_LoginButton_clicked()
{
    LoginDialog *lo = new LoginDialog();
    lo->show();
    this->close();
}

void MyWidget::readServer()
{
    if(client->bytesAvailable() < sizeof(quint16))
    {
        return;
    }
    quint16 nextBlockSize = 0;
    QByteArray datagram;
    datagram.resize(sizeof(quint16));
    client->read(datagram.data(),datagram.size());
    QDataStream tin(&datagram, QIODevice::ReadOnly);
    tin >> nextBlockSize;

    datagram.resize(nextBlockSize);
    client->read(datagram.data(),datagram.size());
    QDataStream in(&datagram, QIODevice::ReadOnly);
    int type, size;
    in >> type;
    switch(type)
    {
    case INITQUE:
        in >> size;
        SumQuestionList.clear();
        for(int i = 0; i < size; i++)
        {
            Question QuestionReadyToAdd;
            int basicInf;
            QString userId, creatTime, questionTitle, basicCon;
            in >> basicInf;
            in >> userId;
            in >> creatTime;
            in >> questionTitle;
            in >> basicCon;
            QuestionReadyToAdd.setBasicInfoId(basicInf);
            QuestionReadyToAdd.setCreatUserId(userId);
            QuestionReadyToAdd.setCreatTime(creatTime);
            QuestionReadyToAdd.setQuestionTitle(questionTitle);
            QuestionReadyToAdd.setBasicContent(basicCon);

            SumQuestionList.push_back(QuestionReadyToAdd);
        }
        this->getAnswerInfo();
        break;
    case INITANS:
        in >> size;
        SumAnswerList.clear();
        for(int i = 0; i < size; i++)
        {
            Answer AnswertoSubmit;
            int basicInf, prasizeNum;
            QString userId, creatTime, basicCon;
            in >> basicInf;
            in >> userId;
            in >> creatTime;
            in >> prasizeNum;
            in >> basicCon;
            AnswertoSubmit.setBasicInfoId(basicInf);
            AnswertoSubmit.setCreatUserId(userId);
            AnswertoSubmit.setCreatTime(creatTime);
            AnswertoSubmit.setPraiseNum(prasizeNum);
            AnswertoSubmit.setBasicContent(basicCon);

            SumAnswerList.push_back(AnswertoSubmit);
            SumQuestionList[AnswertoSubmit.getBasicInfoId()].addAnswer(SumAnswerList.size()-1);
        }
        this->getUserInfo();
        break;
    case INITUSER:
        in >> size;
        SumUserList.clear();
        UserId.clear();
        UserPassword.clear();
        for(int i = 0; i < size; i++)
        {
            User tmpUser;
            QString sid, sname, spass, sfocus;
            int num;
            in >> sid;
            in >> sname;
            in >> spass;
            in >> num;
            UserId.push_back(sid);
            UserPassword.push_back(spass);
            tmpUser.setUserId(sid);
            tmpUser.setUserName(sname);
            tmpUser.setUserPassword(spass);
            for(int j = 0; j < num; j++)
            {
                in >> sfocus;
                tmpUser.setUserFocuslist(sfocus);
            }
            SumUserList.push_back(tmpUser);
        }
        break;
    }
}

void MyWidget::error()
{
    //update UI and close
    QMessageBox::critical(this, "Error", client->errorString());
    client->close();
    this->close();
}
