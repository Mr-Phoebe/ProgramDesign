#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QtNetwork>
#include "totalclass.h"

namespace Ui {
    class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();

private slots:
    void on_RegisterButton_clicked();
    void on_LoginButton_clicked();
    void readServer();
    void error();

private:
    Ui::MyWidget *ui;
    QTcpSocket *client;
    void getQuestionInfo();
    void getAnswerInfo();
    void getUserInfo();
};


#endif // MYWIDGET_H
