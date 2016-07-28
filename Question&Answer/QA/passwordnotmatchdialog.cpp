#include "passwordnotmatchdialog.h"
#include "ui_passwordnotmatchdialog.h"
#include "registerdialog.h"

PasswordNotMatchDialog::PasswordNotMatchDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PasswordNotMatchDialog)
{
    ui->setupUi(this);
}

PasswordNotMatchDialog::~PasswordNotMatchDialog()
{
    delete ui;
}

void PasswordNotMatchDialog::on_pushButton_clicked()
{
    RegisterDialog *re=new RegisterDialog();
    re->show();
    this->close();
}
