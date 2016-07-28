#include "subqusetiondonedialog.h"
#include "ui_subqusetiondonedialog.h"
#include "showqadialog.h"
#include "showanswerdialog.h"
#include "totalclass.h"

SubQusetionDoneDialog::SubQusetionDoneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubQusetionDoneDialog)
{
    ui->setupUi(this);
}

SubQusetionDoneDialog::~SubQusetionDoneDialog()
{
    delete ui;
}

void SubQusetionDoneDialog::on_pushButton_clicked()
{
    if(choose==1)
    {
        ShowQADialog *sh=new ShowQADialog();
        sh->show();
    }
    else if(choose==2)
    {
        ShowAnswerDialog *sh=new ShowAnswerDialog();
        sh->show();
    }
    choose=0;
    this->close();

}
