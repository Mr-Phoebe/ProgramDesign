#include "cmdDialog.h"
#include "structs.h"
#include "io.h"
#include <cstdio>
#include "log.h"

class Train;

CmdDialog::CmdDialog(int _trainId)
    : trainId(_trainId)
{
    setWindowTitle("用户命令");

    QString askStr = "请点击您对" + QString::number(trainId)
                     + "号火车的命令：";
    askLbl = new QLabel(askStr);

    runBtn = new QPushButton("启动");
    stopBtn = new QPushButton("暂停");
    acceBtn = new QPushButton("加速");
    deceBtn = new QPushButton("减速");

    connect(runBtn, SIGNAL(clicked()), this, SLOT(onRunCmd()));
    connect(stopBtn, SIGNAL(clicked()), this, SLOT(onStopCmd()));
    connect(acceBtn, SIGNAL(clicked()), this, SLOT(onAcceCmd()));
    connect(deceBtn, SIGNAL(clicked()), this, SLOT(onDeceCmd()));
    connect(this, SIGNAL(exit()), this, SLOT(accept()));

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(runBtn);
    btnLayout->addWidget(stopBtn);
    btnLayout->addWidget(acceBtn);
    btnLayout->addWidget(deceBtn);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(askLbl);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);
}

void CmdDialog::onRunCmd()
{
    fprintf(logPtr, "\ntrain %d starts\n", trainId);
    trains[trainId].curState = TrainState(RUN);
    emit exit();
}

void CmdDialog::onStopCmd()
{
    fprintf(logPtr, "\ntrain %d stops\n", trainId);
    trains[trainId].curState = TrainState(STOP);
    emit exit();
}

void CmdDialog::onAcceCmd()
{
    fprintf(logPtr, "\ntrain %d accelerates\n", trainId);
    trains[trainId].speed += 1.;
    trains[trainId].curSpeed += 1.;
    emit exit();
}

void CmdDialog::onDeceCmd()
{
    fprintf(logPtr, "\ntrain %d decelerates\n", trainId);
    if (trains[trainId].speed > 0)
    {
        trains[trainId].speed -= 1.;
        trains[trainId].curSpeed -= 1.;
    }
    emit exit();
}

