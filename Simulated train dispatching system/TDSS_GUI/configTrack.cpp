#include "configTrack.h"

ConfigTrackNumDialog::ConfigTrackNumDialog(QWidget* parent)
{
    if (parent)
        setWindowIcon(parent->windowIcon());
    setWindowTitle("轨道数量配置");

    cout << "!!!!configTrackNum\n";

    trackNumLbl = new QLabel("请输入轨道数量：");
    trackNumLineEdit = new QLineEdit;
    trackNumLineEdit->setValidator(new QIntValidator(1, 10, this));
    trackNumLineEdit->setPlaceholderText("请输入1~10的整数");
    okBtn = new QPushButton("确定");
    cnclBtn = new QPushButton("取消");

    QVBoxLayout* trackNumLayout = new QVBoxLayout;
    trackNumLayout->addWidget(trackNumLbl);
    trackNumLayout->addWidget(trackNumLineEdit);
    trackNumLayout->addWidget(okBtn);
    trackNumLayout->addWidget(cnclBtn);
    setLayout(trackNumLayout);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cnclBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void ConfigTrackNumDialog::setData()
{
    trackNum = trackNumLineEdit->text().toInt();
    cout << "trackNum = " << trackNum << endl;
}

void ConfigTrackDialog::setData()
{
    tracks[trackId].length = lengthLineEdit->text().toInt();
    tracks[trackId].width = widthLineEdit->text().toInt();
    tracks[trackId].peremeter = (tracks[trackId].length + tracks[trackId].width) * 2.;

    for (int i(0); i < trackNum; ++i)
    {
        if (i == trackId)
        {
            publicTracks[i][i].exist = 0;
            continue;
        }

        publicTracks[trackId][i].inPoint = iPLE[i]->text().toInt();
        publicTracks[trackId][i].outPoint = iPLE[i]->text().toInt();

        if (publicTracks[trackId][i].inPoint > -1
            && publicTracks[trackId][i].outPoint > -1)
        {
            publicTracks[trackId][i].midPoint = (publicTracks[trackId][i].inPoint
                                                + publicTracks[trackId][i].outPoint) / 2.;
            publicTracks[trackId][i].exist = 1;
        }
        else
            publicTracks[trackId][i].exist = 0;
    }

    return;
}

ConfigTrackDialog::ConfigTrackDialog(QWidget *parent, int _trackId)
    : trackId(_trackId)
{
    cout << "in Ctor of ConfigTrackDialog\n";
    if (parent)
        setWindowIcon(parent->windowIcon());

    QString title = QString::number(trackId) + "号轨道配置";
    setWindowTitle(title);


    lengthLbl = new QLabel("轨道长度：");
    lengthLineEdit = new QLineEdit;
    lengthLineEdit->setValidator(new QIntValidator(20, 60, this));
    lengthLineEdit->setPlaceholderText("请输入20~60的整数");
    QHBoxLayout* lengthLayout  = new QHBoxLayout;
    lengthLayout->addWidget(lengthLbl);
    lengthLayout->addWidget(lengthLineEdit);

    widthLbl = new QLabel("轨道宽度：");
    widthLineEdit = new QLineEdit;
    widthLineEdit->setValidator(new QIntValidator(20, 60, this));
    widthLineEdit->setPlaceholderText("请输入20~60的整数");
    QHBoxLayout* widthLayout  = new QHBoxLayout;
    widthLayout->addWidget(widthLbl);
    widthLayout->addWidget(widthLineEdit);

    QGroupBox* publicTrackGrp = new QGroupBox("与其他轨道的公共轨道入点及出点坐标（顺时针距左上角距离）：\n"
                                              "(无公共轨道请输入-1）");
    QVBoxLayout* publicTrackLayout = new QVBoxLayout;

    for (int i(0); i < trackNum; ++i)
    {
        if (i == trackId)
            continue;

        QLabel* iPLbl = new QLabel(QString::number(trackId) + " - " + QString::number(i) + "入点：");
        iPLE[i] = new QLineEdit;
        iPLE[i]->setValidator(new QIntValidator(-1, 240, this));
        QLabel* oPLbl = new QLabel("出点：");
        oPLE[i] = new QLineEdit;
        oPLE[i]->setValidator(new QIntValidator(-1, 240, this));
        QHBoxLayout* iOPLayout = new QHBoxLayout;

        iOPLayout->addWidget(iPLbl);
        iOPLayout->addWidget(iPLE[i]);
        iOPLayout->addWidget(oPLbl);
        iOPLayout->addWidget(oPLE[i]);

        publicTrackLayout->addLayout(iOPLayout);
    }

    publicTrackGrp->setLayout(publicTrackLayout);

    okBtn = new QPushButton("确定");
    cnclBtn = new QPushButton("取消");

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(lengthLayout);
    mainLayout->addLayout(widthLayout);
    mainLayout->addWidget(publicTrackGrp);
    mainLayout->addWidget(okBtn);
    mainLayout->addWidget(cnclBtn);

    connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cnclBtn, SIGNAL(clicked(bool)), this, SLOT(reject()));

    setLayout(mainLayout);
}
