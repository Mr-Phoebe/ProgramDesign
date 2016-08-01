#include "configTrain.h"

ConfigTrainNumDialog::ConfigTrainNumDialog(QWidget* parent)
{
    if (parent)
        setWindowIcon(parent->windowIcon());
    setWindowTitle("轨道数量配置");

    cout << "!!!!configTrainNum\n";

    trainNumLbl = new QLabel("请输入火车数量：");
    trainNumLineEdit = new QLineEdit;
    trainNumLineEdit->setValidator(new QIntValidator(1, 100, this));
    okBtn = new QPushButton("确定");
    cnclBtn = new QPushButton("取消");
    QVBoxLayout* trainNumLayout = new QVBoxLayout;
    trainNumLayout->addWidget(trainNumLbl);
    trainNumLayout->addWidget(trainNumLineEdit);
    trainNumLayout->addWidget(okBtn);
    trainNumLayout->addWidget(cnclBtn);

    setLayout(trainNumLayout);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cnclBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void ConfigTrainNumDialog::setData()
{
    trainNum = trainNumLineEdit->text().toInt();
}

void ConfigTrainDialog::setData()
{
    trains[trainId].type = TrainType(typeLE->text().toInt());
    trains[trainId].dir = TrainDir(dirLE->text().toInt());

    if (trains[trainId].dir == WHATEVER)
        trains[trainId].dir = CNTRCLKWISE;

    trains[trainId].startTime = startTimeLE->text().toInt();
    trains[trainId].startTrack = startTrackLE->text().toInt();
    trains[trainId].startPos = startPosLE->text().toInt();
    trains[trainId].speed = speedLE->text().toInt();

    trains[trainId].pass[trains[trainId].startTrack] = 1;

    for (int i(0); i < trackNum; ++i)
    {
        if (i == trains[trainId].startTrack)
            continue;
        if (passCB[i]->isChecked())
            trains[trainId].pass[i] = 1;
    }

    for (int i(0); i < trackNum; ++i)
        for (int j(0); j < trackNum; ++j)
            if (publicTracks[i][j].exist)
            {
                trains[trainId].stayDur[i][j] =
                        stayDurLE[i][j]->text().toInt();
            }

    return;
}

ConfigTrainDialog::ConfigTrainDialog(QWidget* parent, int _trainId)
    : trainId(_trainId)
{
    //qDebug("enter ConfigTrainDialog");
    if (parent)
        setWindowIcon(parent->windowIcon());
    //设置图标
    QString title = QString::number(trainId) + "号火车配置";
    setWindowTitle(title);

    typeLbl = new QLabel("火车类型");
    dirLbl = new QLabel("火车方向");
    startTimeLbl = new QLabel("启动时间");
    startTrackLbl = new QLabel("起始轨道");
    startPosLbl = new QLabel("启动位置");
    speedLbl = new QLabel("火车速度");
    passLbl = new QLabel("经过轨道");
    stayDurLbl = new QLabel("停靠时间");

    typeLE = new QLineEdit;
    typeLE->setValidator(new QIntValidator(0, 1, this));
    typeLE->setPlaceholderText("慢车 - 0， 快车 - 1");

    dirLE = new QLineEdit;
    dirLE->setValidator(new QIntValidator(0, 1, this));
    dirLE->setPlaceholderText("逆时针 - 0， 顺时针 - 1");

    startTimeLE = new QLineEdit;
    startTimeLE->setValidator(new QIntValidator(0, 10000, this));

    startTrackLE = new QLineEdit;
    startTrackLE->setValidator(new QIntValidator(0, trackNum - 1, this));

    startPosLE = new QLineEdit;
    startPosLE->setValidator(new QIntValidator(0, 240, this));

    speedLE = new QLineEdit;
    speedLE->setValidator(new QIntValidator(0, 1000, this));

    QHBoxLayout* typeLayout= new QHBoxLayout;
    typeLayout->addWidget(typeLbl);
    typeLayout->addWidget(typeLE);

    QHBoxLayout* dirLayout = new QHBoxLayout;
    dirLayout->addWidget(dirLbl);
    dirLayout->addWidget(dirLE);

    QHBoxLayout* startTimeLayout = new QHBoxLayout;
    startTimeLayout->addWidget(startTimeLbl);
    startTimeLayout->addWidget(startTimeLE);

    QHBoxLayout* startTrackLayout = new QHBoxLayout;
    startTrackLayout->addWidget(startTrackLbl);
    startTrackLayout->addWidget(startTrackLE);


    QHBoxLayout* startPosLayout = new QHBoxLayout;
    startPosLayout->addWidget(startPosLbl);
    startPosLayout->addWidget(startPosLE);


    QHBoxLayout* speedLayout = new QHBoxLayout;
    speedLayout->addWidget(speedLbl);
    speedLayout->addWidget(speedLE);

    QGroupBox* passGrp = new QGroupBox("经过轨道");

    QVBoxLayout* passLayout = new QVBoxLayout;

    for (int i(0); i < trackNum; ++i)
    {
        passCB[i] = new QCheckBox(QString::number(i) + "号轨道", this);
        passLayout->addWidget(passCB[i]);
    }

    passGrp->setLayout(passLayout);

    QGroupBox* stayDurGrp = new QGroupBox("在公共轨道上停靠时间");

    QVBoxLayout* stayDurLayout = new QVBoxLayout;

    for (int i(0); i < trackNum; ++i)
        for (int j(0); j < trackNum; ++j)
            if (publicTracks[i][j].exist)
            {
                QHBoxLayout* publicTrackLayout = new QHBoxLayout;

                QLabel* publicTrackIdLbl = new QLabel("公共轨道 " + QString::number(i)
                                                      + " - " + QString::number(j));

                stayDurLE[i][j] = new QLineEdit;
                stayDurLE[i][j]->setValidator(new QIntValidator(0, 10000));

                publicTrackLayout->addWidget(publicTrackIdLbl);
                publicTrackLayout->addWidget(stayDurLE[i][j]);

                stayDurLayout->addLayout(publicTrackLayout);
            }

    stayDurGrp->setLayout(stayDurLayout);

    QHBoxLayout* btnLayout = new QHBoxLayout;
    btnLayout->addWidget(okBtn);
    btnLayout->addWidget(cnclBtn);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(typeLayout);
    mainLayout->addLayout(dirLayout);
    mainLayout->addLayout(startTimeLayout);
    mainLayout->addLayout(startTrackLayout);
    mainLayout->addLayout(startPosLayout);
    mainLayout->addLayout(speedLayout);
    mainLayout->addWidget(passGrp);
    mainLayout->addWidget(stayDurGrp);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cnclBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));
    return;
}
