#include "showanswerdialog.h"
#include "ui_showanswerdialog.h"
#include "answerquestiondialog.h"
#include "showquestiondialog.h"
#include "answerdetaildialog.h"
#include "totalclass.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QLayout>
#include <QDebug>
#include <algorithm>
int u,si;

ShowAnswerDialog::ShowAnswerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowAnswerDialog)
{
    Qt::WindowFlags flags=Qt::Dialog;
    flags |=Qt::WindowMinimizeButtonHint;
    flags |=Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);

    ui->setupUi(this);
    ui->QuestionTitlelabel->setText(QString::fromLocal8Bit("问题标题：")+SumQuestionList[QId].getQuestionTitle());
    ui->QuestionInfolabel->setText(QString::fromLocal8Bit("具体描述：")+SumQuestionList[QId].getBasicContent());
    ui->comboBox->setCurrentIndex(0);
    getFindSum(0);
 }


ShowAnswerDialog::~ShowAnswerDialog()
{
    delete ui;
}


void ShowAnswerDialog::on_AnswerButton_clicked()
{
    AnswerQuestionDialog *an = new AnswerQuestionDialog();
    an->show();
    this->close();
    AnswerItemList.clear();
    u = 0;
    si = 0;
    AId = 0;
}

void ShowAnswerDialog::on_ExitButton_clicked()
{
    this->close();
    AnswerItemList.clear();
    u = 0;
    si = 0;
    AId = 0;
    if(fochoice == 0)
    {
        if(currentpage==SumQuestionList.size()/10+1)
            siz+=SumQuestionList.size()%10;
        else
            siz+=10;
        ShowQuestionDialog *sh=new ShowQuestionDialog();
        sh->show();
    }
    else
    {
        qu=0;
        qsi=0;
        SumFocusQuestionList.clear();
        SumFocusAnswerList.clear();
        curanspage=0;
        focusquespage=0;
        this->close();
    }
}

bool praiseSort(int a,int b)
{
    return SumAnswerList[a].getPasiseNum() > SumAnswerList[b].getPasiseNum();
}

void ShowAnswerDialog::getFindSum(int flag)
{
    u=0;
    si=0;
    AId=0;
    AnswerItemList = SumQuestionList[QId].getAnswer();
    if(flag == 0)
    {
        //qSort();
        //按照时间顺序排序，即，按照原有顺序即可
    }
    else if(flag == 1)    //按照点赞数排序
    {
       qSort(AnswerItemList.begin(), AnswerItemList.end(), praiseSort);
    }
    if(AnswerItemList.size() == 0)
        curanspage=0;
    else if(AnswerItemList.size() >= 11)
        si=u+9;
    else
        si=AnswerItemList.size()-1;
    this->setListwigitItem();
}

void ShowAnswerDialog::setListwigitItem()
{
    curanspage=u/10+1;
    QString answerpage=QString::number(((AnswerItemList.size()-1)/10+1),10);
    QString curpage=QString::number(curanspage,10);

    ui->label_4->setText(QString::fromLocal8Bit("一共有")+answerpage+
                         QString::fromLocal8Bit("页，当前为第")+
                         curpage+QString::fromLocal8Bit("页"));
    if(u==0)
        ui->lastPageBtn->setEnabled(false);
    else
        ui->lastPageBtn->setEnabled(true);
    if(si==AnswerItemList.size()-1 || AnswerItemList.size()==0)
        ui->nextPageBtn->setEnabled(false);
    else
        ui->nextPageBtn->setEnabled(true);

    if(AnswerItemList.size()!=0)
         for(;u<=si;u++)
         {
             itemnumber=AnswerItemList[u];
             AId=u+1;
             //AId++;
             QListWidgetItem *item=new QListWidgetItem(ui->listWidget,u);
             item->setSizeHint(QSize(200,150));
             AnswerDetailDialog *an=new AnswerDetailDialog();
             ui->listWidget->setItemWidget(item,an);
         }
    //qDebug()<<AnswerItemList.size();
}


void ShowAnswerDialog::on_nextPageBtn_clicked()
{
    si+=10;
    //qDebug()<<AnswerItemList.size();
    if(si>=(AnswerItemList.size()-1))
    {
        si=AnswerItemList.size()-1;
    }
    ui->listWidget->clear();
    this->setListwigitItem();
}

void ShowAnswerDialog::on_lastPageBtn_clicked()
{
    u=(si/10-1)*10;
    si=u+9;
    ui->listWidget->clear();
    this->setListwigitItem();
}

void ShowAnswerDialog::on_comboBox_currentIndexChanged(int index)
{
    ui->listWidget->clear();
    AnswerItemList.clear();
    this->getFindSum(index);
}

void ShowAnswerDialog::on_listWidget_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    QString text = ui->listWidget->item(row)->text();
}
