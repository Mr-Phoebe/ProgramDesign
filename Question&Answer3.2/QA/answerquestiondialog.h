#ifndef ANSWERQUESTIONDIALOG_H
#define ANSWERQUESTIONDIALOG_H

#include <QDialog>
#include <QtNetwork>
#include "totalclass.h"

namespace Ui {
    class AnswerQuestionDialog;
}

class AnswerQuestionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnswerQuestionDialog(QWidget *parent = 0);
    ~AnswerQuestionDialog();

private slots:
    void on_ReturnButton_clicked();
    void on_SubmitButton_clicked();
    void on_ClearButton_clicked();

private:
    Ui::AnswerQuestionDialog *ui;
    QTcpSocket *client;
    void sendMessage(Answer);
};

#endif // ANSWERQUESTIONDIALOG_H
