#ifndef CMD_DIALOG_H
#define CMD_DIALOG_H

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
//#include "io.h"

//#include "mainWindow.h"

class CmdDialog : public QDialog
{
    Q_OBJECT
    public:
        CmdDialog(int _trainId = -1);

        QLabel* askLbl;

        QPushButton* runBtn;
        QPushButton* stopBtn;
        QPushButton* acceBtn;
        QPushButton* deceBtn;

    signals:
        exit();

    private slots:
        void onRunCmd();
        void onStopCmd();
        void onAcceCmd();
        void onDeceCmd();

    private:
        int trainId;
};

#endif // CMD_DIALOG_H
