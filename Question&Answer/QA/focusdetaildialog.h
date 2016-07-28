#ifndef FOCUSDETAILDIALOG_H
#define FOCUSDETAILDIALOG_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class focusDetailDialog;
}

class focusDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit focusDetailDialog(QWidget *parent = 0);
    ~focusDetailDialog();

    void setFocusName(const QString &focusname);

    void showFocusName();

    void updateAnswer();

    void updateQuesiton();

private slots:
    void on_BackpushButton_clicked();

    void on_detailtableView_doubleClicked(const QModelIndex &index);

    void on_detailtableView2_doubleClicked(const QModelIndex &index);

    void on_BackpushButton2_clicked();

private:
    Ui::focusDetailDialog *ui;
    QString focusname;
    QStandardItemModel *model;
    QStandardItemModel *model2;
};

#endif // FOCUSDETAILDIALOG_H
