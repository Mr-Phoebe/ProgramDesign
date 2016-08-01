#include "infoWidget.h"
#include "mainWidget.h"


void InfoWidget::updateInfoTextEdit(void)
{
    //qDebug() << "+1s!!!!\n";
    displayTime = new QTime(displayTime->addSecs(1));
    timeLCDNumber->display(displayTime->toString("hh:mm:ss"));
    infoTextEdit->setText("当前策略：" + strategyStr[strategy]);
    infoTextEdit->append("火车序号   当前位置   当前速度");
    for (int i = 0; i < trainNum; ++i)
    {
        infoTextEdit->append("   " + QString::number(i) + "     (" +
                             QString::number(trains[i].getX(),'.',2) + ", " +
                             QString::number(trains[i].getY(),'.',2) + ")     " +
                             QString::number(trains[i].curState == RUN ? trains[i].curSpeed : 0));
    }
}

void InfoWidget::setFastFtrst()
{
    strategy = FAST_FIRST;
}

void InfoWidget::setAlternative()
{
    strategy = ALTERNATIVE;
}

void InfoWidget::setManualCtrl()
{
    strategy = MANUAL_CTRL;

    cout << "change strategy to " << strategy << endl;
}

void InfoWidget::enablePause()
{
    if (pauseBtn)
        pauseBtn->setEnabled(true);
}

void InfoWidget::disablePause()
{
    if (pauseBtn)
        pauseBtn->setEnabled(false);
}

InfoWidget::InfoWidget(QWidget* parent)
{
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0x00, 0x00, 0x00, 0x00));
    setPalette(pal);

    displayTime = new QTime(0, 0);

    timeLCDNumber = new QLCDNumber(8);
    timeLCDNumber->setSegmentStyle(QLCDNumber::Flat);
    timeLCDNumber->setFixedHeight(50);
    timeLCDNumber->setLineWidth(0);
    timeLCDNumber->setStyleSheet("color:rgb(6, 12 ,41);");
    timeLCDNumber->display(displayTime->toString("hh:mm:ss"));

    startBtn = new QPushButton(QObject::tr("开始模拟"));
    pauseBtn = new QPushButton(QObject::tr("暂停模拟"));
    pauseBtn->setEnabled(false);
    QGridLayout* btnLayout = new QGridLayout;
    btnLayout->addWidget(startBtn, 0, 0);
    btnLayout->addWidget(pauseBtn, 0, 1);
    connect(startBtn, SIGNAL(clicked()), this, SLOT(enablePause()));
    connect(startBtn, SIGNAL(clicked()), parent, SIGNAL(start()));
    connect(pauseBtn, SIGNAL(clicked()), this, SLOT(disablePause()));
    connect(pauseBtn, SIGNAL(clicked()), parent, SIGNAL(pause()));

    for (int i = 0; i < trainNum; ++i)
    {
        qDebug() << i << "号火车\n";

        trainBtn[i] = new QToolButton;
        trainBtn[i]->setText(QString::number(i) + "号火车");
        //QString pngName(QString::number(i)+".png");
        trainBtn[i]->setIcon(QPixmap(":/images/train"+QString::number(i)+"_up.png"));
        //trainBtn[i]->setIconSize(QPixmap(QString::number(i)+".png").size());
        trainBtn[i]->setIconSize(QSize(30,30));
        trainBtn[i]->setAutoRaise(true);
        trainBtn[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        connect(trainBtn[i], SIGNAL(clicked()), trains + i, SLOT(getCmd()));
    }

    QPushButton* fastFirstBtn = new QPushButton("快车优先");
    QPushButton* alternativeBtn = new QPushButton("交替优先");
    QPushButton* manualCtrlBtn = new QPushButton("人工控制");

    connect(fastFirstBtn, SIGNAL(clicked()), this, SLOT(setFastFtrst()));
    connect(alternativeBtn, SIGNAL(clicked()), this, SLOT(setAlternative()));
    connect(manualCtrlBtn, SIGNAL(clicked()), this, SLOT(setManualCtrl()));

    QHBoxLayout* strategyLayout = new QHBoxLayout;
    strategyLayout->addWidget(fastFirstBtn);
    strategyLayout->addWidget(alternativeBtn);
    strategyLayout->addWidget(manualCtrlBtn);

    infoLabel = new QLabel("状态信息");
    infoTextEdit = new QTextEdit;
    infoTextEdit->setFixedWidth(200);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(timeLCDNumber);
    mainLayout->addLayout(btnLayout);
    mainLayout->addLayout(strategyLayout);
    for (int i = 0; i < trainNum; ++i)
        mainLayout->addWidget(trainBtn[i]);

    mainLayout->addSpacing(15);
    mainLayout->addWidget(infoLabel);
    mainLayout->addWidget(infoTextEdit);
    mainLayout->setAlignment(Qt::AlignHCenter);
    setLayout(mainLayout);
}

