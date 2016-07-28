#include "askforquestiondialog.h"
#include "ui_askforquestiondialog.h"
#include "showqadialog.h"
#include "subqusetiondonedialog.h"
#include "inputemptydialog.h"
#include "totalclass.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>


AskForQuestionDialog::AskForQuestionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AskForQuestionDialog)
{
    ui->setupUi(this);
}

AskForQuestionDialog::~AskForQuestionDialog()
{
    delete ui;
}

void AskForQuestionDialog::on_pushButton_clicked()
{
    ShowQADialog *sh=new ShowQADialog();
    sh->show();
    this->close();
}

void AskForQuestionDialog::on_SubmitButton_clicked()
{
    QString InputQuestionTitle,InputQuestionContent,CurrentTime;
    InputQuestionTitle=ui->QusetionEdit->text();
    InputQuestionContent=ui->QuestionInfoEdit->toPlainText();
    //qDebug()<<InputQuestionTitle;
    //qDebug()<<InputQuestionContent;
    if(InputQuestionTitle.isEmpty())
    {
        choice=3;
        this->close();
        InputEmptyDialog *in = new InputEmptyDialog();
        in->show();
    }
    else
    {
        //Question QuestionReadyToAdd;
        QDateTime time=QDateTime::currentDateTime();
        CurrentTime=time.toString("yy-MM-dd hh:mm:ss");
        QuestionReadyToAdd.setQuestionTitle(InputQuestionTitle);
        QuestionReadyToAdd.setCreatUserId(temp);
        QuestionReadyToAdd.setQuestionTitle(InputQuestionTitle);
        QuestionReadyToAdd.setBasicContent(InputQuestionContent);
        QuestionReadyToAdd.setCreatTime(CurrentTime);
        QuestionReadyToAdd.setBasicInfoId(SumQuestionList.size()+1);

        SumQuestionList.push_back(QuestionReadyToAdd);
        this->sendMessage(QuestionReadyToAdd);

        choose=1;
        SubQusetionDoneDialog *su=new SubQusetionDoneDialog();
        su->show();
        this->close();
    }
}

void AskForQuestionDialog::sendMessage(Question QuestionReadyToAdd)
{
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);

    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << QUESTION;
    out << QuestionReadyToAdd.getBasicInfoId();
    out << QuestionReadyToAdd.getCreatUserId();
    out << QuestionReadyToAdd.getCreatTime();
    out << QuestionReadyToAdd.getQuestionTitle();
    out << QuestionReadyToAdd.getBasicContent();
    client->write(data);
}
