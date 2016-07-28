#include "showqadialog.h"
#include "ui_showqadialog.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "totalclass.h"
#include "mywidget.h"
#include "showquestiondialog.h"
#include "askforquestiondialog.h"
#include "showfocuslistdialog.h"

ShowQADialog::ShowQADialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowQADialog)
{
    ui->setupUi(this);
    ui->label->setText(QString::fromLocal8Bit("欢迎来到问答系统,") + temp);
}

ShowQADialog::~ShowQADialog()
{
    delete ui;
}

void ShowQADialog::on_ExitButton_clicked()//退出按钮操作
{
    MyWidget *my = new MyWidget();
    my->show();
    this->close();
    UserFocusList.clear();
    AnswerPriseList.clear();
}

void ShowQADialog::on_LookoverQButton_clicked()//查看问题按钮操作
{

    if(SumQuestionList.size()!=0)
    {
        currentpage = 0;
        ShowQuestionDialog *sh = new ShowQuestionDialog();
        sh->show();
        this->close();
    }
    else
    {
         QMessageBox::critical(NULL, QString::fromLocal8Bit("提示"),
                               QString::fromLocal8Bit("暂时没有问题，快去提问吧"));
    }
}

void ShowQADialog::on_AskQButton_clicked()// 提问操作
{
    AskForQuestionDialog *as = new AskForQuestionDialog();
    as->show();
    this->close();
}

void ShowQADialog::on_LookFocusBtn_clicked()// 查看关注操作
{
    ShowFocusListDialog *sh = new ShowFocusListDialog();
    sh->show();
    this->close();
}
