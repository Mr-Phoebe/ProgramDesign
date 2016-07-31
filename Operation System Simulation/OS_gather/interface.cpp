#include"memory.h"
extern MemorySystem ms;
extern int v_page_num;
FCB * MemorySystem::getFileFCB(string path)
{
    FCB *p = new FCB();
    int blocks = rand() % 3 + 1;
    for (int i = 0; i < blocks; i++)
    {
        p->blockId.push_back(rand() % 64);
    }
    return p;
}
string MemorySystem::getBlockContent(int blockId)
{

    string a = "";
    for (int i = 0; i < 1024; i++)
    {
        a += '0';
    }
    return a;
}
string MemorySystem::get_content_mod()
{
    string str = "";
    int len = 0, block = 0;
    block = rand() % 2;
    len = block * 1024 + rand()%1023;
    for (int i = 0; i < len; i++)
    {
        str += (char)(rand() % 25) + 'a';
    }
    return str;
}
int MemorySystem::updateFile(string path, vector<string> newblock)
{
    return 1;
}
QString MemorySystem::op_show_m()
{
    QString blocks = "";
    //printf("空闲块：□\n已占用块：■\n");
    blocks += "空闲块：□\n已占用块：■\n";
    for (int i = 0; i <PAGE_NUM; i++)
    {

        if (ms.get_tra_m()[i].valid==1)
        {
            //printf("□");
            blocks += "□";
        }
        else
        {
            //printf("■");
            blocks += "■";
        }
        if (i % 6 == 5)
            blocks += '\n';
    }
    return blocks;
}
QString MemorySystem::op_show_vm()
{
    QString blocks = "";
    //printf("空闲块：□\n已占用块：■\n");
    blocks += "空闲块：□\n已占用块：■\n";
    for (int i = 0; i <v_page_num; i++)
    {

        if (ms.get_tra_vm()[i].valid == 1)
        {
            //printf("□");
            blocks += "□";
        }
        else
        {
            //printf("■");
            blocks += "■";
        }
        if (i % 6 == 5)
            blocks += '\n';
    }
    return blocks;
}

