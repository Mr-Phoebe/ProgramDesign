#ifndef PROCESS
#define PROCESS

using namespace std;

enum state{ready, running, waiting, terminated};

class PCB
{
private:
    int PID;//进程号
    int arrTime;//到达时间
    int state;//状态
    int timeNeeded;//生命周期
    int priority;//优先级
    int cpuTime;//cpu占用时间
    int ioTime;//io占用时间
    int pageNum;//需要内存页数
    int operation;//文件操作，0空操作，1创建，2打开，3修改，4保存，5关闭，6删除，7删除文件夹，8重命名，9权限修改，10cd, 11错误

public:
    PCB()
    {
        PID = 0;
        arrTime = 0;
        state = 0;
        timeNeeded = 0;
        priority = 0;
        cpuTime = 0;
        ioTime = 0;
        pageNum = 0;
        operation = -1;//
    }

    PCB(const PCB &p)
    {
        this->PID = p.PID;
        this->arrTime = p.arrTime;
        this->state = p.state;
        this->timeNeeded = p.timeNeeded;
        this->priority = p.priority;
        this->cpuTime = p.cpuTime;
        this->ioTime = p.ioTime;
        this->pageNum = p.pageNum;
        this->operation = p.operation;//
    }

    ~PCB(){}

    void initPCB(int PID, int arrivedTime, int state, int timeNeeded, int priority, int cpuTime, int ioTime, int pageNum, int operation)
    {
        this->PID = PID;
        this->arrTime = arrivedTime;
        this->state = state;
        this->timeNeeded = timeNeeded;
        this->priority = priority;
        this->cpuTime = cpuTime;
        this->ioTime = ioTime;
        this->pageNum = pageNum;
        this->operation = operation;
    }

    void setTimeNeeded(int t)
    {
        this->timeNeeded = t;
    }

    void setCPUTime(int t)
    {
        this->cpuTime = t;
    }

    void setIOTime(int t)
    {
        this->ioTime = t;
    }
    void setState(int s)
    {
        this->state = s;
    }

    int getPID()
    {
        return this->PID;
    }

    int getArrTime()const
    {
        return this->arrTime;
    }

    int getTimeNeeded()const
    {
        return this->timeNeeded;
    }

    int getPriority()const
    {
        return this->priority;
    }

    int getCPUTime()
    {
        return this->cpuTime;
    }

    int getIOTime()
    {
        return this->ioTime;
    }

    int getState()
    {
        return this->state;
    }

    int getPageNum()
    {
        return this->pageNum;
    }

    int getOperation()
    {
        return this->operation;
    }
};

#endif // PROCESS

