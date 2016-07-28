#ifndef PASSWORDNOTMATCHDIALOG_H
#define PASSWORDNOTMATCHDIALOG_H

#include <QDialog>

namespace Ui {
    class PasswordNotMatchDialog;
}

class PasswordNotMatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PasswordNotMatchDialog(QWidget *parent = 0);
    ~PasswordNotMatchDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::PasswordNotMatchDialog *ui;
};

#endif // PASSWORDNOTMATCHDIALOG_H
