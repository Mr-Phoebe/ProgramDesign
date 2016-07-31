#ifndef FILEWINDOW_H
#define FILEWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "fileSystem.h"
#include <QStandardItemModel>
#include <QTextCodec>
namespace Ui {
class fileWindow;
}

class fileWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit fileWindow(QWidget *parent = 0);
    ~fileWindow();
    QString getFilePathFromUI();

private:
    Ui::fileWindow *ui;
    QTimer *timer;
    QStandardItemModel *goodsModel;
public slots:
    void run();
private slots:
    QList<QStandardItem *> printTree(int id);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_lineEdit_destroyed();
};

#endif // FILEWINDOW_H
