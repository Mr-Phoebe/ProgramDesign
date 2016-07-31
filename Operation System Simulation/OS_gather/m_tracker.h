#ifndef TRACKER_H
#define TRACKER_H

#include <qmutex.h>
#include<QThread>
#include<QWaitCondition>
#include<process.h>
#include<windows.h>
extern QMutex mutex;
extern int isok;
extern QWaitCondition bufferEmpty;
extern QWaitCondition bufferFull;
extern const int buffersize;
extern DWORD Tracker(LPDWORD lpdwparm);
class m_tracker : public QThread
{
public:
    m_tracker();
    void run();
};

#endif // TRACKER_H
