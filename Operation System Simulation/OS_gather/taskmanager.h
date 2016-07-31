#ifndef TASKMANAGER
#define TASKMANAGER

#include "process.h"
#include <list>
using namespace std;

enum strategy{FCFS, SJF, PRIORITY, RR};

class TaskManager
{
public:
    list<PCB> readyList;//就绪队列
    list<PCB> waitingList;//等待队列

    TaskManager()
    {

    }
    void selectStrategy(enum strategy s);//cpu调度策略选择
    void createPCB(int PID, int arrTime, int operation);//创建新的进程
    bool destroyPCB(int PID);//终止进程
    void ExecuteStrategy();//cpu调度
    void IOStrategy();//io调度
};

class ArrTime
{
public:
    bool operator()(const PCB p1, const PCB p2)const
    {
        return p1.getArrTime() < p2.getArrTime();
    }
};

class TimeNeeded
{
public:
    bool operator()(const PCB p1, const PCB p2)const
    {
        return p1.getTimeNeeded() < p2.getTimeNeeded();
    }
};

class Priority
{
public:
    bool operator()(const PCB p1, const PCB p2)const//数字越小，表示优先级越高
    {
        return p1.getPriority() < p2.getPriority();
    }
};

#endif // TASKMANAGER

