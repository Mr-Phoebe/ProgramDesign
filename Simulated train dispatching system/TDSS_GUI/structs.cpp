#include "structs.h"

ULL t;

int remainingTime;

int trackNum;
Track tracks[MAX_TRACK_NUM];
PublicTrack publicTracks[MAX_TRACK_NUM][MAX_TRACK_NUM];
int trainNum;
Train trains[MAX_TRAIN_NUM];

int intend[MAX_TRACK_NUM][MAX_TRACK_NUM];
int first[MAX_TRAIN_NUM][MAX_TRAIN_NUM];

Strategy strategy = FAST_FIRST;

QString strategyStr[] =
{
    "快车优先",
    "交替优先",
    "人工控制"
};

Deque trainsQ[MAX_TRACK_NUM][MAX_TRACK_NUM];

void changeInOutPoint(int oneTrack, int anotherTrack)
{
     int tempInPoint = publicTracks[oneTrack][anotherTrack].inPoint;
     publicTracks[oneTrack][anotherTrack].inPoint = tracks[oneTrack].peremeter - publicTracks[oneTrack][anotherTrack].outPoint;
     publicTracks[oneTrack][anotherTrack].outPoint = tracks[oneTrack].peremeter - tempInPoint;
     publicTracks[oneTrack][anotherTrack].midPoint = (publicTracks[oneTrack][anotherTrack].inPoint + publicTracks[oneTrack][anotherTrack].outPoint) / 2.;
}

bool cmp(int a, int b)
{
    return trains[a].startPos < trains[b].startPos;
}

double PublicTrack::getX(int curTrack, int anotherTrack, int d)
{
    double length = tracks[curTrack].length;
    double width = tracks[curTrack].width;
    double peremeter = tracks[curTrack].peremeter;
    TrainDir dir = tracks[curTrack].dir;
    double curPos = (d == 0) ? publicTracks[curTrack][anotherTrack].inPoint
                               : publicTracks[curTrack][anotherTrack].outPoint;
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

double PublicTrack::getY(int curTrack, int anotherTrack, int d)
{
    double length = tracks[curTrack].length;
    double width = tracks[curTrack].width;
    double peremeter = tracks[curTrack].peremeter;
    TrainDir dir = tracks[curTrack].dir;
    double curPos = (d == 0) ? publicTracks[curTrack][anotherTrack].inPoint
                               : publicTracks[curTrack][anotherTrack].outPoint;

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

void initDeque()
{
    //sort(trains,trains+trainNum,cmp);
    for(int i(0); i < trainNum; ++i)
        for(int j(0); j < i; ++j)
            first[i][j]=i;

    std::vector<int> TrainsInTrack[MAX_TRACK_NUM];

    for (int i(0); i < trainNum; ++i)
    {
        TrainsInTrack[trains[i].startTrack].push_back(i);
    }
    for(int i(0); i < trainNum; ++i)
    {
        int oneTrack = -1,anotherTrack = -1;
        for(int j(0); j < trainNum; ++j)
            if(publicTracks[i][j].exist)
            {
                if(oneTrack == -1)oneTrack = j;
                else anotherTrack = j;
            }
        publicTracks[i][oneTrack].next = anotherTrack;
        publicTracks[i][anotherTrack].next = oneTrack;
    }


    for (int i(0); i < trainNum; ++i)
    {
        int trackNo = trains[i].startTrack;
        if (tracks[trackNo].dir == WHATEVER)
        {
            tracks[trackNo].dir = trains[i].dir;
            if(tracks[trackNo].dir == CNTRCLKWISE)
            {
                trains[i].startPos = tracks[trackNo].peremeter  - trains[i].startPos;
                for(int j(0); j < trackNum; ++j)
                    if(publicTracks[trackNo][j].exist)
                    {
                        changeInOutPoint(trackNo,j); //change inPoint outPoint
                    }
            }
        }
    }

    for (int i(0); i < trackNum; ++i)
        for (int j(0); j < trackNum; ++j) if(i != j && publicTracks[i][j].exist)
        {
            if (tracks[i].dir != WHATEVER)
            {
                std::sort(TrainsInTrack[i].begin(), TrainsInTrack[i].end(), cmp);
                int anotherPubTrackNo=publicTracks[i][j].next;
                if(publicTracks[i][j].inPoint < publicTracks[i][anotherPubTrackNo].inPoint)
                {
                    int headPos = -1;
                    for (int k(0); k < TrainsInTrack[i].size(); ++k)
                    {
                        int curTrain = TrainsInTrack[i][k];
                        if (trains[curTrain].startPos <=  publicTracks[i][j].inPoint)
                            headPos = k;
                        else break;

                    }
                    int pos=headPos;
                    for (pos ; pos >= 0; --pos)
                    {
                        int curTrain = TrainsInTrack[i][pos];
                        trainsQ[i][j].pushBack(curTrain);
                    }
                    for (pos = TrainsInTrack[i].size()-1; pos >= 0; --pos)
                    {
                        int curTrain = TrainsInTrack[i][pos];
                        if (trains[curTrain].startPos < publicTracks[i][anotherPubTrackNo].outPoint)
                            break;
                        trainsQ[i][j].pushBack(TrainsInTrack[i][pos]);
                    }
                }
                else
                {
                    int headPos = -1;
                    for (int k(0); k < TrainsInTrack[i].size(); ++k)
                    {
                        int curTrain = TrainsInTrack[i][k];
                        if (trains[curTrain].startPos <= publicTracks[i][j].inPoint)
                            headPos = k;
                        else break;

                    }
                    int pos=headPos;
                    for (pos ; pos >= 0; --pos)
                    {
                        int curTrain = TrainsInTrack[i][pos];
                        if (trains[curTrain].startPos < publicTracks[i][anotherPubTrackNo].outPoint)
                            break;
                        trainsQ[i][j].pushBack(curTrain);
                    }
                }
            }
        }
}
