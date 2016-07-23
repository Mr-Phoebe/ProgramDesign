#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QIcon>
#include <QTime>
#include <QTimer>
#include <QDate>
#include <QTextCodec>
#include <QModelIndex>
#include <QInputDialog>
#include "plane.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void initLoginPage();
    void initMainPage();
    void initOrderPage();
    void initCheckInPage();
    void initTime();

    void resetOrderPage();
    void resetCheckInPage();
    void resetEvluatePage();
    void resetSetPage();

    void updateOrderPage();
    void updateCheckInPage();
    void updateRoomInfoPage();
    void updateRoomInfoPage_2();
    void updatePayPage();
    void updateEvluatePage();
    void updateUsersInfoPage();
    void updatePlanePage();

    void dealOrderPage();
    void dealCheckInPage();
    void dealPayPage();
    void dealEvluatePage();

    bool ExecuteUpdateRoomTable(const QString&, const int&);
    void ExecuteUpdateStatistic(const int);
    void ExecuteUpdateCheckInTable(const QString&,
                                   const int&,
                                   const QString&,
                                   const QString&,
                                   const QString&);

    bool isValidCheckInCustomer(const QString&, const QString&, const QString&);
    bool isEmptyCheckInCustomer(const QString&, const QString&, const QString&);
    bool isValidCheckInDate(QString& checkin,int size);

    void keyPressEvent(QKeyEvent *);

    plane showplane;

    int level;

    Ui::Widget *ui;
    QTime ti;
    QTimer *ack;
    QDate thedate;

private slots:
    void on_submitButton_clicked();
    void on_moneyAddButton_clicked();
    void on_commitButton_2_clicked();
    void on_cancelButton_clicked();
    void on_newCustomerButton_clicked();
    void on_commitButton_clicked();
    void on_exitButton_clicked();
    void on_loginButton_clicked();
    void updateAllInfo();
    void processOrderCustomer();
    void processCheckInCustomer(int, int);
    void on_Exit_clicked();
    void on_About_clicked();
    void on_ExitID_clicked();
    void on_Statistics_clicked();
    void on_Display_clicked();
    void on_roomInfoTableWidget_doubleClicked(const QModelIndex &index);
    void on_queryButton_clicked();
    void on_RoomButton_clicked();
    void on_RoombackButton_clicked();
    void on_UsersButton_clicked();
    void on_DeleteUsersButton_clicked();
    void on_UsersInfoTableWidget_cellDoubleClicked(int row, int column);
    void on_UsersInfoTableWidget_pressed(const QModelIndex &index);
    void updateTime();
};

#endif // WIDGET_H
