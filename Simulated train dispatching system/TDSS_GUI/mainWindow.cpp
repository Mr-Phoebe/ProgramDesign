#include <algorithm>
#include <QAccessible>
#include "mainWindow.h"
#include "mainWidget.h"
#include "configTrack.h"
#include "configTrain.h"
//#include "manualCtrlDialog.h"


void MainWindow::pause()
{
    remainingTime = timer->remainingTime();
    timer->stop();
}

void MainWindow::start()
{
    if (!started)
    {
        timer = new QTimer;
        timer->start(UNIT_TIME);
        started = 1;
        logBtn->setEnabled(true);
        logPtr = fopen("TDSS.log", "w");
        connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    }
    else
    {
        timer->start(remainingTime);
    }
}


void MainWindow::createMenus(void)
{
    logBtn = new QPushButton("日志");
    logBtn->setEnabled(false);
    connect(logBtn, SIGNAL(clicked()), this, SLOT(openLog()));

    menuBar()->setCornerWidget(logBtn, Qt::TopLeftCorner);
    menuBar()->setDefaultUp(true);

    qDebug("leave createMenus");
    return;
}

void MainWindow::openLog(void)
{
    pause();
    fclose(logPtr);
    system("TDSS.log");
    logPtr = fopen("TDSS.log", "a+");
    start();
    return;
}

void MainWindow::configTrack(void)
{
    qDebug("enter configTrack");
    //int remainingTime = pause();
    cout << "new a configTrackDialog\n";

    cout << trackNum << endl;

    QMessageBox useDefltTrackConfig(QMessageBox::Question, "轨道配置", "是否使用默认轨道配置?",
                                    QMessageBox::Yes | QMessageBox::No);

    if (useDefltTrackConfig.exec() == QMessageBox::No)
    {
        ConfigTrackNumDialog configTrackNumDialog(this);
        while (configTrackNumDialog.exec())
        {
            configTrackNumDialog.setData();
            break;
        }

        for (int trackId(0); trackId < trackNum; ++trackId)
        {
            ConfigTrackDialog configTrackDialog(this, trackId);

            while (configTrackDialog.exec())
            {
                //configTrackDialog.setData();
                break;
            }
        }
    }

    return;
}

void MainWindow::configTrain()
{
    qDebug("enter configTrain");
    //int remainingTime = pause();
    cout << "new a configTrainDialog\n";

    cout << trainNum << endl;

    QMessageBox useDefltTrainConfig(QMessageBox::Question, "火车配置", "是否使用默认火车配置?",
                                    QMessageBox::Yes | QMessageBox::No);

    if (useDefltTrainConfig.exec() == QMessageBox::No)
    {
        ConfigTrainNumDialog configTrainNumDialog(this);
        while (configTrainNumDialog.exec())
        {
            configTrainNumDialog.setData();
            break;
        }

        for (int trainId(0); trainId < trainNum; ++trainId)
        {
            ConfigTrainDialog configTrainDialog(this, trainId);

            configTrainDialog.exec();
        }
    }

    return;
}


void MainWindow::onTimeout(void)
{
    /*
     * emit someSignal tp trigger displayWidget.repaint()
     * if (!(t % UNITS_PER_SEC)) update the LCD
     * getIntend();
     * dispatch(); //MANUAL_CTRL -> QMessageBox
     * stateTrans();
     */

    emit refresh();

    if (!((t++) % UNITS_PER_SEC))
    {
        //qDebug() << "1s!!!!\n";
        emit updateInfoTextEdit();

        printState();
    }

    control();

    timer->start(UNIT_TIME);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/images/train.png"));
    setFixedSize(MainWindowWidth, MainWindowHeight);

    loadFromConfig();
    createMenus();
    configTrack();
    configTrain();

    init();

    started = 0;

    qDebug() << "trainNum = " << trainNum << endl;

    mainWidget = new MainWidget(this);
    setCentralWidget(mainWidget);
    mainWidget->setWindowTitle(QObject::tr("模拟火车调度系统"));

    setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QPixmap(":/images/blankBackground.png"));
    setPalette(palette);


    connect(this, SIGNAL(updateInfoTextEdit()), mainWidget, SIGNAL(updateInfoTextEdit()));
    connect(this, SIGNAL(refresh()), mainWidget, SIGNAL(refresh()));

    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(2);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    animation->pause();

    animation->resume();
}

MainWindow::~MainWindow()
{

}
