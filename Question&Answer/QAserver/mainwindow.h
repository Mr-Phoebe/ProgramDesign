#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include "totalclass.h"

namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpServer *server;
    QTcpSocket *clientConnection;
    int checkhas(QString, QString);
    void sendUser();
    void sendQue();
    void sendAns();
    void sendMessage(MessageType);
    void sendMessage(MessageType, int);
    void answerAdd(Answer);
    void questionAdd(Question);
    void setInfo();
    void setInfo(QString);
    void setInfo(QString, QString, QString);


private slots:
    void acceptConnection();
    void readClient();
    void error();
};

#endif // MAINWINDOW_H
