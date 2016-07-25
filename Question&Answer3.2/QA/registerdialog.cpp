#include "registerdialog.h"
#include "ui_registerdialog.h"
#include "totalclass.h"
#include "passwordnotmatchdialog.h"
#include "mywidget.h"
#include "inputemptydialog.h"
#include "showqadialog.h"
#include <QDialog>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QObject>


RegisterDialog::RegisterDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    QRegExp regx("[a-zA-Z0-9]+$");
    QValidator *validator=new QRegExpValidator(regx, ui->InputUserPassword);
    QValidator *validator1=new QRegExpValidator(regx, ui->ReInputUserPassword);
    ui->InputUserPassword->setToolTip(QString::fromLocal8Bit("仅限数字和英文字母"));
    ui->ReInputUserPassword->setToolTip(QString::fromLocal8Bit("仅限数字和英文字母"));
    ui->InputUserPassword->setValidator(validator);
    ui->ReInputUserPassword->setValidator(validator1);

    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);

    connect(client, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
}

RegisterDialog::~RegisterDialog()
{
    client->close();
    delete ui;
}


void RegisterDialog::on_Surebutton_clicked()
{
    QString UserIdInput, UserName, UserPasswordInput, ReUserPassword;
    UserIdInput = ui->InputUserId->text();
    UserName = ui->InputUserName->text();
    UserPasswordInput = ui->InputUserPassword->text();
    ReUserPassword = ui->ReInputUserPassword->text();
    if(UserIdInput.isEmpty() || UserName.isEmpty() ||
       UserPasswordInput.isEmpty() || ReUserPassword.isEmpty())
    {
        choice = 1;
        this->close();
        InputEmptyDialog *inp = new InputEmptyDialog();
        inp->show();
    }
    else
    {
        if(UserPasswordInput != ReUserPassword)
        {
            this->close();
            PasswordNotMatchDialog *pa = new PasswordNotMatchDialog();
            pa->show();
        }
        else
        {
            //User MainUser;
            this->sendMessage(REGISTER, UserIdInput, UserName, UserPasswordInput);
            MainUser.setUserId(UserIdInput);
            temp = UserIdInput;
            MainUser.setUserName(UserName);
            MainUser.setUserPassword(UserPasswordInput);
            UserId.push_back(UserIdInput);
            UserPassword.push_back(UserPasswordInput);
            this->close();
            ShowQADialog *sh = new ShowQADialog();
            sh->show();
        }
    }
}

void RegisterDialog::on_Nobutton_clicked()
{
    MyWidget *my = new MyWidget();
    my->show();
    this->close();
}

void RegisterDialog::error()
{
    //update UI and close
    QMessageBox::critical(this, "Error", client->errorString());
    client->close();
}


void RegisterDialog::sendMessage(int type, QString id, QString name, QString pass)
{
    QByteArray data;
    QDataStream out(&data, QIODevice::WriteOnly);
    out << type << id << name << pass;
    client->write(data);
}
