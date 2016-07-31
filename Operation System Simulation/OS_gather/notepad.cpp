#include "notepad.h"
#include "ui_notepad.h"
#include "taskmanager.h"
#include "filewindow.h"
#include <qdebug.h>
#include <QLabel>
extern int fileOperation;
extern int curclock;
extern TaskManager task;
extern int PIDcnt;
extern Notepad *np;
fileWindow *f;

Notepad::Notepad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Notepad)
{
    ui->setupUi(this);

    this->setWindowTitle("文件窗口");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::showFile(QString content, FileAccess facc)
{
    qDebug() << "!!!!";
    ui->textEdit->setText(content);
    if(facc == readOnly)
    {
        ui->textEdit->setEnabled(false);
        ui->pushButton->setVisible(false);
    }
    this->show();
}

void Notepad::on_pushButton_clicked()
{
    if(ui->textEdit->toPlainText().size() >= maxLen)
    {
        QLabel *l = new QLabel();

        l->setText("字数超过限制，最多64个字！");
        l->show();
    }
    else
    {
        if(fileOperation == 3)
        {
            fileOperation = 4;
            task.createPCB(PIDcnt, curclock, 4);
        }
    }
}

void Notepad::on_pushButton_2_clicked()
{
    if(fileOperation == 3)
    {
        //TODO:i don't know whether it works
        np->hide();
        //np->close();
        delete f;
        f = new fileWindow;
        f->show();
        fileOperation = 5;
        task.createPCB(PIDcnt, curclock, 5);
    }
}

QString Notepad::getFileContent()
{
    QString tmp = ui->textEdit->toPlainText();
    qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << tmp.length();
    return tmp;
}

QString Notepad::getFilePath()
{
    return filePath;
}

void Notepad::setPath(string path)
{
    QString tmp = QString::fromStdString(path);
    this->filePath = tmp;
}
