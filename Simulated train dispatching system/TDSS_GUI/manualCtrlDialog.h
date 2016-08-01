#ifndef MANUAL_CTRL_DIALOG_H
#define MANUAL_CTRL_DIALOG_H

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

class ManualCtrlDialog : public QDialog
{
    Q_OBJECT
    public:
        ManualCtrlDialog(int _train0 = -1, int _train1 = -1);

        QLabel* askLbl;
        QPushButton* train0Btn;
        QPushButton* train1Btn;

        int getFirst();

    signals:
        void exit();

    public slots:
        void setTrain0First();
        void setTrain1Fisrt();

    private:
        int train0, train1;
        bool firstTrain;
};

#endif
