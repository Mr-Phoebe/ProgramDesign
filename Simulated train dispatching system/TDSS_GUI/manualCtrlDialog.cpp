#include "manualCtrlDialog.h"
#include "structs.h"
#include "mainWindow.h"

ManualCtrlDialog::ManualCtrlDialog(int _train0, int _train1)
    : train0(_train0), train1(_train1), firstTrain(0)
{
    setWindowTitle("人工控制");

    QString askStr = QString::number(train0) + "号火车与"
                     + QString::number(train1) + "号火车正在争夺公共轨道，\n"
                     + "请选择优先通过的车辆：";

    askLbl = new QLabel(askStr);

    QHBoxLayout* askLayout = new QHBoxLayout;
    askLayout->addWidget(askLbl);

    train0Btn = new QPushButton(QString::number(train0) + "号火车");
    train1Btn = new QPushButton(QString::number(train1) + "号火车");

    connect(train0Btn, SIGNAL(clicked()), this, SLOT(setTrain0First()));
    connect(train1Btn, SIGNAL(clicked()), this, SLOT(setTrain1Fisrt()));
    connect(this, SIGNAL(exit()), this, SLOT(accept()));

    QHBoxLayout* ansLayout = new QHBoxLayout;
    ansLayout->addWidget(train0Btn);
    ansLayout->addWidget(train1Btn);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(askLayout);
    mainLayout->addLayout(ansLayout);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    setLayout(mainLayout);
}

void ManualCtrlDialog::setTrain0First()
{
    cout << "set train 0\n";
    firstTrain = 0;
    emit exit();
}

void ManualCtrlDialog::setTrain1Fisrt()
{
    cout << "set train 1\n";
    firstTrain = 1;
    emit exit();
}

int ManualCtrlDialog::getFirst()
{
    return firstTrain ? train1 : train0;
}
