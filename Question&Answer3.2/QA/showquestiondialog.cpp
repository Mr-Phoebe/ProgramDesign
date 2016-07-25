#include "showquestiondialog.h"
#include "ui_showquestiondialog.h"
#include "showqadialog.h"
#include "totalclass.h"
#include "showanswerdialog.h"
#include "askforquestiondialog.h"
#include "questiondetaildialog.h"
#include "finddialog.h"
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QTextCodec>
#include <QString>
#include <QPushButton>
#include <QLayout>
#include <QDebug>
#include <QLineEdit>
#include <QInputDialog>
#include <QLineEdit>
#include <algorithm>


void ShowQuestionDialog::setAllQuestion()
{
    QuestionItemList.clear();
    for(int i = 0; i < SumQuestionList.size(); i++)
    {
        QuestionItemList.push_back(i);
    }
    siz = QuestionItemList.size() - 1;
    this->sortQuestion();
}

void ShowQuestionDialog::setReqQuestion(QString need)
{
    string req = need.toStdString();
    QuestionItemList.clear();
    for(int i = 0; i < SumQuestionList.size(); i++)
    {
        string temp = SumQuestionList[i].getQuestionTitle().toStdString();
        if(temp.find(req) != string::npos)
        {
            QuestionItemList.push_back(i);
        }
    }
    siz = QuestionItemList.size() - 1;
    this->sortQuestion();
}

void ShowQuestionDialog::setTimQuestion(QDateTime bet,QDateTime ent)
{
    QuestionItemList.clear();
    for(int i = 0; i < SumQuestionList.size(); i++)
    {
        QString temp = SumQuestionList[i].getCreatTime();
        QDateTime tmp = QDateTime::fromString(temp, "yy-MM-dd hh:mm:ss");
        if(bet <= tmp && tmp <= ent)
        {
            QuestionItemList.push_back(i);
        }
    }
    siz = QuestionItemList.size() - 1;
    this->sortQuestion();
}

bool numberSort(int a, int b)
{
    return SumQuestionList[a].getAnswerNumber() < SumQuestionList[b].getAnswerNumber();
}

void ShowQuestionDialog::sortQuestion()
{
    if(ui->comboBox->currentIndex() == 0)
    {
        //按时间排序，什么也不做
    }
    else if(ui->comboBox->currentIndex() == 1)  // 按照回答问题的数目来排序
    {
        qSort(QuestionItemList.begin(), QuestionItemList.end(), numberSort);
    }
}

ShowQuestionDialog::ShowQuestionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowQuestionDialog)
{
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowMinimizeButtonHint;
    flags |= Qt::WindowMaximizeButtonHint;
    setWindowFlags(flags);
    ui->setupUi(this);
    this->resize(QSize(900,600));
    this->ui->comboBox->setCurrentIndex(0);
    this->setAllQuestion();
    this->setListwigitItem();
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(showDetail(QListWidgetItem*)));
}

ShowQuestionDialog::~ShowQuestionDialog()
{
    delete ui;
}


void ShowQuestionDialog::on_retButton_clicked()
{
    ShowQADialog *sh = new ShowQADialog();
    sh->show();
    this->close();
}

void ShowQuestionDialog::on_askquesBtn_clicked()
{
    AskForQuestionDialog *as = new AskForQuestionDialog();
    as->show();
    this->close();
}

void ShowQuestionDialog::on_nextpageButton_clicked()
{
    setListwigitItem();
}

void ShowQuestionDialog::on_lastpageButton_clicked()
{
    int x = (QuestionItemList.size()-1)/10+1;
    if(currentpage == x)
        siz += QuestionItemList.size()%10+10;
    else
        siz += 20;
    setListwigitItem();
}

void ShowQuestionDialog::setListwigitItem()
{
    ui->listWidget->clear();
    int sma = siz - 9;
    int pagenumber = (QuestionItemList.size()-1)/10+1;
    currentpage = (QuestionItemList.size()-siz)/10+1;
    QString curnum = QString::number(currentpage,10);
    QString pnum = QString::number(pagenumber,10);


    ui->pagelabel->setText(QString::fromLocal8Bit("一共有 ")+pnum
                          +QString::fromLocal8Bit(" 页,当前为第 ")+curnum
                          +QString::fromLocal8Bit(" 页"));
    if(siz == (QuestionItemList.size()-1))
        ui->lastpageButton->setEnabled(false);
    else
        ui->lastpageButton->setEnabled(true);

    if(siz <= 9)
    {
        ui->nextpageButton->setEnabled(false);
        sma = 0;
     }
    else
        ui->nextpageButton->setEnabled(true);
    if(QuestionItemList.size()!=0)
    {
         for( ; siz >= sma; siz--)
         {             
             QListWidgetItem *item = new QListWidgetItem(ui->listWidget,QuestionItemList.size()-1-siz);
             item->setSizeHint(QSize(200,60));
             QuestionDetailDialog *qu = new QuestionDetailDialog();
             ui->listWidget->setItemWidget(item,qu);
         }
     }
}
void ShowQuestionDialog::showDetail(QListWidgetItem *index)
{
    QId = QuestionItemList[QuestionItemList.size()-1-index->type()];
    ShowAnswerDialog *sh = new ShowAnswerDialog();
    sh->show();
    this->close();
}




void ShowQuestionDialog::on_searchButton_clicked()
{
    findDialog *fin = new findDialog();
    fin->show();
    this->close();
}

void ShowQuestionDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    siz = QuestionItemList.size() - 1;
    this->sortQuestion();
    this->setListwigitItem();
}
