#ifndef SHOWQUESTIONDIALOG_H
#define SHOWQUESTIONDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QDateTime>

namespace Ui {
    class ShowQuestionDialog;
}

class ShowQuestionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ShowQuestionDialog(QWidget *parent = 0);
    ~ShowQuestionDialog();
    void setListwigitItem();
    void setAllQuestion();
    void setReqQuestion(QString need);
    void setTimQuestion(QDateTime bet,QDateTime ent);
    void sortQuestion();

private slots:
    void showDetail(QListWidgetItem *);

    void on_retButton_clicked();

    void on_askquesBtn_clicked();

    void on_nextpageButton_clicked();

    void on_lastpageButton_clicked();

    void on_searchButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::ShowQuestionDialog *ui;
};

#endif // SHOWQUESTIONDIALOG_H
