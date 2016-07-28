#ifndef INPUTEMPTYDIALOG_H
#define INPUTEMPTYDIALOG_H

#include <QDialog>

namespace Ui {
    class InputEmptyDialog;
}

class InputEmptyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputEmptyDialog(QWidget *parent = 0);
    ~InputEmptyDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::InputEmptyDialog *ui;
};

#endif // INPUTEMPTYDIALOG_H
