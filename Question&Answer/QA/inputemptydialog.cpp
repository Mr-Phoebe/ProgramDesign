#include "inputemptydialog.h"
#include "ui_inputemptydialog.h"
#include "registerdialog.h"
#include "logindialog.h"
#include "totalclass.h"
#include "askforquestiondialog.h"
#include "answerquestiondialog.h"
#include <QDebug>

InputEmptyDialog::InputEmptyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputEmptyDialog)
{
    ui->setupUi(this);
}

InputEmptyDialog::~InputEmptyDialog()
{
    delete ui;
}

void InputEmptyDialog::on_pushButton_clicked()
{
    if(choice==1)
    {
        RegisterDialog *re=new RegisterDialog();
        re->show();
    }
    else if(choice==2)
    {
        LoginDialog *ln=new LoginDialog();
        ln->show();
    }
    else  if(choice==3)
    {
        AskForQuestionDialog *as=new AskForQuestionDialog();
        as->show();
    }
    else if(choice==4)
    {
        AnswerQuestionDialog *an=new AnswerQuestionDialog();
        an->show();
    }
    choice=0;
    this->close();
}
