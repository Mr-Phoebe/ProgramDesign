#include "log_dialog.h"
#include "ui_log_dialog.h"
#include <QFile>
#include <QDebug>

extern int roomnum;

log_Dialog::log_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::log_Dialog)
{
    ui->setupUi(this);
    QString tmp_str;
    QFile log_file("log"+tmp_str.number(roomnum)+".txt");
    if(!log_file.open(QIODevice::ReadOnly))
    {
        qDebug()<<"cannot open log_file: "<<log_file.errorString();
    }
    QTextStream fin(&log_file);
    QString message = "\0";
    while(!fin.atEnd())
    {
        QString tmp_str;
        fin>>tmp_str;
        message += tmp_str + "\t";
    }
    ui->log_text->setText(message);
}

log_Dialog::~log_Dialog()
{
    delete ui;
}

