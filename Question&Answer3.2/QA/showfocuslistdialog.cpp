#include "showfocuslistdialog.h"
#include "ui_showfocuslistdialog.h"
#include "showqadialog.h"
#include "totalclass.h"
#include "focusdetaildialog.h"
#include <QDebug>
#include <string>

ShowFocusListDialog::ShowFocusListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowFocusListDialog)
{
    ui->setupUi(this);
    for(int i=0;i<UserFocusList.size();i++)
    {
        QListWidgetItem *item=new QListWidgetItem(ui->listWidget,i);
        item->setSizeHint(QSize(100,60));
        item->setText(QString::fromLocal8Bit("用户名：")+UserFocusList[i]);
        ui->listWidget->addItem(item);
    }
}

ShowFocusListDialog::~ShowFocusListDialog()
{
    delete ui;
}

void ShowFocusListDialog::on_ReturnButton_clicked()
{
    ShowQADialog *sho=new ShowQADialog();
    sho->show();
    this->close();
}



void ShowFocusListDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)    //展示详细的信息
{
    QString tmpqname = item->text();
    string tmpname = tmpqname.toStdString();
    tmpname = tmpname.substr(12);         //12表示前面的“用户名：”这几个字符
    QString name = QString::fromStdString(tmpname);
    focusDetailDialog *foc = new focusDetailDialog();
    foc->setFocusName(name);
    foc->show();
    this->close();
}
