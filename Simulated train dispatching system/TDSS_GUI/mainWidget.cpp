#include "mainWidget.h"
#include "displayWidget.h"
#include "infoWidget.h"

MainWidget::MainWidget(QWidget* parent)
{
    if(parent)
        setWindowIcon(parent->windowIcon());
    displayWidget = new DisplayWidget(this);
    infoWidget= new InfoWidget(this);

    QGridLayout *infoLayout = new QGridLayout;
    //infoLayout->addWidget(infoWidget,0,0);
    infoLayout->setMargin(15);
    infoLayout->addWidget(infoWidget,0,0);
    QGroupBox *infoGroupBox = new QGroupBox("控制");
    infoGroupBox->setLayout(infoLayout);


    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(displayWidget);
    mainLayout->addSpacing(50);
    mainLayout->addWidget(infoGroupBox);


    setLayout(mainLayout);

    connect(this, SIGNAL(start()), parent, SLOT(start()));
    connect(this, SIGNAL(pause()), parent, SLOT(pause()));
    connect(this, SIGNAL(refresh()), displayWidget, SLOT(repaint()));
    connect(this, SIGNAL(updateInfoTextEdit()), infoWidget, SLOT(updateInfoTextEdit()));
    qDebug("leave MainWidget2");
}
