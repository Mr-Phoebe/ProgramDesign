#ifndef CONFIG_TRACK_H
#define CONFIG_TRACK_H

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

class ConfigTrackNumDialog : public QDialog
{       
    Q_OBJECT
    public:
        ConfigTrackNumDialog(QWidget* parent = 0);
        void setData();

    private:
        QLabel* trackNumLbl;
        QLineEdit* trackNumLineEdit;

        QPushButton* okBtn;
        QPushButton* cnclBtn;
};

class ConfigTrackDialog : public QDialog
{
    Q_OBJECT
    public:
        ConfigTrackDialog(QWidget* parent = 0, int trackId = -1);
        void setData();

    private:
        int trackId;
        QPushButton* okBtn;
        QPushButton* cnclBtn;

        QLabel* lengthLbl;
        QLabel* widthLbl;

        QLineEdit* lengthLineEdit;
        QLineEdit* widthLineEdit;

        QGroupBox* publicTracksGrpBox;

        QLineEdit* iPLE[MAX_TRACK_NUM];
        QLineEdit* oPLE[MAX_TRACK_NUM];
};

#endif // CONFIG_TRACK_H
