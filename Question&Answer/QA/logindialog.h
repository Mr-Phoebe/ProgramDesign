#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
    class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:

    void on_Surebutton_clicked();

    void on_Nobutton_clicked();

    void readServer();

private:
    Ui::LoginDialog *ui;
    QTcpSocket *client;
    void sendMessage(int, QString, QString);
    void log(int);
};

#endif // LOGINDIALOG_H
