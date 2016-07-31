#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <qmutex.h>
#include<QThread>
#include<QWaitCondition>

#include<process.h>
extern int Allocator(PCB submit,int ok);

extern QMutex mutex;
extern int isok;
extern QWaitCondition bufferEmpty;
extern QWaitCondition bufferFull;
extern const int buffersize;
class m_allocator :public QThread
{
	public:
    m_allocator(){}
    void alloc(PCB submit, int ok);                    //to get into memory
};

#endif // ALLOCATOR_H
