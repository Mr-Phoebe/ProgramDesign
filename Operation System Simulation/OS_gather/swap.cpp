#include"memory.h"
#include"qdebug.h"
extern QString get_op;
extern int curclock;
extern int v_page_num;
extern MemorySystem ms;
int MemorySystem::get_victim(MemorySystem &ms)
{
    int i = 0;
    int oldest = 0;
    int pos=0;
    trace_page *temp=ms.get_tra_m();
    for (; i < PAGE_NUM; i++)
    {
        if (temp[i].swap == 1 && temp[i].age > oldest)
        {
            oldest = temp[i].age;
            pos = i;
        }
    }
    cout << pos<<"              ---------------------------"<<oldest<<endl;
    return pos;
}
int MemorySystem::get_into_page(PCB p, MemorySystem &ms)
{
    qDebug()<<ms.get_pages()<<"----------------------22222222";
    QString op;
    char  temp[8];
    QString op1;
    trace_page *t = ms.get_tra_m();
    if (ms.get_pages() >= p.getPageNum())
    {
        int j = 0;//为该进程或文件分配空间
        int end = PAGE_NUM;
        int k = 1;
        for (; j < end && k <= p.getPageNum(); j++)         //找到合适的页进行置换
        {
            if (t[j].valid == 1)
            {
                ms.set_tra_m(j,p,k,ms,"",0);

                op = "进程";
                _itoa(p.getPID(),temp,10);
                op+=temp;
                op+="放入内存";
                _itoa(j,temp,10);
                op += temp;
                ms.log(op,ms);
                op1 = "M";
                op1 += temp;
                op1 += ":";
                op1 += "□->■";
                op1 += '\n';
                get_op += op1;
                ms.set_page(ms.get_pages()-1);
                k++;
                //ms.set_start((ms.get_start()+1)%PAGE_NUM);
            }
        }
    }
    else
    {
        int pos;
        int logical = 0;
        int to_swap = p.getPageNum() - ms.get_pages();
        for (int j = 1; j <= to_swap; j++)
        {
            pos = ms.swap_out(ms.get_victim(ms), ms);
            if (pos != -1)
            {
                ms.set_tra_m(pos, p, j, ms,"",0);
                op = "进程";
                _itoa(p.getPID(),temp,10);
                op+=temp;
                op+="放入内存";
                _itoa(j, temp, 10);
                op += temp;
                ms.log(op, ms);
                op1 = "M";
                op1 += temp;
                op1 += "->VM";
                _itoa(pos,temp,10);
                op1 += temp;
                op1 += '\n';
                get_op = get_op + "M" + temp + ":□->■\n";
                logical++;
                return 1;
            }
            else
            {
                op="虚拟内存及内存空间不足,无法运行!";
                ms.log(op,ms);
                return 0;
            }
        }
        for (int  j = 0; j < ms.get_pages(); j++)
        {
            for (int i = 0; i<PAGE_NUM; i++)
            {
                if (t[i].valid == 1)
                {
                    ms.set_tra_m(i, p, logical, ms, "", 0);
                    op = "进程";
                    _itoa(p.getPID(),temp,10);
                    op+=temp;
                    op+="放入内存";
                    _itoa(i, temp, 10);
                    op += temp;
                    ms.log(op, ms);
                    op1 = "M";
                    op1 += temp;
                    op1 += ":□->■";
                    op1 += temp;
                    op1 += '\n';
                    get_op += op1;
                    ms.set_page(ms.get_pages() - 1);
                    logical++;
                    //ms.set_start((ms.get_start()+1)%PAGE_NUM);
                }
            }
        }

    }
}

void MemorySystem::set_tra_m(int pos, PCB p, int logical, MemorySystem &mss,string file_name,int type)
{
    if (logical!=0)
        ms.get_tra_m()[pos].valid = 0;
    else
    {
        ms.get_tra_m()[pos].valid = 1;
    }
    ms.get_tra_m()[pos].PID = p.getPID();
    if (type == 0)
    {
        ms.get_tra_m()[pos].type = 0;
        ms.get_tra_m()[pos].process_logicalad = logical;
        if (p.getState() == ready)
            ms.get_tra_m()[pos].swap = 1;
        else
        {
            ms.get_tra_m()[pos].swap = 0;
        }
        ms.get_tra_m()[pos].oper = p.getOperation();
    }
    else
    {
        ms.get_tra_m()[pos].file_logicalad = logical;

        ms.get_tra_m()[pos].file_path = file_name;
        ms.get_tra_m()[pos].swap = 1;
        ms.get_tra_m()[pos].type = 1;
    }
    ms.get_tra_m()[pos].age = 0;
    ms.update_age(ms);
}
void MemorySystem::update_age(MemorySystem &ms)       //依次更新age
{
    for (int i = 0; i < PAGE_NUM; i++)
    {
        if (ms.tra_m[i].valid == 0)
            ms.tra_m[i].age++;
    }
}
int MemorySystem::swap_out(int pos, MemorySystem &ms)
{
    QString op;
    qDebug()<<ms.get_v_pages()<<"          -----------------------11111111111111";
    char  temp[8];
    char temp2[8];
    int i = 0;
    int flag = 0;
    trace_page *t = ms.get_tra_m();
    if (ms.get_v_pages() != 0)
    {
        for (i = 0; i < v_page_num&&0==flag; i++)
            if (ms.get_tra_vm()[i].valid == 1)          //保存进程的记录项
            {
                flag = 1;
                ms.set_tra_vm(t[pos], i,ms);
                op = "页面";
                _itoa(pos, temp, 10);
                op += temp;
                op += "被换出到虚存";
                _itoa(i,temp2,10);
                op += temp2;
                get_op = get_op+"M"+temp+"->"+"VM"+temp2+'\n';
                ms.get_tra_m()[pos].age = 0;
                ms.log(op,ms);
                ms.set_v_num(ms.get_v_pages()-1);
            }
        return i-1;
    }
    else
    {
        return -1;
    }
}

void MemorySystem::set_tra_vm(trace_page t, int pos, MemorySystem &ms)
{

    if (t.PID == 0)
    {
        ms.get_tra_vm()[pos].valid = 1;
    }
    else
    {
        ms.get_tra_vm()[pos].valid = 0;

    }
    ms.get_tra_vm()[pos].PID = t.PID;
    ms.get_tra_vm()[pos].process_logicalad = t.process_logicalad;
    ms.get_tra_vm()[pos].file_logicalad = t.file_logicalad;
    ms.get_tra_vm()[pos].file_path = t.file_path;
    ms.get_tra_vm()[pos].type = t.type;
    ms.get_tra_vm()[pos].oper = t.oper;
}
int MemorySystem::check_in(PCB p,MemorySystem &ms)
{
    int in[10];
    int count = 0;
    int pos;
    int v_pos;              //该页在虚存中的位置
    for (int j = 1; j <= p.getPageNum(); j++)
        in[j] = 0;
    trace_page * t = ms.get_tra_m();
    for (int k = 0; k < PAGE_NUM; k++)
        if (t[k].PID == p.getPID())
        {
            in[t[k].process_logicalad] = 1;
            ms.update_swap(p.getPID(),ms);
            count++;
            if(ms.get_str()==1)
            {
                ms.update_age_lru(k,ms);
            }
        }
    if (count == p.getPageNum()){
        return 1;
    }
    else
    {
        for (int i = 1; i <= p.getPageNum(); i++)
        {
            if (in[i]!=1)
            {
                v_pos = ms.check_in_vm(p.getPID(),i,"",ms,0);
                if (v_pos != -1)
                {
                    ms.update_swap(p.getPID(), ms);
                    pos = ms.get_victim(ms);
                    ms.swap_out(pos, ms);
                    ms.swap_in(pos,v_pos,ms);
                }
                else
                {
                    return -1;

                }
            }
        }///////////////////////huan
    }
    return 1;
}
int MemorySystem::check_in_vm(int pid, int logical, string file_path, MemorySystem &ms,int type)
{
    trace_vm * t = ms.get_tra_vm();
    if (type==0)
    {
        for (int i = 0; i < v_page_num; i++)
            if (t[i].PID == pid && t[i].process_logicalad == logical)
                return i;
        return -1;
    }
    else
    {
        for (int i = 0; i < v_page_num; i++)
            if (t[i].file_path == file_path && t[i].file_logicalad == logical)
                return i;
        return -1;
    }
}
int MemorySystem::swap_in(int pos, int v_pos,MemorySystem &ms)
{
    QString op;
    char temp[10];
    char temp2[10];
    trace_vm* t = ms.get_tra_vm();
    PCB p;
    p.initPCB(t[v_pos].PID,0,running,0,0,0,0,0,t[v_pos].oper);
    if (t[v_pos].type == 0)
    {
        ms.set_tra_m(pos,p,t[v_pos].process_logicalad,ms,"",0);
        op = "进程";
        _itoa(p.getPID(),temp,10);
        op+=temp;
        op+="放入内存";
        _itoa(pos,temp,10);
        op += temp;
        _itoa(v_pos,temp2,10);
        get_op = get_op + "VM" + temp2 + "->" + "M" + temp + '\n';
        ms.log(op, ms);
    }
    else
    {
        ms.set_tra_m(pos,p,t[v_pos].file_logicalad,ms,t[v_pos].file_path,1);
        op = "进程";
        _itoa(p.getPID(),temp,10);
        op+=temp;
        op+="放入内存";
        _itoa(pos, temp, 10);
        op += temp;
        _itoa(v_pos, temp2, 10);
        get_op = get_op + "VM" + temp2 + "->" + "M" + temp + '\n';
        ms.log(op, ms);
    }
    trace_page a;
    a.age = 0;
    a.file_logicalad = 0;
    a.file_path = "";
    a.oper = 0;
    a.PID = 0;
    a.process_logicalad = 0;
    a.swap = 0;
    a.type = 0;
    a.valid = 1;
    ms.set_tra_vm(a,v_pos,ms);
    ms.set_v_num(ms.get_v_pages()+1);
    return 1;
}
int MemorySystem::remove(int pid,MemorySystem &ms)
{
    PCB p;
    trace_page a;
    a.age = 0;
    a.file_logicalad = 0;
    a.file_path = "";
    a.oper = 0;
    a.PID = 0;
    a.process_logicalad = 0;
    a.swap = 0;
    a.type = 0;
    a.valid = 1;
    p.initPCB(0, 0, running, 0, 0, 0, 0, 0, 0);
    trace_page * t = ms.get_tra_m();
    trace_vm * vt = ms.get_tra_vm();
    int count1 = 0;
    int count2 = 0;
    QString op="";
    char temp[10];
    for (int i = 0; i < PAGE_NUM; i++)
    {
        if (t[i].PID == pid && t[i].type==0)
        {
            count1++;
            ms.set_tra_m(i, p, 0, ms, "", 0);
            op="放有进程";
            _itoa(pid,temp,10);
            op+=temp;
            op+= "的内存页面";
            _itoa(i, temp, 10);
            op += temp;
            op += "被释放";
            get_op = get_op + "M" + temp + ":■" + "->" + "□"+'\n';
            ms.log(op, ms);
        }

    }
    for(int i=0;i<v_page_num;i++)
    {
        if (vt[i].PID == pid && vt[i].type==0)
        {
            count2++;
            ms.set_tra_vm(a, i, ms);
            op="放有进程";
            _itoa(pid,temp,10);
            op+=temp;
            op += "的虚拟内存页面";
            _itoa(i, temp, 10);
            op += temp;
            op += "被释放";
            get_op = get_op + "VM" + temp + ":■" + "->" + "□"+'\n';
            ms.log(op, ms);
        }
    }
    int i=ms.get_pages();
    i+=count1;
    ms.set_page(i);
    i=ms.get_v_pages();
    i+=count2;
    qDebug()<<"now has oooooooooo"<<ms.get_pages();
    ms.set_v_num(i);
    return 1;
}
int MemorySystem::file_check(string file_path,MemorySystem &ms,int logical)
{
    trace_page *t = ms.get_tra_m();
    for (int i = 0; i < PAGE_NUM; i++)
    {
        if (t[i].file_path == file_path && t[i].file_logicalad == logical&& t[i].valid==0)
            return i;
    }
    return -1;
}

int MemorySystem::file_into_page(MemorySystem &ms,string file_path,int blocks,string content,int pid)
{
    PCB p;
    p.initPCB(pid, 0, running, 0, 0, 0, 0, 0, 0);
    QString op;
    char  temp[8];
    if (ms.get_pages()>0)
    {
        int j = 0;//为该进程或文件分配空间
        int end = PAGE_NUM;
        int ok = 0;
        for (; j < end&&ok==0; j++)         //找到合适的页进行置换
        {
            qDebug()<<" file in page ?";
            if (ms.tra_m[j].valid == 1)
            {
                ms.set_tra_m(j, p, blocks, ms, file_path, 1);
                ms.set_page(ms.get_pages() - 1);
                ms.set_string(content,j,ms);
                op="来自路径";
                op+=file_path.c_str();

                op+= "的文件放入内存";
                _itoa(j,temp,10);
                op += temp;
                get_op = get_op + "M" + temp + ":□" + "->" + "■" + "\n";
                ms.log(op, ms);
                //ms.set_start((ms.get_start()+1)%PAGE_NUM);
                ok = 1;
            }
        }
        return j-1;
    }
    else                                   //找到牺牲页，将牺牲页中的内容换入虚拟内存，然后将该页放入新的文件内容
    {
        int j = ms.get_victim(ms);
        if(ms.swap_out(j, ms)!=-1)
        {
            ms.set_tra_m(j,p,blocks,ms,file_path,1);
            op="来自路径";
            op+=file_path.c_str();

            op+= "的文件放入内存";
            _itoa(j, temp, 10);
            op += temp;
            get_op = get_op + "M" + temp + ":□" + "->" + "■" + "\n";
            ms.log(op, ms);
            ms.set_page(ms.get_pages() - 1);
            ms.set_string(content, j, ms);
            return j;
        }
        else
        {
            return -1;
        }
    }
    return -1;
}
void MemorySystem::set_string(string content,int pos, MemorySystem &ms)
{
    ms.page[pos] = content;
}
void MemorySystem::delete_string(int pos, MemorySystem &ms)
{
    ms.page[pos] = "";
}
void MemorySystem::update_age_lru(int pos, MemorySystem &ms)
{
    ms.get_tra_m()[pos].age = 0;
    ms.update_age(ms);
}
void MemorySystem::update_filepage(string con,MemorySystem &ms,int pos)          //0 修改 1 清空
{
    PCB p;
    p.initPCB(0, 0, running, 0, 0, 0, 0, 0, 0);
    ms.set_string(con, pos, ms);
    QString op="";
    char temp[10];
    _itoa(pos,temp,10);
    if (con.size() == 0)
    {
        ms.set_page(ms.get_pages() + 1);
        ms.set_tra_m(pos, p, 0, ms, "", 0);
        op =op+ "页面"+temp+"中的文件被删除\n";
    }
    else
        op = op + "页面" + temp + "中的文件被修改\n";
    ms.log(op, ms);
}
//int pos;
//int logical = 0;
//int to_swap = blocks - ms.get_pages();
//for (int j = 1; j <= to_swap; j++)
//{
    //pos = ms.swap_out(ms.get_victim(ms), ms);
    //if (pos != -1)
    //{
        //ms.set_tra_m(pos, p, j, ms, file_path, 1);
        //ms.set_string(content, pos, ms);
        //logical++;
//	}
//}
//for (int i = 0; i < ms.get_pages(); i++)
//{
    //if (ms.tra_m[i].valid == 1)
    //{
        //ms.set_tra_m(pos, p, logical, ms, file_path, 1);
        //ms.set_page(ms.get_pages() - 1);
        //ms.set_string(content, i, ms);
        //logical++;
        //ms.set_start((ms.get_start()+1)%PAGE_NUM);
//	}
//}
int MemorySystem::find_file(int logical, MemorySystem ms,string file_path)
{
    trace_page * t = ms.get_tra_m();
    for (int i = 0; i < PAGE_NUM; i++)
    {
        if (t[i].file_path == file_path && t[i].file_logicalad == logical)
            return i;
    }
    return -1;
}
void MemorySystem::log(QString oper,MemorySystem ms)
{
    ofstream fout;
    fout.open("Memory_log.txt", ios_base::out | ios_base::app);
    if (fout.is_open())
    {
        fout <<  ms.get_time()<< endl;
        fout << oper.toStdString() << endl;
    }
    fout.close();
}
string MemorySystem::get_time()
{
    tm *hour;
    tm *minute;
    tm *second;
    time_t t;
    t = time(0);
    char h[10];
    char m[10];
    char s[10];
    string temp="";

    hour = localtime(&t);
    minute = localtime(&t);
    second = localtime(&t);
    temp += _itoa(hour->tm_hour, h, 10);
    temp += ":";
    temp += _itoa(minute->tm_min, m, 10);
    temp += ":";
    temp += _itoa(second->tm_sec, s, 10);
    return temp;
}
void MemorySystem::remove_file(string file_path,MemorySystem &mss)
{
    PCB p;
    trace_page a;
    a.age = 0;
    a.file_logicalad = 0;
    a.file_path = "";
    a.oper = 0;
    a.PID = 0;
    a.process_logicalad = 0;
    a.swap = 0;
    a.type = 0;
    a.valid = 1;
    p.initPCB(0, 0, running, 0, 0, 0, 0, 0, 0);
    trace_page * t = ms.get_tra_m();
    trace_vm * vt = ms.get_tra_vm();
    int count1 = 0;
    int count2 = 0;
    QString op="";
    char temp[10];
    for (int i = 0; i < PAGE_NUM; i++)
    {
        if (t[i].file_path == file_path && t[i].type==1)
        {
            count1++;
            ms.set_tra_m(i, p, 0, ms, "", 0);
            op = "内存存放文件";
            op+=file_path.c_str();
            op+="的页面";
            _itoa(i, temp, 10);
            op += temp;
            op += "被释放";
            get_op = get_op + "M" + temp + ":■" + "->" + "□"+'\n';
            ms.log(op, ms);
        }

    }
    for(int i=0;i<v_page_num;i++)
    {
        if (vt[i].file_path == file_path && t[i].type==1)
        {
            count2++;
            ms.set_tra_vm(a, i, ms);
            op = "虚拟内存存放文件";
            op+=file_path.c_str();
            op+="页面";
            _itoa(i, temp, 10);
            op += temp;
            op += "被释放";
            get_op = get_op + "VM" + temp + ":■" + "->" + "□"+'\n';
            ms.log(op, ms);
        }
    }
    for(int i=0;i<16;i++)
        ms.set_string("",i,ms);
    ms.set_page(ms.get_pages()+count1);
    ms.set_v_num(ms.get_v_pages() + count2);

}
