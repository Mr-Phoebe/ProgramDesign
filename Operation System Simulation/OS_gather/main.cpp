#include "mainwindow.h"
#include <QApplication>
#include "fileSystem.h"
#include "notepad.h"
#include "memory.h"
#include"m_allocator.h"
#include"m_tracker.h"
FileSystem *fs;
Notepad *np;
m_allocator *m_allo;
m_tracker *m_trac;
MemorySystem ms(0);
extern HANDLE allo, trac;
extern MemorySystem ms;
extern PCB submit[24];
extern string m_buffer;
extern string get_op;
QMutex mutex;
int v_page_num;
int isok=0;
QWaitCondition bufferEmpty;
QWaitCondition bufferFull;
const int buffersize=1;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    init();
    fs = new FileSystem;
    //np = new Notepad;

    m_allo=new m_allocator();
    m_trac=new m_tracker() ;
    m_trac->start();
    m_allo->start();
    /*=======内存部分============*/
    /*
    DWORD dwThread;
    HANDLE handle[2];
    //生成两个线程
    handle[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Tracker, NULL, 0, &dwThread);
    handle[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Allocator, NULL, 0, &dwThread);

    //生成两个信号量
    LPCWSTR pName1=(LPCWSTR)"allo", pName2 = (LPCWSTR)"trac";
    allo = CreateSemaphore(NULL, 0, 1, pName1);
    trac = CreateSemaphore(NULL, 1, 1, pName2);

*/

    fs->save();
    fs->log("boot-strap", "");

    MainWindow w;
    //w.setWindowTitle("银行");
    w.show();


    //等待线程执行的执行结束后，再退出
   // WaitForMultipleObjects(2, handle, TRUE, INFINITE);
    //===========

    return  a.exec();

}
