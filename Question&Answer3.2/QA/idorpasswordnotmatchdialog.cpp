#include "idorpasswordnotmatchdialog.h"
#include "ui_idorpasswordnotmatchdialog.h"
#include "logindialog.h"

IdOrPasswordNotMatchDialog::IdOrPasswordNotMatchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IdOrPasswordNotMatchDialog)
{
    ui->setupUi(this);
}

IdOrPasswordNotMatchDialog::~IdOrPasswordNotMatchDialog()
{
    delete ui;
}

void IdOrPasswordNotMatchDialog::on_pushButton_clicked()
{
    LoginDialog *lo=new LoginDialog();
    lo->show();
    this->close();
}
