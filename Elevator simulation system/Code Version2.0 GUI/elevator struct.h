#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "egg.h"


#ifndef elevator

#define elevator
//声明部分
typedef struct
{
	int time;//对应用户请求的仿真时间
	char order;//对应用户的请求指令
	int is_done;//1表示已经被完成，0表示没有被完成
}Input;
//main函数中储存用户指令的结构体

typedef struct
{
	int floor;//前一状态的楼层
	int statue;//这一个时间段需要执行的状态（=0开关门 =1上升 =-1下降 =-2空闲）
}Output;
//main函数中记录电梯输出的结构体数组

typedef struct
{
	int time;//记录该请求已经等待的时间
	int value;
	int index;//对应指令input数组中内部指令的下标
}C_fast1;
//最快响应策略中用于储存转换后的用户指令的结构体数组

typedef struct
{
	int time_up;//对应上行指令已经等待的时间
	int time_down;//对应下行指令已经等待的时间
	int value;
	int index_up;//对应指令input数组中上行指令的下标
	int index_down;//对应指令input数组中下行指令的下标
}C_fast2;
//最快响应策略中用于储存转换后的用户指令的结构体数组

typedef struct
{
	char order;//对应的第一版本中的字符
	int leftup_x;//左上角坐标的x值
	int leftup_y;//左上角坐标的y值
	int rightdown_x;//右下角坐标的x值
	int rightdown_y;//右下角坐标的y值
	char bitmap_name1[25];//储存对应的图片1的名字（初始）
	char bitmap_name2[25];//储存对应的图片2的名字（有请求）
}mouse;
extern const mouse click_position[];//下表从0开始，记录每个键的信息


#define max(a,b) (a)>=(b)?(a):(b)
#define min(a,b) (a)<=(b)?(a):(b)

/*--------------------------------------------------策略函数的声明------------------------------------------------------------*/
extern int orderServe(int out[],Input in[],int time,int in_size,int*);//先到先服务
extern void fastest_respond(Input input[],int size,int system_time,int output[],int dir);//最快响应
extern int assistServe(int out[],int time,int *direction,Input in[],int in_size);//顺便服务
extern void least_wait(Input input[],int size,int system_time,int output[],int dir);//最短平均等待时间
/*--------------------------------------------------策略函数的声明------------------------------------------------------------*/

/*--------------------------------------------------全局变量的声明------------------------------------------------------------*/
extern int system_time;//记录当前仿真时间
extern Input input[500];//记录用户的输入请求指令,下标从一开始
extern int size;//input数组的当前元素个数
extern int delay;//每次行动等待时间
extern int strategy;//当前采取的策略号
extern int is_go;//=1表示GO键被按下
extern int output[1001];//储存每个仿真时刻的电梯状态的数组，下标表示时间（如output[0]=1表示电梯在第0秒处于第一层）
extern int dir;//表示电梯当前的状态（/*0停止*/ 1上升 -1下降 -2空闲）
extern int ratio;//等待时间与上升时间的比例
extern int bitmap;//=0表示不在贴图 =1表示在贴图
extern int animation;//=0表示不在动画 =1表示在动画
extern int ratio;//等待时间与上升时间的比例
extern int initial;//=1 表示初始化完成 =0表示未完成初始化
extern int ng;

#define KEY_AMOUNT 31//键数
#define step 20//切片数
#define NAME1 "bitmap//外部上行2.bmp"
#define NAME2 "bitmap//外部下行2.bmp"
#define NAME3 "bitmap//外部上行.bmp"
#define NAME4 "bitmap//外部下行.bmp"
/*--------------------------------------------------全局变量的声明------------------------------------------------------------*/
//声明部分
#endif



