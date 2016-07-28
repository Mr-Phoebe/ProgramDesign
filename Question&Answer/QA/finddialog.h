#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

namespace Ui {
class findDialog;
}

class findDialog : public QDialog
{
    Q_OBJECT

public:
    explicit findDialog(QWidget *parent = 0);
    ~findDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_keyradioButton_clicked();

    void on_timeradioButton_clicked();

private:
    Ui::findDialog *ui;
};

#endif // FINDDIALOG_H
