#ifndef IDORPASSWORDNOTMATCHDIALOG_H
#define IDORPASSWORDNOTMATCHDIALOG_H

#include <QDialog>

namespace Ui {
    class IdOrPasswordNotMatchDialog;
}

class IdOrPasswordNotMatchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IdOrPasswordNotMatchDialog(QWidget *parent = 0);
    ~IdOrPasswordNotMatchDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::IdOrPasswordNotMatchDialog *ui;
};

#endif // IDORPASSWORDNOTMATCHDIALOG_H
