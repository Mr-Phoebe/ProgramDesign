#include "focusdetaildialog.h"
#include "ui_focusdetaildialog.h"
#include <QDebug>
#include <QMessageBox>
#include "totalclass.h"
#include "showfocuslistdialog.h"

focusDetailDialog::focusDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::focusDetailDialog)
{
    ui->setupUi(this);
}

focusDetailDialog::~focusDetailDialog()
{
    delete model;
    delete model2;
    delete ui;
}

void focusDetailDialog::setFocusName(const QString &focusname)
{
    this->focusname = focusname;
    this->updateAnswer();
    this->updateQuesiton();
}

void focusDetailDialog::updateAnswer()
{
    ui->namelabel->setText(focusname);
    AnswerItemList.clear();
    for(itemnumber=SumAnswerList.size()-1; itemnumber>=0; itemnumber--)
    {
        if(focusname.compare(SumAnswerList[itemnumber].getCreatUserId()) == 0)
            AnswerItemList.push_back(itemnumber);
    }

    unique(AnswerItemList.begin(),AnswerItemList.end());

    model = new QStandardItemModel();

    //设置大小

    model->setColumnCount(3);    //列
    model->setRowCount(AnswerItemList.size());    //行
    //设置标题
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("问题ID"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("创建时间"));
    model->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("回答内容"));
    //添加数据
    for(int i = 0; i < AnswerItemList.size(); i++)
    {
        int pos = AnswerItemList[i];
        //设置字符内容
        model->setItem(i,0,new QStandardItem(QString::number(SumAnswerList[pos].getBasicInfoId())));
        //设置字符颜色
        model->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
        //设置字符位置
        model->item(i,0)->setTextAlignment(Qt::AlignCenter);

        model->setItem(i,1,new QStandardItem(SumAnswerList[pos].getCreatTime()));

        model->setItem(i,2,new QStandardItem(SumAnswerList[pos].getBasicContent()));
     }

    //选择这个model

    ui->detailtableView->setModel(model);

    //隐藏左边那列
    ui->detailtableView->verticalHeader()->hide();

    ui->detailtableView->resizeColumnsToContents();
    ui->detailtableView->resizeRowsToContents();
    ui->detailtableView->setColumnWidth(2,180);
    ui->detailtableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void focusDetailDialog::updateQuesiton()
{
    ui->namelabel2->setText(focusname);
    QuestionItemList.clear();
    for(itemnumber = SumQuestionList.size()-1; itemnumber >= 0; itemnumber--)
    {
        if(focusname.compare(SumQuestionList[itemnumber].getCreatUserId()) == 0)
            QuestionItemList.push_back(itemnumber);
    }

    unique(QuestionItemList.begin(),QuestionItemList.end());

    model2 = new QStandardItemModel();

    //设置大小

    model2->setColumnCount(4);    //列
    model2->setRowCount(QuestionItemList.size());    //行
    //设置标题
    model2->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("问题ID"));
    model2->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("创建时间"));
    model2->setHeaderData(2,Qt::Horizontal,QString::fromLocal8Bit("问题标题"));
    model2->setHeaderData(3,Qt::Horizontal,QString::fromLocal8Bit("问题内容"));
    //添加数据
    for(int i = 0; i < QuestionItemList.size(); i++)
    {
        int pos = QuestionItemList[i];
        //设置字符内容
        model2->setItem(i,0,new QStandardItem(QString::number(SumQuestionList[pos].getBasicInfoId())));
        //设置字符颜色
        model2->item(i,0)->setForeground(QBrush(QColor(255, 0, 0)));
        //设置字符位置
        model2->item(i,0)->setTextAlignment(Qt::AlignCenter);

        model2->setItem(i,1,new QStandardItem(SumQuestionList[pos].getCreatTime()));

        model2->setItem(i,2,new QStandardItem(SumQuestionList[pos].getQuestionTitle()));

        model2->setItem(i,3,new QStandardItem(SumQuestionList[pos].getBasicContent()));
     }

    //选择这个model

    ui->detailtableView2->setModel(model2);

    //隐藏左边那列
    ui->detailtableView2->verticalHeader()->hide();

    ui->detailtableView2->resizeColumnsToContents();
    ui->detailtableView2->resizeRowsToContents();
    ui->detailtableView2->setColumnWidth(2,180);
    ui->detailtableView2->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void focusDetailDialog::showFocusName()
{
    qDebug()<<this->focusname;
}


void focusDetailDialog::on_BackpushButton_clicked()
{

    ShowFocusListDialog *sho = new ShowFocusListDialog();
    AnswerItemList.clear();
    AId = 0;
    sho->show();
    this->close();
}

void focusDetailDialog::on_detailtableView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    QString text = model->item(row,2)->text();

    QMessageBox::information(NULL,
                             QString::fromLocal8Bit("回答详情"),
                             text, QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
}

void focusDetailDialog::on_detailtableView2_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

    QString title = model2->item(row,2)->text();
    QString text = model2->item(row,3)->text();

    QMessageBox::information(NULL,
                             title,
                             text, QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
}

void focusDetailDialog::on_BackpushButton2_clicked()
{

    ShowFocusListDialog *sho = new ShowFocusListDialog();

    QuestionItemList.clear();
    AId = 0;
    sho->show();
    this->close();
}
