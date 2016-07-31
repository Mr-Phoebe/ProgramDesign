#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "process.h"
#include "taskManager.h"
#include <ctime>
#include <cstdlib>
#include <QStandardItemModel>
#include <QTextCodec>
#include "filewindow.h"
#include <QDebug>
#include "memory.h"
#include "m_allocator.h"
#include "m_tracker.h"
PCB cpuPCB;
PCB ioPCB;
TaskManager task;
int PIDcnt;
int curclock;
bool hasclosed = 1;
extern bool finished;
enum strategy curStrategy ;
extern int fileOperation;
extern fileWindow *f;
extern  m_allocator *m_allo;
extern m_tracker m_trac;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("任务管理器");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit_3);
    ui->lineEdit_3->setValidator(validator);

    curStrategy = FCFS;

    /*
    PCB *pTemp = new PCB[7];
    for(int i = 1; i < 8; i++)
    {
        int randomTime = rand()%10 + 1;
        int randomCpuTime = rand()%10 + 1;
        while(randomTime < randomCpuTime)
        {
            randomCpuTime = rand()%10 + 1;
        }
        int randomIoTime = randomTime - randomCpuTime;
        int randomPriority = rand()%5 + 1;
        pTemp[i].initPCB(i, i + 1, ready, randomTime, randomPriority, randomCpuTime, randomIoTime, 1, 0);
        if(pTemp[i].getPID()!=0)
        {
            m_allo->alloc(pTemp[i],1);
           //Allocator(pTemp[i],1);
           // qDebug()<<pTemp[i].getPID();
        }
        task.readyList.push_back(pTemp[i]);
    }

    PIDcnt = 8;
    curclock = 8;
    cpuPCB = task.readyList.front();


    task.readyList.pop_front();
    ui->progressBar->setRange(0, cpuPCB.getCPUTime());
    this->processCPU = cpuPCB.getCPUTime();
    */
    PIDcnt = 1;
    curclock = 0;
    ui->progressBar->setRange(0, 1);
    ui->progressBar->setValue(0);
    ui->progressBar_2->setRange(0, 1);
    ui->progressBar_2->setValue(0);


    cpuPCB.setState(-1);

    if(!task.waitingList.empty())
    {
        ioPCB = task.waitingList.front();
        task.waitingList.pop_front();
    }
    else
    {
        ioPCB.setState(-1);
        this->processIO = 0;
        //ui->progressBar_2->setRange(0, 0);
    }

    CPUmodel = new QStandardItemModel();//添加表头
    char* cpuHead[] = {"PID", "到达时间", "CPU时间", "优先级", "资源页数", "执行操作"};
    this->initTable(CPUmodel, cpuHead, 6);
    IOmodel = new QStandardItemModel();//添加表头
    char* ioHead[] = {"PID", "到达时间", "IO时间", "资源页数", "执行操作"};
    this->initTable(IOmodel, ioHead, 5);


    ui->tableView->setModel(CPUmodel);
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setItemDelegate(new Delegate);
    ui->tableView->setStyleSheet("background-color:rgb(255, 255, 191)");

    ui->tableView_2->setModel(IOmodel);
    ui->tableView_2->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView_2->verticalHeader()->hide();
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_2->setItemDelegate(new Delegate);
    ui->tableView_2->setStyleSheet("background-color:rgb(255, 255, 191)");

    //updateReadyTable();
    //updateWaitingTable();


    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(run()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTable(QStandardItemModel *model, char* headline[], int count)
{
    model->setColumnCount(count);
    for(int i = 0; i < count; i++)
    {
        model->setHeaderData(i, Qt::Horizontal, headline[i]);
    }
}

void MainWindow::run()
{
    qDebug()<<"run main start";
    if(cpuPCB.getState() != -1)
    {
        if(cpuPCB.getCPUTime() > 0)
        {
            cpuPCB.setCPUTime(cpuPCB.getCPUTime() - 1);
            //cpuPCB.setTimeNeeded(cpuPCB.getTimeNeeded() - 1);
        }

        if(cpuPCB.getCPUTime() == 0 || curStrategy == RR)
        {
            if(cpuPCB.getCPUTime() == 0 && cpuPCB.getOperation() != 0)
            {
                finished = true;
                qDebug() << "123";
            }
            task.selectStrategy(curStrategy);
            this->processCPU = cpuPCB.getTimeNeeded() - cpuPCB.getIOTime();
            ui->progressBar->setRange(0, this->processCPU - 1);
        }
    }


    if(ioPCB.getIOTime() > 0)
    {
        ioPCB.setIOTime(ioPCB.getIOTime() - 1);
        //ioPCB.setTimeNeeded(ioPCB.getTimeNeeded() - 1);
    }

    if(ioPCB.getIOTime() == 0)
    {
        task.IOStrategy();
        if(ioPCB.getState() != -1)
        {
            this->processIO = ioPCB.getIOTime();
            ui->progressBar_2->setRange(0, this->processIO - 1);
        }
        else
        {
            ui->progressBar_2->setRange(0, 1);
        }
    }

    updateReadyTable();
    updateWaitingTable();

    ui->lcdNumber->display(curclock);
    ui->label_6->setVisible(false);
    curclock++;
}

void MainWindow::updateReadyTable()
{
    CPUmodel->removeRows(0,CPUmodel->rowCount());
    ui->lineEdit->clear();
    ui->progressBar->setValue(0);

    if(cpuPCB.getState() != -1)
    {
        ui->progressBar->setValue(this->processCPU - cpuPCB.getCPUTime());
        QString temp = "";
        //temp = "进程（" + cpuPCB.getPID() + "） 总时间：" + cpuPCB.getTimeNeeded() + " CPU时间：" + cpuPCB.getCPUTime();
        temp += "进程" + QString::number(cpuPCB.getPID());
        //temp += " 总时间：" + QString::number(cpuPCB.getTimeNeeded());
        //temp += " 到达时间：" + QString::number(cpuPCB.getArrTime());
        //temp += " CPU：" + QString::number(cpuPCB.getCPUTime());
        ui->lineEdit->setText(temp);

        int i = 0;
        for(list<PCB>::iterator it = task.readyList.begin(); it != task.readyList.end(); it++, i++)
        {
            PCB pcb_temp = (*it);

            CPUmodel->setItem(i, 0, new QStandardItem(QString::number(pcb_temp.getPID())));
            CPUmodel->setItem(i, 1, new QStandardItem(QString::number(pcb_temp.getArrTime())));
            CPUmodel->setItem(i, 2, new QStandardItem(QString::number(pcb_temp.getCPUTime())));
            CPUmodel->setItem(i, 3, new QStandardItem(QString::number(pcb_temp.getPriority())));
            CPUmodel->setItem(i, 4, new QStandardItem(QString::number(pcb_temp.getPageNum())));
            CPUmodel->setItem(i, 5, new QStandardItem(QString::number(pcb_temp.getOperation())));
            CPUmodel->item(i, 0)->setTextAlignment(Qt::AlignRight);
            CPUmodel->item(i, 1)->setTextAlignment(Qt::AlignRight);
            CPUmodel->item(i, 2)->setTextAlignment(Qt::AlignRight);
            CPUmodel->item(i, 3)->setTextAlignment(Qt::AlignRight);
            CPUmodel->item(i, 4)->setTextAlignment(Qt::AlignRight);
            CPUmodel->item(i, 5)->setTextAlignment(Qt::AlignRight);
        }
    }

}

void MainWindow::updateWaitingTable()
{
    IOmodel->removeRows(0,IOmodel->rowCount());
    ui->lineEdit_2->clear();
    ui->progressBar_2->setValue(0);

    if(ioPCB.getState() != -1)
    {
        ui->progressBar_2->setValue(this->processIO - ioPCB.getIOTime());
        QString temp = "";
        //temp = "进程（" + cpuPCB.getPID() + "） 总时间：" + cpuPCB.getTimeNeeded() + " CPU时间：" + cpuPCB.getCPUTime();
        temp += "进程" + QString::number(ioPCB.getPID());
        //temp += " io时间：" + QString::number(ioPCB.getIOTime());
        //temp += " 到达时间：" + QString::number(ioPCB.getArrTime());
        ui->lineEdit_2->setText(temp);

        int i = 0;
        for(list<PCB>::iterator it = task.waitingList.begin(); it != task.waitingList.end(); it++, i++)
        {
            PCB pcb_temp = (*it);

            IOmodel->setItem(i, 0, new QStandardItem(QString::number(pcb_temp.getPID())));
            IOmodel->setItem(i, 1, new QStandardItem(QString::number(pcb_temp.getArrTime())));
            IOmodel->setItem(i, 2, new QStandardItem(QString::number(pcb_temp.getIOTime())));
            IOmodel->setItem(i, 3, new QStandardItem(QString::number(pcb_temp.getPageNum())));
            IOmodel->setItem(i, 4, new QStandardItem(QString::number(pcb_temp.getOperation())));
            IOmodel->item(i, 0)->setTextAlignment(Qt::AlignRight);
            IOmodel->item(i, 1)->setTextAlignment(Qt::AlignRight);
            IOmodel->item(i, 2)->setTextAlignment(Qt::AlignRight);
            IOmodel->item(i, 3)->setTextAlignment(Qt::AlignRight);
            IOmodel->item(i, 4)->setTextAlignment(Qt::AlignRight);
        }
    }
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    curStrategy = (enum strategy)index;
}

void MainWindow::on_pushButton_clicked()
{
    if(cpuPCB.getState() == -1)
    {
        task.createPCB(PIDcnt, curclock, 0);
        this->processCPU = cpuPCB.getTimeNeeded() - cpuPCB.getIOTime();
        ui->progressBar->setRange(0, this->processCPU - 1);
    }
    else
    {
        task.createPCB(PIDcnt, curclock, 0);
    }
    //updateReadyTable();
}

void MainWindow::on_pushButton_3_clicked()
{
    if(!task.destroyPCB(ui->lineEdit_3->text().toInt()))
    {
        ui->label_6->setText("该进程不存在！");
        ui->label_6->setStyleSheet("color:red");
        ui->label_6->setVisible(true);
    }
    else
    {
        ui->label_6->setVisible(false);
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    if(hasclosed == 1)
    {
        delete f;
        f = new fileWindow();

        f->show();

        hasclosed = 0;
    }
    else
    {
        QLabel *l = new QLabel();
        l->setText("文件系统已打开！");
        l->show();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if(hasclosed == 1)
    {
        this->close();
    }
    else
    {
        QLabel *l = new QLabel();
        l->setText("文件系统或文件未关闭！");
        l->show();
    }
}
