#ifndef SHOWFOCUSLISTDIALOG_H
#define SHOWFOCUSLISTDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
    class ShowFocusListDialog;
}

class ShowFocusListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowFocusListDialog(QWidget *parent = 0);
    ~ShowFocusListDialog();

private slots:
    void on_ReturnButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::ShowFocusListDialog *ui;
};

#endif // SHOWFOCUSLISTDIALOG_H
