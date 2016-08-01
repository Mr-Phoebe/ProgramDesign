#ifndef DISPLAY_WIDGET_H
#define DISPLAY_WIDGET_H
#include <QPainter>
#include <QFrame>
#include <QImage>
#include <QWidget>
#include <QLayout>
#include <QIcon>
#include <QPixmap>
#include <QRectF>
#include <QGraphicsBlurEffect>
#include "io.h"

class DisplayWidget : public QWidget
{
    Q_OBJECT
    public:
        DisplayWidget(QWidget* parent = 0);
        void draw(QPainter* painter);
        void drawTrack(int x1, int y1, int x2, int y2);
        void drawTrain(int trainId, int x, int y);
        void drawInOutPoint(int x0, int y0, int oneTrack,int anotehrTrack, int d);


    private:
        void paintEvent(QPaintEvent *event = 0);
        const int _D = 7;
        const int SCALE = 5;
        const int X0 = 100;
        const int Y0 = 20;
};
#endif // DISPLAY_WIDGET_H
