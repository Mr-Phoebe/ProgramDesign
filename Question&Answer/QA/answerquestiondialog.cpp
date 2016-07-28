#include "answerquestiondialog.h"
#include "ui_answerquestiondialog.h"
#include "showanswerdialog.h"
#include "totalclass.h"
#include "subqusetiondonedialog.h"
#include "inputemptydialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDateTime>


AnswerQuestionDialog::AnswerQuestionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnswerQuestionDialog)
{
    ui->setupUi(this);
    ui->QuestionTitlelabel->setText(QString::fromLocal8Bit("问题标题：")+SumQuestionList[QId].getQuestionTitle());
    ui->QuestionInfolabel->setText(QString::fromLocal8Bit("附加描述：")+SumQuestionList[QId].getBasicContent());
}

AnswerQuestionDialog::~AnswerQuestionDialog()
{
    delete ui;
}


void AnswerQuestionDialog::on_ReturnButton_clicked()
{
    ShowAnswerDialog *sh=new ShowAnswerDialog();
    sh->show();
    this->close();
}

void AnswerQuestionDialog::on_SubmitButton_clicked()
{
    QDateTime time = QDateTime::currentDateTime();
    QString CurrentTime = time.toString("yy-MM-dd hh:mm:ss");
    QString answer = ui->textEdit->toPlainText().replace(QString("\n"),QString(""));
    if(answer != NULL)
    {
        Answersubmit.setPraiseNum(0);
        Answersubmit.setCreatTime(CurrentTime);
        Answersubmit.setCreatUserId(temp);
        Answersubmit.setBasicInfoId(QId);
        Answersubmit.setBasicContent(answer);
        SumAnswerList.push_back(Answersubmit);
        SumQuestionList[QId].addAnswer(SumAnswerList.size()-1);

        this->sendMessage(Answersubmit);

        choose=2;
        SubQusetionDoneDialog *su = new SubQusetionDoneDialog();
        su->show();
        this->close();
   }
   else
   {
       choice=4;
       InputEmptyDialog *in = new InputEmptyDialog();
       this->close();
       in->show();
   }
}

void AnswerQuestionDialog::on_ClearButton_clicked()
{
    ui->textEdit->setText("");
}

void AnswerQuestionDialog::sendMessage(Answer Answersubmit)
{
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);

    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << ANSWERADD;
    out << Answersubmit.getBasicInfoId();
    out << Answersubmit.getCreatUserId();
    out << Answersubmit.getCreatTime();
    out << Answersubmit.getPasiseNum();
    out << Answersubmit.getBasicContent();

    client->write(data);
}
