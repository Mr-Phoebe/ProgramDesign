#ifndef SHOWANSWERDIALOG_H
#define SHOWANSWERDIALOG_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
    class ShowAnswerDialog;
}

class ShowAnswerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowAnswerDialog(QWidget *parent = 0);
    ~ShowAnswerDialog();
    void setListwigitItem();
    void getFindSum(int);
signals:
    void praise_btn_clicked();
private slots:
    void on_AnswerButton_clicked();
    //void showDe(QListWidgetItem *);
    void on_ExitButton_clicked();
    /*protected slots:
    // 点击子窗口中按钮的slot
    void ClickedBtn()
    {
        // 触发子窗口的信号给父窗口接收。
        emit praise_btn_Event();
    }
    */

    void on_nextPageBtn_clicked();

    void on_lastPageBtn_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_listWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::ShowAnswerDialog *ui;

};

#endif // SHOWANSWERDIALOG_H
