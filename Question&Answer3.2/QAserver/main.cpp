#include "mainwindow.h"
#include <QApplication>
#include "totalclass.h"



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

void getQuestionInfo();
void getAnswerInfo();
void getUserInfo();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    getQuestionInfo();
    getAnswerInfo();
    getUserInfo();
    return a.exec();
}


void getQuestionInfo()
{
    QFile file("Question_Info.txt");
    int i=1;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //QMessageBox::critical(NULL, QObject::tr("提示"), QObject::tr("文件不存在，无法打开文件"));
        //create the file
    }
    else
    {
        QString line,title,time,createid,content;
        QTextStream in(&file);
        while(!in.atEnd())
        {
            line = in.readLine().replace(QString("\n"),QString(""));
            if(i%5==0)
            {
                content = line;
                QuestionReadyToAdd.setBasicContent(content);
                SumQuestionList.push_back(QuestionReadyToAdd);
            }
            else if(i%5==1)
            {
                QuestionReadyToAdd.setBasicInfoId(i);
            }
            else if(i%5==2)
            {
                createid = line;
                QuestionReadyToAdd.setCreatUserId(createid);
            }
            else if(i%5==3)
            {
                time = line;
                QuestionReadyToAdd.setCreatTime(time);
            }
            else
            {
                title=line;
                QuestionReadyToAdd.setQuestionTitle(title);
            }
            i = (i+1)%5;
    }
    file.close();
   }
}

void getAnswerInfo()
{
    QFile filename("Answer_Info.txt");
    int j=1;
    if(!filename.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //QMessageBox::critical(NULL, QObject::tr("提示"), QObject::tr("文件不存在，无法打开文件"));
        //create the file
    }
    else
    {
        int id,prise;
        QString line,sid,answerid,answertime,answerinfo,answerprise;
        QTextStream in(&filename);
        while(!in.atEnd())
        {
            line = in.readLine().replace(QString("\n"),QString(""));
            if(j%5 == 1)
            {
                sid = line;
                id = sid.toInt();
                Answersubmit.setBasicInfoId(id);
                //UserId.push_back(id);
            }
            else if(j%5 == 2)
            {
                answerid=line;
                Answersubmit.setCreatUserId(answerid);
            }
            else if(j%5 == 3)
            {
                answertime=line;
                Answersubmit.setCreatTime(answertime);
            }
            else if(j%5 == 4)
            {
                answerprise = line;
                prise = answerprise.toInt();
                Answersubmit.setPraiseNum(prise);
            }
            else
            {
                answerinfo = line;
                Answersubmit.setBasicContent(answerinfo);
                SumAnswerList.push_back(Answersubmit);
                SumQuestionList[Answersubmit.getBasicInfoId()].addAnswer(SumAnswerList.size()-1);
            }
            j++;
        }
        filename.close();
    }
}

void getUserInfo()
{
    QFile filepath("User_Info.txt");
    QFile filepath2("User_focus.txt");
    int j=1, k=1;
    if(!filepath.open(QIODevice::ReadOnly | QIODevice::Text) ||
       !filepath2.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        //QMessageBox::critical(NULL, QObject::tr("提示"), QObject::tr("文件不存在，无法打开文件"));
        //create the file
    }
    else
   {
        QString line,id,password;
        QTextStream userin(&filepath);
        QTextStream focusin(&filepath2);
        while(!userin.atEnd())
        {
            line = userin.readLine().replace(QString("\n"),QString(""));
            if(j == k)
            {
                MainUser.reset();
                k += 3;
                id = line;
                UserId.push_back(id);
                MainUser.setUserId(id);
                while(!focusin.atEnd())
                {
                    line = focusin.readLine().replace(QString("\n"),QString(""));
                    if(line == "end")
                    {
                        break;
                    }
                    else
                    {
                        MainUser.setUserFocuslist(line);
                    }
                }
            }
            else if(j%3==0)
            {
                password = line;
                UserPassword.push_back(password);
                MainUser.setUserPassword(password);
                SumUserList.push_back(MainUser);
            }
            j++;
        }
        filepath.close();
    }
}
