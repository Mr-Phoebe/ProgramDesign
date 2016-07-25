#ifndef SHOWQADIALOG_H
#define SHOWQADIALOG_H

#include <QDialog>

namespace Ui {
    class ShowQADialog;
}

class ShowQADialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowQADialog(QWidget *parent = 0);
    ~ShowQADialog();

private slots:
    void on_ExitButton_clicked();

    void on_LookoverQButton_clicked();

    void on_AskQButton_clicked();

    void on_LookFocusBtn_clicked();

private:
    Ui::ShowQADialog *ui;
};

#endif // SHOWQADIALOG_H
