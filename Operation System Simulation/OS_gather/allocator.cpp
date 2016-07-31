#include "m_allocator.h"
#include<qdebug.h>
extern int isok;
void m_allocator::alloc(PCB submit,int ok){
    mutex.lock();
    if(isok==buffersize)
    {
        bufferEmpty.wait(&mutex);

    }
    qDebug()<<"thread1-----------------------------------------------------";
    qDebug()<<&isok;
    Allocator(submit,ok);
    isok++;
    if(isok==2)
        isok=0;
    bufferFull.wakeAll();
    mutex.unlock();

}
