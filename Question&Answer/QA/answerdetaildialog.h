#ifndef ANSWERDETAILDIALOG_H
#define ANSWERDETAILDIALOG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
    class AnswerDetailDialog;
}

class AnswerDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnswerDetailDialog(QWidget *parent = 0);
    ~AnswerDetailDialog();
private slots:
    void showDetail();
    void focus();

private:
    Ui::AnswerDetailDialog *ui;
    int m,n;
    QTcpSocket *client;
    void sendMessage();
};

#endif // ANSWERDETAILDIALOG_H
