#include "control.h"

//下一周期火车位置
inline double nextPos(int i)
{
    double ret(trains[i].curPos + trains[i].curSpeed * (1. / (double(UNITS_PER_SEC))));

    if (ret > tracks[trains[i].curTrack].peremeter)
        ret -= tracks[i].peremeter;

    return ret;
}

//判断某个位置是否在某个公共轨道内
inline bool in(double pos, int i, int j)
{
    return (pos >= publicTracks[i][j].inPoint
            && pos <= publicTracks[i][j].outPoint);
}

//判断某个位置是否即将进入或刚离开某个公共轨道
inline bool willIn(double pos, int i, int j)
{
    double p1(pos + INTEND_DIS),
           p2(pos - INTEND_DIS);

    if (p1 > tracks[i].peremeter)
        p1 -= tracks[i].peremeter;
    if (p2 < 0.)
        p2 += tracks[i].peremeter;

    return in(p1, i, j) || in(p2, i, j);
}

void getIntend()
{
    memset(intend, -1, sizeof(intend));

    for (int curTrack(0); curTrack < trackNum; ++curTrack)
        for (int anotherTrack(0); anotherTrack < trackNum; ++anotherTrack)
            if (publicTracks[curTrack][anotherTrack].exist
                && trainsQ[curTrack][anotherTrack].size)
            {
                int j = trainsQ[curTrack][anotherTrack].getTop();

                double _nextPos = nextPos(j);

                //检测冲突只需检测队首状态
                switch (trains[j].curState)
                {
                    //队首火车子在运行
                    case RUN:
                    {
                        //在公共轨道上
                        if (trains[j].inPublicTrack)
                        {
                            //还未等待，即restStayDur未初始化，（= -1）
                            //将其初始化为在该公共轨道上需等待的时间
                            //if (trains[j].restStayDur == -1)
                            //trains[j].restStayDur = trains[j].stayDur[curTrack][anotherTrack] * UNITS_PER_SEC;

                            if (tracks[anotherTrack].dir == WHATEVER)
                            {
                                if (trains[j].dir == CLKWISE)
                                    tracks[anotherTrack].dir = CLKWISE;
                                else
                                {
                                    tracks[anotherTrack].dir = CNTRCLKWISE;
                                    for(int k(0); k < trackNum; ++k)
                                        if(publicTracks[curTrack][k].exist)
                                        {
                                            changeInOutPoint(anotherTrack, k); //change inPoint outPoint
                                        }
                                }
                            }

                            //下一时刻该将超过轨道中点
                            if (in(_nextPos, curTrack, anotherTrack)
                                && _nextPos >= publicTracks[curTrack][anotherTrack].midPoint)
                            {
                                //若该车需等待，则状态转为STAY
                                if (trains[j].restStayDur == -1)
                                    trains[j].restStayDur = trains[j].stayDur[curTrack][anotherTrack] * UNITS_PER_SEC;

                                if (trains[j].restStayDur > 0)
                                    trains[j].curState = WAIT; 


                                //若该车需变轨（变到anotherTrack上）
                                else if (!trains[j].hasChangedTrack
                                         && trains[j].pass[anotherTrack])
                                {
                                    //将该车的信息变换为新轨道坐标下信息
                                    trains[j].curTrack = anotherTrack;

                                    if (trains[j].dir == tracks[anotherTrack].dir)
                                    {
                                        trains[j].curPos = publicTracks[anotherTrack][curTrack].inPoint
                                                           + (publicTracks[curTrack][anotherTrack].outPoint
                                                              - trains[j].curPos);

                                        if (trains[j].curPos > tracks[anotherTrack].peremeter)
                                            trains[j].curPos -= tracks[anotherTrack].peremeter;
                                        if (trains[j].curPos < 0.)
                                            trains[j].curPos += tracks[anotherTrack].peremeter;
                                    }
                                    else
                                    {
                                        trains[j].curPos = publicTracks[anotherTrack][curTrack].inPoint
                                                           + (trains[j].curPos
                                                              - publicTracks[curTrack][anotherTrack].inPoint);

                                        if (trains[j].curPos > tracks[anotherTrack].peremeter)
                                            trains[j].curPos -= tracks[anotherTrack].peremeter;
                                        if (trains[j].curPos < 0.)
                                            trains[j].curPos += tracks[anotherTrack].peremeter;
                                    }
                                    trains[j].restStayDur = 0;
                                    trains[j].dir = tracks[anotherTrack].dir;
                                    //将该车从当前公共轨道的队列弹出
                                    trainsQ[anotherTrack][curTrack].pushFront(j);
                                    //压入对偶的公共轨道的队列队首，交由对方处理
                                    trainsQ[curTrack][anotherTrack].popFront();
                                    trains[j].hasChangedTrack = true;
                                }
                            }
                        }
                        //若该车下一时刻会进入该公共轨道，发出请求，由dispatch()函数处理调度
                        else if (willIn(_nextPos, curTrack, anotherTrack))
                        {
                            if (publicTracks[curTrack][anotherTrack].state == IDLE)
                                intend[curTrack][anotherTrack] = j;
                            else
                                trains[j].curState = WAIT;
                        }

                        break;
                    }
                    case WAIT:
                    {
                        break;
                    }
                    case STOP:
                    {
                        break;
                    }
                }
            }
}

void dispatch()
{
    for (int i(0); i < trackNum; ++i)
        for (int j(0); j < i; ++j)
        {
            if (publicTracks[i][j].exist
                && ((~intend[i][j]) || ~intend[j][i]))
            {
                int a = intend[i][j],
                    b = intend[j][i];

                publicTracks[i][j].state = BUSY; //公共轨道标记为被占用
                publicTracks[j][i].state = BUSY;

                if (~a && ~b)
                {
                    switch(strategy)
                    {
                        case FAST_FIRST: //快车优先策略
                        {
                            if (trains[a].speed > trains[b].speed)
                            {
                                trains[a].curState = RUN;
                                trains[a].inPublicTrack = 1;
                                trains[b].curState = WAIT;
                                publicTracks[i][j].color = RED;

                            }
                            else if (trains[i].speed < trains[j].speed)
                            {
                                trains[a].curState = WAIT;
                                trains[b].curState = RUN;
                                trains[b].inPublicTrack = 1;
                                publicTracks[j][i].color = RED;
                            }
                            else goto CASE_ALTERNATIVE;

                            break;
                        }
                        case ALTERNATIVE: //交替优先策略
                        {
                            CASE_ALTERNATIVE:

                            if (first[a][b] == a)
                            {
                                trains[a].curState = RUN;
                                trains[a].inPublicTrack = 1;
                                trains[b].curState = WAIT;
                                first[a][b] = b;
                                publicTracks[i][j].color = RED;
                            }
                            else
                            {
                                trains[a].curState = WAIT;
                                trains[b].curState = RUN;
                                trains[b].inPublicTrack = 1;
                                first[a][b] = a;
                                publicTracks[j][i].color = RED;
                            }
                            break;
                        }
                        case MANUAL_CTRL: //人工控制策略
                        {
                            //fflush(stdin);

                            ManualCtrlDialog manualCtrlDialog(a, b);
                            manualCtrlDialog.exec();

                            if (a != manualCtrlDialog.getFirst())
                            {
                                publicTracks[j][i].color = RED;
                                swap(a, b);
                            }
                            else publicTracks[i][j].color = RED;

                            trains[a].curState = RUN;
                            trains[a].inPublicTrack = 1;
                            trains[b].curState = WAIT;

                            break;
                        }
                    }
                }
                else if (~intend[i][j])
                {
                    int a = intend[i][j];
                    trains[a].curState = RUN;
                    trains[a].inPublicTrack = 1;
                    publicTracks[i][j].color = RED;
                }
                else if (~intend[j][i])
                {
                    int a = intend[j][i];
                    trains[a].curState = RUN;
                    trains[a].inPublicTrack = 1;
                    publicTracks[j][i].color = RED;
                }
            }
        }
}

void stateTrans()
{
    for (int i(0); i < trainNum; ++i)
    {
        trains[i].moved = 0;
    }

    for (int curTrack(0); curTrack < trackNum; ++curTrack)
        for (int anotherTrack(0); anotherTrack < trackNum; ++anotherTrack)
            if (publicTracks[curTrack][anotherTrack].exist
                && trainsQ[curTrack][anotherTrack].size)
            {
                int size = trainsQ[curTrack][anotherTrack].size;
                int j; //当前火车
                int k = -1; //队列中的前一辆火车
                bool popped = 0;

                for (int i(0); i < size; k = j, ++i)
                {
                    j = trainsQ[curTrack][anotherTrack][i];
                    double _nextPos = nextPos(j);

                    switch (trains[j].curState)
                    {
                        case RUN:
                        {
                            if (!i) //队首
                            {

                                if (!trains[j].moved) //在该周期为发生位移，则发生位移
                                {
                                    trains[j].curPos = _nextPos;

                                    trains[j].moved = 1;  //need repeatedly initialization
                                }

                                if (trains[j].inPublicTrack //即将离开公共轨道
                                    && !willIn(trains[j].curPos, curTrack, anotherTrack))
                                {

                                    publicTracks[curTrack][anotherTrack].state = IDLE; //公共轨道标记为空闲
                                    publicTracks[anotherTrack][curTrack].state = IDLE;

                                    trains[j].inPublicTrack = 0;
                                    trains[j].restStayDur = -1;
                                    trains[j].hasChangedTrack = 0;
                                    popped = 1;
                                    int next = publicTracks[curTrack][anotherTrack].next;
                                    trainsQ[curTrack][next].pushBack(j); //进入下一队列
                                }

                                break;
                            }
                            else
                            {
                                if (i == 1) //队列中第二辆火车（可能在即将进入公共轨道，得特判）
                                {
                                    if (trains[k].inPublicTrack //前车未离开公共轨道
                                        && willIn(_nextPos, curTrack, anotherTrack))
                                        {
                                            trains[j].curState = WAIT; //等待公共轨道空闲
                                            break;
                                        }
                                }

                                //检测与前车是否有碰撞或追尾风险
                                double curDis = trains[k].curPos - trains[j].curPos;
                                double nxtDis = trains[k].curPos - _nextPos;

                                if (curDis * nxtDis < 0) //后车下一周期将超过前车（基本不可能发生）
                                {
                                    if ((trains[j].curPos = trains[k].curPos - SAFE_DIS) < 0.)
                                        trains[j].curPos += tracks[curTrack].peremeter;
                                    trains[j].curState = trains[k].curState;
                                    trains[j].curSpeed = trains[k].speed; //减速

                                    if (trains[k].curState != RUN) //前车若暂停或等待，后车也需等待
                                    {
                                        trains[j].curState = WAIT;
                                        trains[j].waitForFrontTrain = 1;
                                    }
                                }
                                else if (nxtDis < 0.)
                                {
                                    nxtDis += tracks[curTrack].peremeter;
                                }

                                if (nxtDis < SAFE_DIS) //后车下一周期与前车距离将小于安全距离
                                {
                                    if ((trains[j].curPos = trains[k].curPos - SAFE_DIS) < 0.)
                                        trains[j].curPos += tracks[curTrack].peremeter;
                                    trains[j].curState = trains[k].curState;
                                    trains[j].curSpeed = trains[k].speed; //减速

                                    if (trains[k].curState != RUN) //前车若暂停或等待，后车也需等待
                                    {
                                        trains[j].curState = WAIT;
                                        trains[j].waitForFrontTrain = 1;
                                    }
                                }
                                else
                                {
                                    trains[j].curPos = _nextPos; //无碰撞追尾危险则正常发生位移
                                    trains[j].curSpeed = trains[j].speed;
                                }
                            }

                            break;
                        }
                        case WAIT:
                        {
                            if (!i) //队首
                            {
                                if (trains[j].inPublicTrack) //在公共轨道中点则判断是否以停靠完毕
                                {
                                    if (trains[j].restStayDur == 1)
                                    {
                                        trains[j].curState = RUN;
                                        trains[j].restStayDur = 0;
                                        break;
                                    }
                                    else if (trains[j].restStayDur > 1)
                                        --trains[j].restStayDur;
                                }
                                else //轨道若已空闲则运行
                                {
                                    if (publicTracks[curTrack][anotherTrack].state == IDLE)
                                        trains[j].curState = RUN;
                                }
                            }
                            else
                            {
                                if (i == 1) //队列中第二辆火车，有可能正等待公共轨道，需特判
                                {
                                    //前车已离开公共轨道且公共轨道已空闲，则运行
                                    if (popped && publicTracks[curTrack][anotherTrack].state == IDLE)
                                        trains[j].curState = RUN;
                                }

                                trains[j].curState = trains[k].curState;

                                //若前车等待或暂停，该车需等待
                                if (trains[k].curState != RUN)
                                {
                                    trains[j].curState = WAIT;
                                    trains[j].waitForFrontTrain = 1;
                                }
                                //若前车已开始运行，则该车也可开始运行
                                if (trains[j].curState == RUN)
                                {
                                    trains[j].waitForFrontTrain = 0;
                                }
                            }

                            break;
                        }
                        case STOP:
                        {
                            if (!trains[j].started)
                            {
                                if ((--trains[j].startTime) == 0)
                                {
                                    trains[j].started = 1;
                                    trains[j].curState = RUN;
                                }

                                if (willIn(trains[j].startPos, curTrack, anotherTrack))
                                {
                                    trains[j].inPublicTrack = 1;
                                    publicTracks[curTrack][anotherTrack].state = BUSY;
                                    publicTracks[anotherTrack][curTrack].state = BUSY;
                                }
                            }
                            break;
                        }
                    }
                }

                //若队首火车已离开公共轨道，将其弹出该队列
                if (popped)
                    trainsQ[curTrack][anotherTrack].popFront();
            }
}

void control()
{
    getIntend();

    dispatch();

    stateTrans();
}
