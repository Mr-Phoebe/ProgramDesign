#include <fstream>
#include <windows.h>
#include <iostream>
#include <cstring>
#include <string>
#include<ctime>
#include"fileSystem.h"
#include"process.h"
#include "notepad.h"
#define PAGE_NUM 16
#define V_PAGE_NUM_MAX 64
using namespace std;
extern int v_page_num;
typedef struct trace_vm
{
    int PID;                 //进程的标识
    int process_logicalad;   //进程的逻辑块号
    int type;                //0 process 1 file
    int swap;                //可否置换 0 no 1 ok
    int valid;               //该页的有效位 0 no 1 ok
    string  file_path;       //指定路径下的文件地址
    int file_logicalad;      //文件的逻辑块号
    int oper;
}trace_vm;
typedef struct trace_page     //内存的追踪单元
{
    int PID;                 //进程的标识
    int process_logicalad;   //进程的逻辑块号
    int type;                //0 process 1 file
    int swap;                //可否置换 0 no 1 ok
    int valid;               //该页的有效位 0 no 1 ok
    string  file_path;       //指定路径下的文件地址
    int file_logicalad;      //文件的逻辑块号
    int age;               	//页面置换的时候 采用FIFO策略的时候使用
    int oper;
}trace_page;



class MemorySystem
{
	private:
		string page[PAGE_NUM];              //内存的分页
		trace_page tra_m[PAGE_NUM];         //内存的追踪单元
		trace_vm tra_v[V_PAGE_NUM_MAX];           //虚拟内存的追踪单元
		int start;                          //寻找的开始
		int page_num;                       //剩余页数
		int v_num;                          //可用虚存的页数
		int strategy;                        //页面置换策略 0 FIFO 1 LRU
	public:
        MemorySystem(int a)
        {
            ifstream fin;
            fin.open("memory_config.txt");
            if(fin.is_open())
            {
                fin>>v_page_num;
                fin>>strategy;

            }
            start = 0;
            page_num = PAGE_NUM;
            v_num = v_page_num;
            strategy = a;
            for (int i = 0; i < PAGE_NUM; i++)
            {
                tra_m[i].valid = 1;
                tra_v[i].valid = 1;

            }

        }
        ~MemorySystem(){};
        int get_start()           //得到当前置换页应该开始的起点
        {
            return start;
        }
        int get_pages()           //得到当前可以使用的页数
        {
            return page_num;
        }
        int get_v_pages()         //得到当前虚存的剩余页数
        {
            return v_num;
        }
        int get_str(){
            return strategy;
        }
        int get_victim(MemorySystem &ms);
        trace_page * get_tra_m(){
            return tra_m;
        }

        trace_vm * get_tra_vm(){
            return tra_v;
        }
        void set_start(int i){
            start = i;
        }
        void set_page(int i){
            page_num = i;
        }
        void set_v_num(int i){
            v_num = i;
        }
        string* get_string()
        {
            return page;
        }

        void update_filepage(string con, MemorySystem &ms,int pos);        //更新某一页的文件内容
        void set_string(string content,int pos,MemorySystem &ms);                  //将文件内容放入内存
        void delete_string(int pos, MemorySystem &ms);               //清除内存中文件的内容
        //int get_file_path();
        int file_into_page(MemorySystem &ms, string file_path, int blocks, string content,int pid); //将文件载入内存中
        void update_age_lru(int pos,MemorySystem &ms);             //在lru策略下更新页面的访问时间
        FCB * getFileFCB(string path);                            //得到相应的fcb
        string getBlockContent(int blockId);                     //得到文件内的内容
        int file_check(string file_path, MemorySystem &ms, int logical);                //检查文件是否在内存
        int remove(int pid,MemorySystem &ms);                        //将某个进程相关的PCB以及file删除
        int swap_out(int pos, MemorySystem &ms);                 //将某页换入交换区
        void update_age(MemorySystem &ms);                       //更新页面的age，便于使用FIFO置换
        int get_into_page(PCB p, MemorySystem &ms);             //将进程放入内存
        void set_tra_m(int pos, PCB p, int logical, MemorySystem &ms, string file_name,int type);       //更新追踪单元
        void set_tra_vm(trace_page t, int pos, MemorySystem &ms);                //更新虚拟内存
        int check_in(PCB p, MemorySystem &ms);                                //检查是否在内存中
        int check_in_vm(int pid,int logical,string file_path,MemorySystem &ms,int type);         //检查是否在交换区中
        int swap_in(int pos,int v_pos,MemorySystem &ms);                 //将某页换入内存
        string get_content_mod();
        int updateFile(string path, vector<string> newblock);
        int find_file(int logical,MemorySystem ms,string file_path);                    //得到文件的相应页在内存中的位置
        void log(QString oper,MemorySystem ms);                //记录所有的操作日志
        string get_time();            //得到当前时间
        void remove_file(string file_path, MemorySystem &mss);       //删除内存中的文件
        void update_swap(int pid, MemorySystem &ms)
        {
            for (int  i = 0; i < PAGE_NUM; i++)
            {
                if (ms.get_tra_m()[i].PID==pid)
                    ms.get_tra_m()[i].swap = 0;
                else
                    ms.get_tra_m()[i].swap = 1;
            }

        }          //更新可否置换位
        QString op_show_m();
        QString op_show_vm();


   

};

#ifndef GLOBAL
#define GLOBAL

#endif

DWORD Tracker(LPDWORD lpdwparm);
int Allocator(PCB submit,int ok);

#ifndef GLOBAL
#define GLOBAL

#endif
