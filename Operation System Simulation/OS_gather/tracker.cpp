#include "m_tracker.h"
#include"qdebug.h"
extern int isok;
m_tracker::m_tracker(){}

void m_tracker::run()
{
    forever
    {
        mutex.lock();
        if(isok==0)
            bufferFull.wait(&mutex);
        isok--;
        qDebug()<<"thread 2-------------------------------------";
         qDebug()<<&isok;
        Tracker(0);
        bufferEmpty.wakeAll();
        mutex.unlock();
    }
}
