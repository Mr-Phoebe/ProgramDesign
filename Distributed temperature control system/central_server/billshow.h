#ifndef BILLSHOW_H
#define BILLSHOW_H

#include <QMainWindow>

namespace Ui {
class Billshow;
}

class Billshow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Billshow(QWidget *parent = 0);
    void deleteTheTable();
    ~Billshow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Billshow *ui;
    QString getBillString();
    QString getLogString(double);
    void writeToLog();
};

#endif // BILLSHOW_H
