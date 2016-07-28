#ifndef SUBQUSETIONDONEDIALOG_H
#define SUBQUSETIONDONEDIALOG_H

#include <QDialog>

namespace Ui {
    class SubQusetionDoneDialog;
}

class SubQusetionDoneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SubQusetionDoneDialog(QWidget *parent = 0);
    ~SubQusetionDoneDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SubQusetionDoneDialog *ui;
};

#endif // SUBQUSETIONDONEDIALOG_H
