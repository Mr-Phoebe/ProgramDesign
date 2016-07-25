#ifndef TOTALCLASS_H
#define TOTALCLASS_H


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <time.h>
#include <QString>
#include <QObject>
#include <QtNetwork>

using namespace std;

enum MessageType {INITQUE,INITANS,INITUSER,LOGIN,REGISTER,ANSWER,ANSWERADD,QUESTION,FOCUS};

class BasicInfo
{
public:
    void setCreatTime(QString InputCreatTime)   {CreatTime=InputCreatTime;}
    QString getCreatTime()  {return CreatTime;}
    void setCreatUserId(QString UserId) {CreatUserId=UserId;}
    QString getCreatUserId()    {return CreatUserId;}
    void setBasicInfoId(int InputBasicInId) {BasicInfoId=InputBasicInId;}
    int  getBasicInfoId() {return BasicInfoId;}
    void setBasicContent(QString InputBasicContent) {BasicContent=InputBasicContent;}
    QString getBasicContent() {return BasicContent;}

    virtual void Creat(){}//定义为虚函数
    virtual QString getInfo_And_print()
    {
        return QString::number(this->getBasicInfoId()) +
               this->getCreatTime() +
               this->getBasicContent();
    }
private:
        QString CreatUserId;
        int    BasicInfoId;
        QString CreatTime;
        QString BasicContent;
};

class Question:public BasicInfo
{
    public:
    void setQuestionTitle(QString InputTitle) {QuestionTitle=InputTitle;}
    QString getQuestionTitle() {return QuestionTitle;}
    QString getInfo_And_print()
    {
        return QString::number(this->getBasicInfoId())
                + " " + this->getCreatTime()
                + " " + this->getQuestionTitle()
                + " " + this->getBasicContent();
    }
    void addAnswer(int i) {this->AnswerPos.push_back(i);}
    int getAnswerNumber() {return this->AnswerPos.size();}
    QList<int> getAnswer() {return this->AnswerPos;}

    ostream& operator << (ostream &os)
    {
        os<<this->getBasicInfoId()<<endl;
        os<<this->getCreatUserId().toStdString()<<endl;
        os<<this->getCreatTime().toStdString()<<endl;
        os<<this->getQuestionTitle().toStdString()<<endl;
        os<<this->getBasicContent().toStdString()<<endl;
        return os;
    }

    istream& operator >> (istream &is)
    {
        string temp;
        int tmp;
        is>>tmp;    this->setBasicInfoId(tmp);
        is>>temp;   this->setCreatUserId(QString::fromStdString(temp));
        is>>temp;   this->setCreatTime(QString::fromStdString(temp));
        is>>temp;   this->setQuestionTitle(QString::fromStdString(temp));
        is>>temp;   this->setBasicContent(QString::fromStdString(temp));
        return is;
    }

    private:
    QString  QuestionTitle;
    QList<int> AnswerPos;
};

class Answer:public BasicInfo
{
    public:
    void setPraiseNum(int InputPraiseNum) {PraiseNum=InputPraiseNum;}//设置答案的赞数
    void makePraise() {PraiseNum++;}
    int getPasiseNum(){return PraiseNum;}//返回答案的赞数
    void Creat() {Answer AnswerReadyToSubmit;}

    ostream& operator << (ostream &os)
    {
        os<<this->getBasicInfoId()<<endl;
        os<<this->getCreatUserId().toStdString()<<endl;
        os<<this->getCreatTime().toStdString()<<endl;
        os<<this->getPasiseNum()<<endl;
        os<<this->getBasicContent().toStdString()<<endl;
        return os;
    }
    istream& operator >> (istream &is)
    {
        string temp;
        int tmp;
        is>>tmp;    this->setBasicInfoId(tmp);
        is>>temp;   this->setCreatUserId(QString::fromStdString(temp));
        is>>temp;   this->setCreatTime(QString::fromStdString(temp));
        is>>temp;   this->setBasicContent(QString::fromStdString(temp));
        is>>tmp;    this->setPraiseNum(tmp);
        return is;
    }

    private:
    int PraiseNum;



};

class User
{
public :

    void setUserId(QString InputId)                     {UserId=InputId;}
    void setUserName(QString InputName)                 {UserName=InputName;}
    void setUserPassword(QString InputPassword)         {UserPassword=InputPassword;}
    void setFocuslist(QList<QString> Focuslist)         {this->UserFocuslist=Focuslist;}
    void setPriseList(QList<int> PriseList)             {this->AnswerPriseList=PriseList;}
    void setUserFocuslist(QString UserReadyToFocus)     {this->UserFocuslist.push_back(UserReadyToFocus);}
    void reset()
    {
        this->setUserId("");
        this->setUserName("");
        this->setUserPassword("");
        UserFocuslist.clear();
        AnswerPriseList.clear();
    }

    QString getUserId()                                 {return UserId;}
    QString getUserName()                               {return UserName;}
    QString getUserPasserword()                         {return UserPassword;}
    QList<QString> getUserFocuslist()                   {return this->UserFocuslist;}
    QList<int> getAnswerPriseList()                     {return this->AnswerPriseList;}

private:
    QString UserId;
    QString UserName;
    QString UserPassword;
    QList<QString> UserFocuslist;
    QList<int> AnswerPriseList;
};

extern int choose;
extern int choice;
extern int fochoice;
extern int QId;
extern int AId;
extern int FocusId;
extern int currentpage;
extern int curanspage;
extern int focusquespage;
extern int itemnumber;
extern int siz;
extern int qu;
extern int qsi;
extern QString temp;

extern vector<QString> UserId;
extern vector<QString> UserPassword;
extern QList<QString> UserFocusList;
extern QList<int> AnswerPriseList;
extern QList<int> AnswerItemList;
extern QList<int>QuestionItemList;

extern User MainUser;//当前用户
extern Question QuestionReadyToAdd;
extern Answer Answersubmit;
extern QList<Question>SumQuestionList;
extern QList<int>SumFocusQuestionList;
extern QList<Answer>SumAnswerList;
extern QList<int>SumFocusAnswerList;


extern QList<User>SumUserList;
#endif // TOTALCLASS_H
