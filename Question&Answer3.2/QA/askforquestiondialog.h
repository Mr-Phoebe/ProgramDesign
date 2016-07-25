#ifndef ASKFORQUESTIONDIALOG_H
#define ASKFORQUESTIONDIALOG_H

#include <QDialog>
#include <QtNetwork>
#include "totalclass.h"

namespace Ui {
    class AskForQuestionDialog;
}

class AskForQuestionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AskForQuestionDialog(QWidget *parent = 0);
    ~AskForQuestionDialog();

private slots:
    void on_pushButton_clicked();

    void on_SubmitButton_clicked();

private:
    Ui::AskForQuestionDialog *ui;
    QTcpSocket *client;
    void sendMessage(Question);
};

#endif // ASKFORQUESTIONDIALOG_H
