#ifndef LOG_DIALOG_H
#define LOG_DIALOG_H

#include <QDialog>

namespace Ui {
class log_Dialog;
}

class log_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit log_Dialog(QWidget *parent = 0);
    ~log_Dialog();

private:
    Ui::log_Dialog *ui;
};

#endif // LOG_DIALOG_H
