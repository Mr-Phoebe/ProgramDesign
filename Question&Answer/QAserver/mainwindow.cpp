#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);
    server = new QTcpServer();
    server->listen(QHostAddress::Any, 6665);
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::acceptConnection()
{
    clientConnection = server->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
    connect(clientConnection, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(error()));
}

void MainWindow::readClient()
{
    QByteArray datagram;
    datagram.resize(clientConnection->size());
    clientConnection->read(datagram.data(),datagram.size());
    QDataStream in(&datagram,QIODevice::ReadOnly);
    int type;
    in >> type;
    if(type <= INITUSER)
    {
        qDebug()<<"INIT";
        this->sendMessage(MessageType(type));
    }
    else if(type == LOGIN)
    {
        qDebug()<<"LOGIN";
        QString id, pass;
        in >> id >> pass;
        this->sendMessage(LOGIN, checkhas(id, pass));
    }
    else if(type == REGISTER)
    {
        qDebug()<<"REGISTER";
        QString id, name, pass;
        in >> id >> name >> pass;
        this->setInfo(id, name, pass);
    }
    else if(type == ANSWER)
    {
        qDebug()<<"ANSWER";
        int size;
        in >> size;
        SumAnswerList.clear();
        for(int i = 0; i < SumQuestionList.size(); i++)
        {
            SumQuestionList[i].clearAnswer();
        }
        for(int i = 0; i < size; i++)
        {
            Answer Answersubmit;
            int basicInf, prasizeNum;
            QString userId, creatTime, basicCon;
            in >> basicInf;
            in >> userId;
            in >> creatTime;
            in >> prasizeNum;
            in >> basicCon;
            Answersubmit.setBasicInfoId(basicInf);
            Answersubmit.setCreatUserId(userId);
            Answersubmit.setCreatTime(creatTime);
            Answersubmit.setPraiseNum(prasizeNum);
            Answersubmit.setBasicContent(basicCon);

            SumAnswerList.push_back(Answersubmit);
            SumQuestionList[basicInf].addAnswer(SumAnswerList.size()-1);
        }
        this->setInfo(QString::fromLocal8Bit("系统出错"));
    }
    else if(type == ANSWERADD)
    {
        qDebug()<<"ANSWERADD";
        Answer Answersubmit;
        int basicInf, prasizeNum;
        QString userId, creatTime, basicCon;
        in >> basicInf;
        in >> userId;
        in >> creatTime;
        in >> prasizeNum;
        in >> basicCon;
        Answersubmit.setBasicInfoId(basicInf);
        Answersubmit.setCreatUserId(userId);
        Answersubmit.setCreatTime(creatTime);
        Answersubmit.setPraiseNum(prasizeNum);
        Answersubmit.setBasicContent(basicCon);

        SumAnswerList.push_back(Answersubmit);
        SumQuestionList[basicInf].addAnswer(SumAnswerList.size()-1);

        this->answerAdd(Answersubmit);
    }
    else if(type == QUESTION)
    {
        qDebug()<<"QUESTION";
        Question QuestionReadyToAdd;
        int basicInf;
        QString userId, creatTime, questionTitle, basicCon;
        in >> basicInf;
        in >> userId;
        in >> creatTime;
        in >> questionTitle;
        in >> basicCon;
        QuestionReadyToAdd.setBasicInfoId(basicInf);
        QuestionReadyToAdd.setCreatUserId(userId);
        QuestionReadyToAdd.setCreatTime(creatTime);
        QuestionReadyToAdd.setQuestionTitle(questionTitle);
        QuestionReadyToAdd.setBasicContent(basicCon);

        SumQuestionList.push_back(QuestionReadyToAdd);
        this->questionAdd(QuestionReadyToAdd);
    }
    else if(type == FOCUS)
    {
        qDebug()<<"FOCUS";
        int size, num;
        QList<QString> ls;
        QString tmp;
        in >> size;
        for(int i = 0; i < size; i++)
        {
            ls.clear();
            in >> num;
            for(int j = 0; j < num; j++)
            {
                in >> tmp;
                ls.push_back(tmp);
            }
            SumUserList[i].setFocuslist(ls);
        }
        this->setInfo();
    }
    else
    {
        QMessageBox::critical(this, "Error", QString::fromLocal8Bit("数据错误"));
    }
}

void MainWindow::error()
{
    //update UI and close
    QMessageBox::critical(this, "Error", clientConnection->errorString());
    clientConnection->close();
}

int MainWindow::checkhas(QString InputId, QString InputPassword)
{
    if(UserId.size() == 0)
        return -1;
    for(int j = 0; j < SumUserList.size(); j++)
    {
        if(SumUserList[j].getUserId() == InputId && SumUserList[j].getUserPasserword() == InputPassword)
        {
            return j;
        }
    }
    return -1;
}


void MainWindow::sendMessage(MessageType type)
{
    if(type == INITQUE)
    {
        this->sendQue();
    }
    else if(type == INITANS)
    {
        this->sendAns();
    }
    else if(type == INITUSER)
    {
        this->sendUser();
    }
    else
    {
        QMessageBox::critical(this, "Error", QString::fromLocal8Bit("系统错误"));
    }
}


void MainWindow::sendMessage(MessageType type, int i)
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << type << i;
    clientConnection->write(data);
    clientConnection->close();
}


void MainWindow::sendUser()
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    int num = SumUserList.size();
    QList<QString> ls;
    out << quint16(0);
    out << INITUSER << num;
    for(int i = 0; i < num; i++)
    {
        User tmpUser = SumUserList[i];
        out << tmpUser.getUserId();
        out << tmpUser.getUserName();
        out << tmpUser.getUserPasserword();
        ls = tmpUser.getUserFocuslist();
        out << ls.size();
        for(int j = 0; j < ls.size(); j++)
        {
            out << ls[j];
        }
    }
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));
    clientConnection->write(data);
}

void MainWindow::sendQue()
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    int num = SumQuestionList.size();
    out << quint16(0);
    out << INITQUE << num;
    for(int i = 0; i < num; i++)
    {
        Question QuestionReadyToAdd = SumQuestionList[i];
        out << QuestionReadyToAdd.getBasicInfoId();
        out << QuestionReadyToAdd.getCreatUserId();
        out << QuestionReadyToAdd.getCreatTime();
        out << QuestionReadyToAdd.getQuestionTitle();
        out << QuestionReadyToAdd.getBasicContent();
    }
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));
    clientConnection->write(data);
}

void MainWindow::sendAns()
{
    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << quint16(0);
    out << INITANS << SumAnswerList.size();
    for(int i = 0; i < SumAnswerList.size(); i++)
    {
        out << SumAnswerList[i].getBasicInfoId();
        out << SumAnswerList[i].getCreatUserId();
        out << SumAnswerList[i].getCreatTime();
        out << SumAnswerList[i].getPasiseNum();
        out << SumAnswerList[i].getBasicContent();
    }
    out.device()->seek(0);
    out << quint16(data.size() - sizeof(quint16));
    clientConnection->write(data);
}


void MainWindow::setInfo()
{
    QString filepath("User_focus.txt");
    QFile file(filepath);
    if(!file.open(QIODevice::ReadWrite |QIODevice::Text))
    {
        //QMessageBox::critical(NULL, QObject::tr("提示"), QObject::tr("系统出错"));
    }
    QTextStream out(&file);

    for(int j = 0; j < SumUserList.size();j++)
    {
        QList<QString> ls = SumUserList[j].getUserFocuslist();
        for(int i = 0; i < ls.size(); i++)
        {
            out << ls[i] << endl;
        }
        out << "end" << endl;
    }
    file.close();
}

void MainWindow::setInfo(QString tip)
{
    QFile file("Answer_Info.txt");
    try
    {
        if(!file.open(QIODevice::ReadWrite|QIODevice::Text ))
        {
            throw tip;
        }
        else
        {
            QTextStream out(&file);
            for(int i = 0; i < SumAnswerList.size(); i++)
            {
                out << SumAnswerList[i].getBasicInfoId()<<endl;
                out << SumAnswerList[i].getCreatUserId()<<endl;
                out << SumAnswerList[i].getCreatTime()<<endl;
                out << SumAnswerList[i].getPasiseNum()<<endl;
                out << SumAnswerList[i].getBasicContent()<<endl;
            }
            file.close();
        }
    }
    catch(const QString a)
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("提示"), a);
    }
}

void MainWindow::setInfo(QString id, QString name, QString pass)
{
    QString filepath("User_Info.txt");
    QFile file(filepath);
    MainUser.setUserId(id);
    MainUser.setUserName(name);
    MainUser.setUserPassword(pass);
    if(!file.open(QIODevice::ReadWrite |QIODevice::Text |QIODevice::Append))
    {
        QMessageBox::critical(NULL,QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("系统出错"));
    }
    else
    {
        QTextStream out(&file);
        out << MainUser.getUserId() << endl;
        out << MainUser.getUserName() << endl;
        out << MainUser.getUserPasserword() << endl;
        SumUserList.push_back(MainUser);
        UserId.push_back(id);
        UserPassword.push_back(pass);
        file.close();
    }
}

void MainWindow::answerAdd(Answer Answersubmit)
{
    QString filepath("Answer_Info.txt");
    QFile file(filepath);
    if(!file.open(QIODevice::ReadWrite |QIODevice::Text |QIODevice::Append))
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("系统出错"));
    }
    else
    {
        QTextStream out(&file);
        out << Answersubmit.getBasicInfoId() << endl;
        out << Answersubmit.getCreatUserId() << endl;
        out << Answersubmit.getCreatTime() << endl;
        out << Answersubmit.getPasiseNum() << endl;
        out << Answersubmit.getBasicContent() << endl;
        file.close();
    }
}

void MainWindow::questionAdd(Question QuestionReadyToAdd)
{
    QString filepath("Question_Info.txt");
    QFile file(filepath);
    try
    {
        if(!file.open(QIODevice::ReadWrite |QIODevice::Text |QIODevice::Append))
        {
            throw QString::fromLocal8Bit("系统出错！");
        }
        else
        {
            QTextStream out(&file);
            out << QuestionReadyToAdd.getBasicInfoId() << endl;
            out << QuestionReadyToAdd.getCreatUserId() << endl;
            out << QuestionReadyToAdd.getCreatTime() << endl;
            out << QuestionReadyToAdd.getQuestionTitle() << endl;
            out << QuestionReadyToAdd.getBasicContent() << endl;
            file.close();
        }
    }
    catch(const QString a)
    {
        QMessageBox::critical(NULL, QString::fromLocal8Bit("提示"), a);
    }
}
