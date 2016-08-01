#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <windows.h>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <QObject>
#include <QDateTime>
#include <QLabel>
#include <QPropertyAnimation>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QString>
#include <sstream>

#include "cmdDialog.h"

using namespace std;

typedef unsigned long long ULL;

#define ONE_SEC 1000
#define UNIT_TIME 15
#define UNITS_PER_SEC 50

extern ULL t;
extern int remainingTime;

class CmdDialog;

#define MAX_TRACK_NUM 100

enum TrainType
{
    SLOW, FAST
};

enum TrainDir
{
    CLKWISE = 1, CNTRCLKWISE = -1, WHATEVER = 0
};

enum TrainState
{
    STOP, RUN, WAIT
};

struct Track
{
    double length;
    double width;
    double peremeter;
    TrainDir dir; //WHATEVER
    double x0, y0;
};

extern int trackNum;
extern Track tracks[MAX_TRACK_NUM];

enum PublicTrackState
{
    IDLE, BUSY
};
enum BtnColor
{
    GREEN, RED
};

struct PublicTrack
{
    bool exist; //1
    double inPoint, outPoint, midPoint;
    PublicTrackState state;
    int next;
    QLabel* inPointLbl;
    QLabel* outPointLbl;
    BtnColor color;

    double getX(int curTrack, int anotherTrack, int d);
    double getY(int curTrack, int anotherTrack, int d);
};

extern PublicTrack publicTracks[MAX_TRACK_NUM][MAX_TRACK_NUM];

void changeInOutPoint(int oneTrack, int anotherTrack);

extern int intend[MAX_TRACK_NUM][MAX_TRACK_NUM];

class Train : public QObject
{    
    Q_OBJECT
    public:
        int id;
        TrainType type;
        TrainDir dir;
        int startTime;
        int startTrack;
        double startPos;
        double speed;
        bool pass[MAX_TRACK_NUM];
        int stayDur[MAX_TRACK_NUM][MAX_TRACK_NUM];

        TrainState curState;
        int curTrack;
        double curPos;
        double curSpeed; //initially speed
        //bool enteringPublicTrack;
        bool inPublicTrack; //0
        //int anotherTrack;
        int restStayDur; //-1
        bool moved;
        bool hasChangedTrack;
        bool waitForFrontTrain;
        bool started;

        QLabel* trainLbl;
        CmdDialog* cmdDialog;

        double getX()
        {
            double length = tracks[curTrack].length;
            double width = tracks[curTrack].width;
            double peremeter = tracks[curTrack].peremeter;

            switch (dir)
            {
                case CLKWISE:
                {
                    if (curPos < length)
                        return curPos;
                    else if (curPos < length + width)
                        return length;
                    else if (curPos < length + width + length)
                        return peremeter - width - curPos;
                    else
                        return 0.;
                }
                case CNTRCLKWISE:
                {
                    if (curPos < width)
                        return 0.;
                    else if (curPos < width + length)
                        return curPos - width;
                    else if (curPos < width + length + width)
                        return length;
                    else
                        return peremeter - curPos;
                }
            }
        }

        double getY()
        {
            double length = tracks[curTrack].length;
            double width = tracks[curTrack].width;
            double peremeter = tracks[curTrack].peremeter;

            switch (dir)
            {
                case CLKWISE:
                {
                    if (curPos < length)
                        return 0.;
                    else if (curPos < length + width)
                        return curPos - length;
                    else if (curPos < length + width + length)
                        return width;
                    else
                        return peremeter - curPos;
                }
                case CNTRCLKWISE:
                {
                    if (curPos < width)
                        return curPos;
                    else if (curPos < width + length)
                        return width;
                    else if (curPos < width + length + width)
                        return peremeter - length - curPos;
                    else
                        return 0.;
                }
            }
        }

    public slots:
        void getCmd()
        {
            cout << "getCmd train " << id << endl;
            cmdDialog = new CmdDialog(id);
            cmdDialog->exec();
        }
};

#define MAX_TRAIN_NUM 26

enum Strategy
{
    FAST_FIRST, ALTERNATIVE, MANUAL_CTRL
};

#define MAX_Q_SIZE (MAX_TRAIN_NUM << 1)

struct Deque
{
    int data[MAX_Q_SIZE];
    int front = 0, rear = 0;
    int size = 0;

    int& operator [](int i)
    {
        return data[(front + i) % MAX_Q_SIZE];
    }

    void pushFront(int trainId)
    {
        ((--front) += MAX_Q_SIZE) %= MAX_Q_SIZE;
        data[front] = trainId;
        ++size;
    }

    void pushBack(int trainId)
    {
        data[rear] = trainId;
        (++rear) %= MAX_Q_SIZE;
        ++size;
    }

    int getTop()
    {
        return size ? data[front] : -1;
    }

    void popFront()
    {
        if (size)
        {
            --size;
            (++front) %= MAX_Q_SIZE;
        }
    }

    void popBack()
    {
        if (size)
        {
            --size;
            ((--rear) += MAX_Q_SIZE) %= MAX_Q_SIZE;
        }
    }
};

void initDeque();

extern int trackNum;
extern Track tracks[MAX_TRACK_NUM];
extern PublicTrack publicTracks[MAX_TRACK_NUM][MAX_TRACK_NUM];
extern int trainNum;
extern Train trains[MAX_TRAIN_NUM];

extern int intend[MAX_TRACK_NUM][MAX_TRACK_NUM];
extern int first[MAX_TRAIN_NUM][MAX_TRAIN_NUM];

extern Strategy strategy;

extern QString strategyStr[];

extern Deque trainsQ[MAX_TRACK_NUM][MAX_TRACK_NUM];

#define INF 0x3f3f3f3f //无穷大

#endif // STRUCTS_H

