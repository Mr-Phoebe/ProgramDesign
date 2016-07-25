#include "finddialog.h"
#include "ui_finddialog.h"
#include "showquestiondialog.h"
#include <QDebug>

findDialog::findDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findDialog)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateTimeEdit2->setDateTime(QDateTime::currentDateTime());
    ui->keyradioButton->setChecked(true);
    ui->timeradioButton->setChecked(false);
    ui->dateTimeEdit->setEnabled(false);
    ui->dateTimeEdit2->setEnabled(false);
    ui->lineEdit->setEnabled(true);
}

findDialog::~findDialog()
{
    delete ui;
}



void findDialog::on_buttonBox_accepted()
{
    ShowQuestionDialog *sho = new ShowQuestionDialog();
    if(ui->keyradioButton->isChecked())
    {
        QString text = ui->lineEdit->text();
        sho->setReqQuestion(text);
        sho->setListwigitItem();
    }
    else if(ui->timeradioButton->isChecked())
    {
        QString time = ui->dateTimeEdit->dateTime().toString("yy-MM-dd hh:mm:ss");
        QDateTime begTime = QDateTime::fromString(time, "yy-MM-dd hh:mm:ss");
        time = ui->dateTimeEdit2->dateTime().toString("yy-MM-dd hh:mm:ss");
        QDateTime endTime = QDateTime::fromString(time, "yy-MM-dd hh:mm:ss");
        if(begTime > endTime)
        {
            delete sho;
            ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
            ui->dateTimeEdit2->setDateTime(QDateTime::currentDateTime());
            return;
        }
        sho->setTimQuestion(begTime, endTime);
        sho->setListwigitItem();
    }
    sho->show();
}

void findDialog::on_buttonBox_rejected()
{
    ShowQuestionDialog *sho = new ShowQuestionDialog();
    sho->show();
}

void findDialog::on_keyradioButton_clicked()
{
    ui->timeradioButton->setChecked(false);
    ui->dateTimeEdit->setEnabled(false);
    ui->dateTimeEdit2->setEnabled(false);
    ui->lineEdit->setEnabled(true);
}

void findDialog::on_timeradioButton_clicked()
{
    ui->keyradioButton->setChecked(false);
    ui->lineEdit->setEnabled(false);
    ui->dateTimeEdit->setEnabled(true);
    ui->dateTimeEdit2->setEnabled(true);
}
