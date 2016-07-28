#include <QtGui>
#include <QApplication>
#include <QTextCodec>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "mywidget.h"
#include "totalclass.h"

int choose = 0;
int choice = 0;
int QId = 0;
int AId = 0;
int siz = 0;
int qu = 0;
int qsi = 0;
int currentpage = 0;
int curanspage = 0;
int itemnumber = 0;
int FocusId = 0;
int focusquespage = 0;
int fochoice = 0;

QString temp("Hello!");


vector<QString>UserId;
vector<QString>UserPassword;

QList<int>AnswerPriseList;
QList<QString>UserFocusList;
QList<User>SumUserList;
QList<Question>SumQuestionList;
QList<int>SumFocusQuestionList;
QList<Answer>SumAnswerList;
QList<int>AnswerItemList;
QList<int>QuestionItemList;
QList<int>SumFocusAnswerList;
User MainUser;
Question QuestionReadyToAdd;
Answer Answersubmit;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWidget w;
    w.show();

    return a.exec();
}


