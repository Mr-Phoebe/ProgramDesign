#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
    class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QWidget *parent = 0);
    ~RegisterDialog();

private slots:

    void on_Surebutton_clicked();

    void on_Nobutton_clicked();

    void error();

private:
    Ui::RegisterDialog *ui;
    QTcpSocket *client;
    void sendMessage(int,QString, QString, QString);
};

#endif // REGISTERDIALOG_H
