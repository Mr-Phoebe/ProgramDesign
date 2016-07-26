/*
	欢迎大家往里面扔自己的常量、定义的新数据类型以及一些小的功能函数（注意标识符不要重复），
	另外更新后的库已经不会被重复包括，请大家放心。
*/

#ifndef CMC_H

#define CMC_H
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
}C_INT;
//最快响应策略中用于储存转换后的用户指令的结构体数组

typedef struct
{
	int time_up;//对应上行指令已经等待的时间
	int time_down;//对应下行指令已经等待的时间
	int value;
	int index_up;//对应指令input数组中上行指令的下标
	int index_down;//对应指令input数组中下行指令的下标
}C_INT2;
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

extern const mouse key_position[];//下表从0开始，记录每个键的信息

extern int system_time;//记录当前仿真时间
extern Input input[500];//记录用户的输入请求指令,下标从一开始
extern int size;//input数组的当前元素个数
extern int delay;//每次行动等待时间


#define KEY_AMOUNT 32//键数
#define NAME1 "bitmap//外部上行2.bmp"
#define NAME2 "bitmap//外部下行2.bmp"
#define NAME3 "bitmap//外部上行.bmp"
#define NAME4 "bitmap//外部下行.bmp"

//声明部分
#endif

