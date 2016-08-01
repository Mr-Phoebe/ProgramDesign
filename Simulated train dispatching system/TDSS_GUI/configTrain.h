#ifndef CONFIG_TRAIN_H
#define CONFIG_TRAIN_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QApplication>
#include <QLayout>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QString>
#include <QButtonGroup>
#include <QDebug>
#include <QCheckBox>
#include <QDateTimeEdit>

#include "structs.h"
#include "mainWindow.h"

class ConfigTrainNumDialog : public QDialog
{
    Q_OBJECT
    public:
        ConfigTrainNumDialog(QWidget* parent = 0);
        void setData();

    private:
        QLabel* trainNumLbl;
        QLineEdit* trainNumLineEdit;

        QPushButton* okBtn;
        QPushButton* cnclBtn;
};

class ConfigTrainDialog : public QDialog
{
    Q_OBJECT
    public:
        ConfigTrainDialog(QWidget * parent = 0, int trainId = -1);
        void setData();

    private slots:

    private:
        int trainId;

        QPushButton* okBtn;
        QPushButton* cnclBtn;

        QLabel* typeLbl;
        QLabel* dirLbl;
        QLabel* startTimeLbl;
        QLabel* startTrackLbl;
        QLabel* startPosLbl;
        QLabel* speedLbl;
        QLabel* passLbl;
        QLabel* stayDurLbl;

        QLineEdit* typeLE;
        QLineEdit* dirLE;
        QLineEdit* startTimeLE;
        QLineEdit* startTrackLE;
        QLineEdit* startPosLE;
        QLineEdit* speedLE;
        QCheckBox* passCB[MAX_TRACK_NUM];
        QLineEdit* stayDurLE[MAX_TRACK_NUM][MAX_TRACK_NUM];
};

#endif // CONFIG_TRAIN_H
