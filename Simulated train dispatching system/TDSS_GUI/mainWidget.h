#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include <QImage>
#include <QSplitter>
#include <QListView>
#include <QTextEdit>
#include <QGroupBox>
#include <QLabel>
#include <QGraphicsOpacityEffect>


class InfoWidget;
class DisplayWidget;

class MainWidget : public QWidget
{
    Q_OBJECT
    public:
        MainWidget(QWidget* parent = 0);

    signals:
        void updateInfoTextEdit();
        void start();
        void pause();
        void refresh();
        void drawInOutPoint(void);


    private:

        DisplayWidget* displayWidget;
        InfoWidget* infoWidget;
};

#endif // MAINWIDGET_H
