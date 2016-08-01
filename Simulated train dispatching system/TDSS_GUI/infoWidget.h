#ifndef INFOWIDGET_H
#define INFOWIDGET_H
#include <QLabel>
#include <QListWidget>
#include <QLabel>
#include <QTextEdit>
#include <QLayout>
#include <QPalette>
#include <QTime>
#include <QLCDNumber>
#include "structs.h"
#include <QToolButton>
#include <QPushButton>

class InfoWidget : public QWidget
{
    Q_OBJECT
    public:
        InfoWidget(QWidget *parent = 0);

    private slots:
        void updateInfoTextEdit(void);
        void setFastFtrst();
        void setAlternative();
        void setManualCtrl();
        void enablePause();
        void disablePause();

    private:
        QTime* displayTime;
        QLCDNumber *timeLCDNumber;
        QLCDNumber *dateLCDNumber;
        QPushButton* startBtn;
        QPushButton* pauseBtn;
        QLabel *trainLabel;
        QListWidget *trainListWidget;
        QLabel *infoLabel;
        QTextEdit *infoTextEdit;
        QToolButton *trainBtn[MAX_TRAIN_NUM];
};

#endif // INFOWIDGET_H
