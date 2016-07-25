#include "logindialog.h"
#include "ui_logindialog.h"
#include "idorpasswordnotmatchdialog.h"
#include "totalclass.h"
#include "mywidget.h"
#include "inputemptydialog.h"
#include "showqadialog.h"
#include <QDebug>
#include <QString>
#include <QFile>
#include <QTextCodec>
#include <QMessageBox>
#include <QObject>


LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);
    connect(client,SIGNAL(readyRead()),this,SLOT(readServer()));
}

LoginDialog::~LoginDialog()
{
    client->close();
    delete client;
    delete ui;
}

void LoginDialog::readServer()
{
    QByteArray datagram;
    datagram.resize(client->size());
    client->read(datagram.data(),datagram.size());
    QDataStream in(&datagram,QIODevice::ReadOnly);
    int type, num;
    in >> type >> num;
    this->log(num);
}

void LoginDialog::on_Surebutton_clicked()
{
    QString UserIdInput,UserPassword;
    UserIdInput = ui->InputUserId->text();
    UserPassword = ui->InputUserPassword->text();
    if(UserIdInput.isEmpty() || UserPassword.isEmpty())
    {
        choice = 2;
        client->close();
        this->close();
        InputEmptyDialog *in = new InputEmptyDialog();
        in->show();
    }
    else
    {
        this->sendMessage(LOGIN, UserIdInput, UserPassword);
    }
}

void LoginDialog::on_Nobutton_clicked()
{
    MyWidget *my = new MyWidget();
    my->show();
    client->close();
    this->close();
}

void LoginDialog::sendMessage(int type, QString name, QString pass)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << type << name << pass;
    client->write(data);
}

void LoginDialog::log(int j)
{
    if(j == -1)
    {
        IdOrPasswordNotMatchDialog *id = new IdOrPasswordNotMatchDialog();
        id->show();
    }
    else
    {
        MainUser = SumUserList[j];
        AnswerPriseList = SumUserList[j].getAnswerPriseList();
        UserFocusList = SumUserList[j].getUserFocuslist();

        temp = ui->InputUserId->text();
        ShowQADialog *sh = new ShowQADialog();
        sh->show();
    }
    client->close();
    this->close();
}
