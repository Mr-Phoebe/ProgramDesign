#include "filewindow.h"
#include "taskmanager.h"
#include "ui_filewindow.h"
#include "memory.h"
#include <ctime>
#include <windows.h>
#include <qdebug.h>
extern FileSystem *fs;
extern TaskManager task;
extern int PIDcnt;
extern int curclock;
extern MemorySystem ms;
extern QString m_buffer;
extern bool hasclosed;
bool finished = false;
int fileOperation;//0无 2打开文件 3修改文件 4保存文件 5关闭文件
fileWindow::fileWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fileWindow)
{
   ui->setupUi(this);

    this->setWindowTitle("文件资源管理器");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    //显示初始化当前路径
    ui->lineEdit_2->setText(QString::fromStdString(fs->getCurPath().c_str()));

    //设置目录表头
    goodsModel = new QStandardItemModel(0, 5,this);

    ui->treeView->setColumnWidth(0, 50);
    ui->treeView->setColumnWidth(1, 200);
    ui->treeView->setColumnWidth(2, 200);
    ui->treeView->setColumnWidth(3, 200);
    ui->treeView->setColumnWidth(4, 200);
    goodsModel->setHeaderData(0, Qt::Horizontal, tr("名称"));
    goodsModel->setHeaderData(1, Qt::Horizontal, tr("修改日期"));
    goodsModel->setHeaderData(2, Qt::Horizontal, tr("类型"));
    goodsModel->setHeaderData(3, Qt::Horizontal, tr("大小"));
    goodsModel->setHeaderData(4, Qt::Horizontal, tr("权限"));

    ui->treeView->setModel(goodsModel);
    ui->treeView->expandAll();
    ui->treeView->setStyleSheet("background-color:rgb(255, 255, 191)");

    //设置错误报告
    ui->label_4->setStyleSheet("color:red");

    //构建目录
    goodsModel->appendRow(this->printTree(1));
    goodsModel->appendRow(this->printTree(2));

    ui->treeView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //显示物理块占用情况
    ui->textEdit->setText(fs->op_showBlock());
    ui->textEdit_2->setText(ms.op_show_m());
    ui->textEdit_3->setText(ms.op_show_vm());
    ui->textEdit_4->setText(m_buffer);

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(run()));
    timer->start(1000);
}
//DFS构建目录
QList<QStandardItem *> fileWindow::printTree(int id)
{
    FileIndexElement current = fs->getfileindex().index[id];
    QList<QStandardItem *> items;

    QStandardItem *name = new QStandardItem(QString::fromStdString(current.fileName));
    items.push_back(name);

    QStandardItem *time = new QStandardItem(QString(QLatin1String(current.fcb->lastModTime)));
    items.push_back(time);

    if(current.fcb->ftype == dir)
    {
        QStandardItem *type = new QStandardItem(QString("目录"));
        items.push_back(type);
        QStandardItem *size = new QStandardItem(QString(""));
        items.push_back(size);
    }
    else
    {
        QStandardItem *type = new QStandardItem(QString("文件"));
        items.push_back(type);
        QStandardItem *size = new QStandardItem(QString::number(current.fcb->flen));
        items.push_back(size);
    }

    if(current.fcb->facc == readOnly || current.fileName == "catalog.ini")
    {
        QStandardItem *access = new QStandardItem(QString("只读"));
        items.push_back(access);
    }
    else
    {
        QStandardItem *access = new QStandardItem(QString("可写"));
        items.push_back(access);
    }

    for(int i = 0; i < current.child.size(); i++)
    {
        QList<QStandardItem *> childs = printTree(current.child[i]);

        items.at(0)->appendRow(childs);
    }

    return items;
}

fileWindow::~fileWindow()
{
    delete ui;
}

void fileWindow::on_pushButton_clicked()
{
    string command = ui->lineEdit->text().split(QRegExp("\\s+"))[0].toStdString();//命令关键字

    if (command == "cd")
    {
        task.createPCB(PIDcnt, curclock, 10);
    }
    else if (command == "md" || command == "mkdir")
    {
        task.createPCB(PIDcnt, curclock, 1);
    }
    else if (command == "mkfile")
    {
        task.createPCB(PIDcnt, curclock, 1);
    }
    else if (command == "rd" || command == "rmdir")
    {
        task.createPCB(PIDcnt, curclock, 7);
    }
    else if (command == "del")
    {
        task.createPCB(PIDcnt, curclock, 6);
    }
    else if (command == "rename" || command == "ren")
    {
        task.createPCB(PIDcnt, curclock, 8);
    }
    else if (command == "attrib")
    {
        task.createPCB(PIDcnt, curclock, 9);
    }
    else
    {
        task.createPCB(PIDcnt, curclock, 11);
    }
    ui->lineEdit->setEnabled(false);
    ui->pushButton->setEnabled(false);
}

void fileWindow::run()
{
    qDebug()<<"run filewindow start!";
    QString tmp = ui->lineEdit->text();
    //qDebug()<<"&&"<<tmp;
    QStringList input = tmp.split(QRegExp("\\s+"));//命令按空格分割后列表
    if(input.length() > 0)
    {
        //qDebug() << input[0];
    }
    string command = ui->lineEdit->text().split(QRegExp("\\s+"))[0].toStdString();//命令关键字
    string logPath;//日志用
    QString report;//错误报告

    if(finished)
    {
        if (command == "cd")
        {
            report = fs->op_cd(logPath, input);
            if (report == "")
            {
                fs->log("cd", logPath);
            }
            ui->label_4->setText(report);
        }
        else if (command == "md" || command == "mkdir")
        {
            report = fs->op_mk(logPath, input, dir);
            if (report == "")
            {
                fs->log("mkdir", logPath);
            }
            ui->label_4->setText(report);
        }
        else if (command == "mkfile")
        {
            report = fs->op_mk(logPath, input, file);
            if (report == "")
            {
                fs->log("mkdir", logPath);
            }
            ui->label_4->setText(report);
        }
        else if (command == "rd" || command == "rmdir")
        {
            report = fs->op_rmdir(logPath, input);
            if (report == "")
            {
                fs->log("rmdir", logPath);
            }
            ui->label_4->setText(report);
        }
        else if (command == "del")
        {
            report = fs->op_delfile(logPath, input);
            if (report == "")
            {
                fs->log("del", logPath);
            }
            ui->label_4->setText(report);
        }
        else if (command == "rename" || command == "ren")
        {
            report = fs->op_rename(logPath, input);
            if (report == "")
            {
                fs->log("rename", logPath);
            }
            ui->label_4->setText(report);
        }
        else if (command == "attrib")
        {
            report = fs->op_alterAttrib(logPath, input);
            if (report == "")
            {
                fs->log("alter_attribute", logPath);
            }
            ui->label_4->setText(report);
        }


        else
        {
            if(fileOperation == 2)
            {
                qDebug() << "打开文件";
                report = fs->op_openFile(logPath, input);
                if(report == "")
                {
                    this->close();
                    fileOperation = 3;
                    task.createPCB(PIDcnt, curclock, 3);
                }
                else
                {
                    fileOperation = 0;
                    ui->label_4->setText(report);
                }
            }
            else if(fileOperation == 3)
            {
                //TODO:
                task.createPCB(PIDcnt, curclock, 3);
                fileOperation = 3;
            }
            else if(fileOperation == 4)
            {
                //TODO:
                //task.createPCB(PIDcnt, curclock, 3);
                fileOperation = 3;
            }
            else if(fileOperation == 5)
            {
                //TODO:
                //qDebug()<< "123456";
                //fileOperation = 0;
            }
            else
                ui->label_4->setText("命令格式错误！");
        }
        fs->save();

        ui->lineEdit_2->setText(QString::fromStdString(fs->getCurPath().c_str()));
        ui->textEdit->setText(fs->op_showBlock());
        //ui->textEdit_2->setText(ms);

        goodsModel->removeRows(0, goodsModel->rowCount());
        goodsModel->appendRow(this->printTree(1));
        goodsModel->appendRow(this->printTree(2));
	ui->treeView->expandAll();
        ui->lineEdit->clear();

        ui->lineEdit->setEnabled(true);
        ui->pushButton->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
        finished = false;
    }
    qDebug()<<"this is swaping, show me !"<<endl;
    qDebug()<<m_buffer;
    ui->textEdit_2->setText(ms.op_show_m());
    ui->textEdit_3->setText(ms.op_show_vm());
    ui->textEdit_4->setText(m_buffer);
    m_buffer="";
    
}

void fileWindow::on_pushButton_2_clicked()
{
    string logPath;

    fs->log("exit", logPath);

    this->close();

    hasclosed = 1;
}

void fileWindow::on_pushButton_3_clicked()
{
    ui->pushButton_3->setEnabled(false);

    fileOperation = 2;
    task.createPCB(PIDcnt, curclock, 2);
    qDebug() << "!!!!!";
}



void fileWindow::on_lineEdit_destroyed()
{

}

QString fileWindow::getFilePathFromUI()
{
    return ui->lineEdit->text();
}
