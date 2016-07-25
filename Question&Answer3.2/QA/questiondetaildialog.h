#ifndef QUESTIONDETAILDIALOG_H
#define QUESTIONDETAILDIALOG_H

#include <QDialog>
#include <QtNetwork>

namespace Ui {
    class QuestionDetailDialog;
}

class QuestionDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuestionDetailDialog(QWidget *parent = 0);
    ~QuestionDetailDialog();

private:
    Ui::QuestionDetailDialog *ui;
    int z;
    QTcpSocket *client;
    void sendMessage();
private slots:
    void addFocusList();
};

#endif // QUESTIONDETAILDIALOG_H
