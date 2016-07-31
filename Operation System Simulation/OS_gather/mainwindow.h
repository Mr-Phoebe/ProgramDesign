#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QStandardItemModel>
#include "taskmanager.h"
#include <QItemDelegate>
#include <QPainter>
#include <QDebug>
#include <QLabel>
#include "filewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initTable(QStandardItemModel  *model, char* headline[], int count);
    void updateReadyTable();
    void updateWaitingTable();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QStandardItemModel  *CPUmodel;
    QStandardItemModel  *IOmodel;
    int processCPU;
    int processIO;

public slots:
    void run();
private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};

class Delegate :public QItemDelegate
{
    Q_OBJECT
public:
    Delegate(QWidget *parent =0):QItemDelegate(parent){}
    void paint(QPainter *painter, const QStyleOptionViewItem &option,const QModelIndex &index)const
    {

        painter->fillRect(option.rect, QBrush(qRgb(255, 255, 191)));


        QItemDelegate::paint(painter, option, index);
    }
};

#endif // MAINWINDOW_H
