#include "displayWidget.h"
#include "mainWindow.h"

DisplayWidget::DisplayWidget(QWidget *parent)
{
    setFixedSize(711, 590);
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(0x00, 0x00, 0x00, 0x00));
    setPalette(pal);
}

void DisplayWidget::drawTrain(int trainId, int x, int y)
{
    QPainter trainPainter(this);
    QPixmap pix;
    double _x(trains[trainId].getX()), _y(trains[trainId].getY());

    if ((_x == (double)tracks[trains[trainId].curTrack].length
         && _y > 0.)
        || (_x == 0.
            && _y < (double)tracks[trains[trainId].curTrack].width))
        pix.load(":/images/train"+QString::number(trainId)+"_right.png");
    else
        pix.load(":/images/train"+QString::number(trainId)+"_up.png");

    if (trains[trainId].curState == WAIT && trains[trainId].inPublicTrack)
        trainPainter.drawText(x - 20, y - 20, QString::number(1 + int(trains[trainId].restStayDur/UNITS_PER_SEC)));
    trainPainter.drawPixmap(x - 10, y - 10, 20, 20, pix);
}

void DisplayWidget::drawTrack(int x1, int y1, int x2, int y2)
{
    QPainter edgePainter(this);
    edgePainter.setRenderHint(QPainter::Antialiasing, true);
    edgePainter.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    edgePainter.drawLine(x1 - _D, y1 - _D, x2 + _D, y1 - _D);
    edgePainter.drawLine(x1 - _D, y2 + _D, x2 + _D, y2 + _D);
    edgePainter.drawLine(x1 + _D, y1 + _D, x2 - _D, y1 + _D);
    edgePainter.drawLine(x1 + _D, y2 - _D, x2 - _D, y2 - _D);
    edgePainter.drawLine(x1 - _D, y1 - _D, x1 - _D, y2 + _D);
    edgePainter.drawLine(x2 + _D, y1 - _D, x2 + _D, y2 + _D);
    edgePainter.drawLine(x1 + _D, y1 + _D, x1 + _D, y2 - _D);
    edgePainter.drawLine(x2 - _D, y1 + _D, x2 - _D, y2 - _D);

    QPainter horTiePainter(this);
    horTiePainter.setRenderHint(QPainter::Antialiasing, true);
    horTiePainter.setPen(QPen(QBrush(Qt::VerPattern), 5 + _D * 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    horTiePainter.drawLine(x1, y1, x2, y1);
    horTiePainter.drawLine(x1, y2, x2, y2);

    QPainter verTiePainter(this);
    verTiePainter.setRenderHint(QPainter::Antialiasing, true);
    verTiePainter.setPen(QPen(QBrush(Qt::HorPattern), 5 + _D * 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    verTiePainter.drawLine(x1, y1, x1, y2);
    verTiePainter.drawLine(x2, y1, x2, y2);
}

void DisplayWidget::drawInOutPoint(int x0, int y0, int oneTrack, int anotherTrack, int d)
{
    QPainter pointPainter(this);
    QPixmap pix;

    if(publicTracks[oneTrack][anotherTrack].state == IDLE) pix.load("green.png");
    else
        pix.load("red.png");

    double _x = publicTracks[oneTrack][anotherTrack].getX(oneTrack, anotherTrack, d);
    double _y = publicTracks[oneTrack][anotherTrack].getY(oneTrack, anotherTrack, d);


    _x = x0 + _x * SCALE;
    _y = y0 + _y * SCALE;

     pointPainter.drawPixmap(_x, _y, 10, 10, pix);
}

void DisplayWidget::paintEvent(QPaintEvent *event)
{
    int l = 60 * SCALE;
    int w = 20 * SCALE;

    tracks[0].x0 = X0;
    tracks[0].y0 = Y0 + w;
    tracks[1].x0 = X0 + l;
    tracks[1].y0 = Y0;
    tracks[2].x0 = X0 + w + w;
    tracks[2].y0 = Y0 + l;
    tracks[3].x0 = X0 + w;
    tracks[3].y0 = Y0 + w + w;

    for (int i(0); i < trackNum; ++i)
    {
        const Track& track(tracks[i]);

        drawTrack(track.x0, track.y0, track.x0 + track.length * SCALE, track.y0 + track.width * SCALE);
    }

    for (int i = 0; i < trainNum; ++i)
    {
        Train& train(trains[i]);

        drawTrain(i,
                  tracks[train.curTrack].x0 + train.getX() * SCALE,
                  tracks[train.curTrack].y0 + train.getY() * SCALE);
    }

    for (int i = 0; i < trackNum; ++i)
        for (int j = 0; j < trackNum; ++j)
            if (publicTracks[i][j].exist)
            {
                drawInOutPoint(tracks[i].x0, tracks[i].y0, i, j, 0);
                drawInOutPoint(tracks[i].x0, tracks[i].y0, i, j, 1);
            }
}
