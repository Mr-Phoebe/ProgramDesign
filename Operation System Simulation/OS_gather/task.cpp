#include "taskmanager.h"
#include"memory.h"
#include <QDebug>
#include "m_allocator.h"
#include "m_tracker.h"
extern PCB cpuPCB;
extern PCB ioPCB;
extern strategy curStrategy;
extern int PIDcnt;
extern int fileOperation;
extern bool finished;
extern  m_allocator *m_allo;
void TaskManager::createPCB(int PID, int arrTime, int operation)
{
    PCB newPCB;

    if(operation == 0)
    {
        int randomTime = rand()%10 + 1;
        int randomCpuTime = rand()%10 + 1;
        while(randomTime < randomCpuTime)
        {
            randomCpuTime = rand()%10 + 1;
        }
        int randomIoTime = randomTime - randomCpuTime;
        int randomPriority = rand()%5 + 1;
        newPCB.initPCB(PID, arrTime, ready, randomTime, randomPriority, randomCpuTime, randomIoTime, 1, 0);

        //newPCB.initPCB(PID, arrTime, ready, 5, 3, 5, 0, 1, 0);
         m_allo->alloc(newPCB,1);
        //Allocator(newPCB,1);
    }
    else
    {
        //int PID, int arrivedTime, int state, int timeNeeded, int priority, int cpuTime, int ioTime, int pageNum, int operation
        switch (operation)
        {
        case 1:
        case 6:
        case 7:
            newPCB.initPCB(PID, arrTime, ready, 3, 1, 3, 0, 1, operation);
             m_allo->alloc(newPCB,1);
            //  Allocator(newPCB,1);
            break;
        case 8:
        case 9:
        case 10:
            newPCB.initPCB(PID, arrTime, ready, 2, 1, 2, 0, 1, operation);
             m_allo->alloc(newPCB,1);
            //  Allocator(newPCB,1);
            break;
        case 2:
        case 4:
            newPCB.initPCB(PID, arrTime, ready, 5, 1, 5, 0, 1, operation);
             m_allo->alloc(newPCB,1);
            //Allocator(newPCB,1);
            break;
        case 5:
            newPCB.initPCB(PID, arrTime, ready, 5, 1, 5, 0, 1, operation);
             m_allo->alloc(newPCB,1);
            //Allocator(newPCB,1);
            break;
        case 3:
            newPCB.initPCB(PID, arrTime, ready, 4, 1, 4, 0, 1, operation);
             m_allo->alloc(newPCB,1);
            //Allocator(newPCB,1);
            break;
        default:
            newPCB.initPCB(PID, arrTime, ready, 1, 1, 1, 0, 1, operation);
             m_allo->alloc(newPCB,1);
            //Allocator(newPCB,1);
            break;
        }
    }

    if(cpuPCB.getState() == -1)
    {
        cpuPCB = newPCB;
        cpuPCB.setState(running);
        //if(cpuPCB.getState()!=0)
          //  Allocator(cpuPCB,1);
    }
    else
    {
        this->readyList.push_back(newPCB);
    }

    PIDcnt++;
}

void TaskManager::selectStrategy(strategy s)
{
    switch(s)
    {
    case FCFS:
        this->readyList.sort(ArrTime());
        ExecuteStrategy();
        break;
    case SJF:
        this->readyList.sort(TimeNeeded());
        ExecuteStrategy();
        break;
    case PRIORITY:
        this->readyList.sort(Priority());
        ExecuteStrategy();
        break;
    case RR:
        if (cpuPCB.getCPUTime() != 0)
        {
            if(!this->readyList.empty())
            {
                cpuPCB.setState(ready);
                 m_allo->alloc(cpuPCB,1);
                this->readyList.push_back(cpuPCB);

                cpuPCB = this->readyList.front();
                cpuPCB.setState(running);
                qDebug()<<"I am running!\n";
                 m_allo->alloc(cpuPCB,1);
                //Allocator(cpuPCB,1);
                this->readyList.pop_front();
            }
        }
        else
        {
            ExecuteStrategy();
        }
        break;
    default:
        this->readyList.sort(ArrTime());
        break;
    }
}

void TaskManager::ExecuteStrategy()
{
    cpuPCB.setState(terminated);
    if(cpuPCB.getPID()!=0)
    {
        Allocator(cpuPCB,1);
    }

    if(cpuPCB.getIOTime() != 0)
    {
        cpuPCB.setState(waiting);
        this->waitingList.push_back(cpuPCB);
       // ioPCB.setState(1);
    }

    if(cpuPCB.getOperation() == 5)
    {
        fileOperation = 0;
        finished = false;
    }

    if (!this->readyList.empty())
    {
        qDebug() << "进来了";
        cpuPCB = this->readyList.front();
        cpuPCB.setState(running);
        qDebug()<<"I am running!\n";
         m_allo->alloc(cpuPCB,1);
        //Allocator(cpuPCB,1);
        this->readyList.pop_front();
    }
    else
    {
        cpuPCB.setState(-1);
    }
}

void TaskManager::IOStrategy()
{
    //this->waitingList.sort(ArrTime());

    if (!this->waitingList.empty())
    {
        ioPCB = this->waitingList.front();
        ioPCB.setState(waiting);
        this->waitingList.pop_front();
    }
    else
    {
        ioPCB.setState(-1);
    }
}

bool TaskManager::destroyPCB(int PID)
{
    for(list<PCB>::iterator it = readyList.begin(); it != readyList.end(); it++)
    {
        PCB temp = *it;
        if(PID == temp.getPID())
        {
            temp.setState(terminated);
            if(temp.getPID()!=0)
            {
                m_allo->alloc(temp,1);
            }

            readyList.erase(it);
            return true;
        }
    }

    for(list<PCB>::iterator it = waitingList.begin(); it != waitingList.end(); it++)
    {
        PCB temp = *it;
        if(PID == temp.getPID())
        {
            temp.setState(terminated);
            if(temp.getPID()!=0)
            {
                m_allo->alloc(temp,1);
            }

            waitingList.erase(it);
            return true;
        }
    }

    if(PID == cpuPCB.getPID() && cpuPCB.getState() != -1)
    {
        selectStrategy(curStrategy);
        return true;
    }
    else if(PID == ioPCB.getPID() && ioPCB.getState() != -1)
    {
        IOStrategy();
        return true;
    }

    return false;
}
