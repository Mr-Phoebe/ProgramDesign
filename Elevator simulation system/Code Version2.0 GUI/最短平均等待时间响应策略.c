/*
  注：工程里必须包含最快响应策略.c！！！因为本文件引用了其中的4个函数	
  problem:关于等待时间计算不是很正规，而且初步调试感觉程序不是很稳定，容易出现匪夷所思的错误，希望大家及时指出，
		  以便发现更多的问题，谢谢啦！————Map.Blair(5-18)
*/
#include "cmc.h"
#include <stdio.h>


void least_wait(Input input[],int size,int system_time,int output[],int condition)
/*
	函数功能:最短平均等待时间函数，通过分析电梯的状态和用户请求，将指令存入output[]，并改变condition
	参数说明:input[]是存储用户的输入指令，包含char order 和 int time两个参数，size是当前结构体数组input[]
			 的指令个数。system_time表示当前的系统时间，output[]储存电梯的指令(下标为时刻)，conditon表示
			 电梯当前的状态（0表示停止 1上升 -1下降 -2表示空闲无请求）
	指令对应关系:1-9代表电梯内乘客按目标按钮；Q、W、E、R、T、Y、I、O对应8层到1层的上行请求，
				A、S、D、F、G、H、J、K表示9层到2层的下行请求。
*/
{		

	extern void trans(Input input[],int size,C_INT inner_ask[10],C_INT2 outer_ask[10],int system_time,int current_floor);
	/*
		函数功能:将用户的指令转换成数字
		参数说明:inner_ask[10].value(=1表示已经按下 =0表示没有按下)
				 outer_ask[10].value(=0表示无请求 =1表示有上行请求 =-1表示有下行请求 =2表示有两种请求)
	*/
	extern int count_time(C_INT inner_ask[10],C_INT2 outer_ask[10],int floor,int condition);
	//返回优先condition方向（1->'u' or -1->'d'）所需的时间
	int waiting_time(C_INT inner_ask[10],C_INT2 outer_ask[10],int floor,int condition);
	//返回condition方向（1->'u' or -1->'d'）上的等待时间
	extern int max3(int a,int b,int c);//返回3个数的最大值
	extern int min3(int a,int b,int c);//返回3个数的最小值

	C_INT inner_ask[10]={0,0};//电梯外部指令,下标从1开始
	C_INT2 outer_ask[10]={0,0};//电梯内部指令,下标从1开始
	int current_floor;//当前时刻楼层
	int keep_time,change_time;//分别表示保持当前状态和改变状态下两者需要的等待时间
	

	current_floor=output[system_time];
	trans(input,size,inner_ask,outer_ask,system_time,current_floor);//转换用户的输入
	if (inner_ask[0].value==-2)//condition为空闲
	{
		output[system_time+1]=output[system_time]*100;
		return;
	}
//判断是否要停
	if (inner_ask[current_floor].value==1)//内部有请求
	{
		output[system_time+1]=current_floor;
		input[ inner_ask[current_floor].index ].is_done=1;

		inner_ask[current_floor].value=0;
		inner_ask[current_floor].index=0;

		return;
	}

	keep_time=count_time(inner_ask,outer_ask,current_floor,-condition)
			  +waiting_time(inner_ask,outer_ask,current_floor,condition);

	change_time=count_time(inner_ask,outer_ask,current_floor,condition)
		        +waiting_time(inner_ask,outer_ask,current_floor,-condition);
		
	if (outer_ask[current_floor].value!=0)//外部有请求
	{
		if (outer_ask[current_floor].value==condition)//外部恰有且仅有一个可以响应的请求	
		{
			outer_ask[current_floor].value=0;
			if (condition==1)
			{
				input[ outer_ask[current_floor].index_up ].is_done=1;
				outer_ask[current_floor].index_up=0;//清空指令
			}
			else
			{
				input[ outer_ask[current_floor].index_down ].is_done=1;
				outer_ask[current_floor].index_down=0;//清空指令
			}

			output[system_time+1]=current_floor;

			return;
		}
		else if (outer_ask[current_floor].value==2)//有两个请求
		{
			outer_ask[current_floor].value=(-condition);
	
			if (condition==1)
			{
				input[ outer_ask[current_floor].index_up ].is_done=1;
				outer_ask[current_floor].index_up=-1;//更改指令
			}
			else
			{				
				input[ outer_ask[current_floor].index_down ].is_done=1;
				outer_ask[current_floor].index_down=1;//指令
			}

			output[system_time+1]=current_floor;

			return;
		}
		else//有一个相反方向的请求
		{
			if (keep_time*6 < change_time*5) 
			//需要响应此请求并掉头
			{
				outer_ask[current_floor].value=0;
				if (condition==1)
				{
					input[ outer_ask[current_floor].index_down ].is_done=1;
					outer_ask[current_floor].index_down=0;//清空指令
				}
				else
				{
					input[ outer_ask[current_floor].index_up].is_done=1;
					outer_ask[current_floor].index_up=0;//清空指令
				}

				output[system_time+1]=current_floor;

				return;
			}	
		}
	}
//判断是否要停


//当前楼层没有需要停靠的请求
	if (keep_time*6 > change_time*5) 
		output[system_time+1]=current_floor+condition;//保持当前行进状态

	else
		output[system_time+1]=current_floor-condition;//掉头

	return;
}	

int waiting_time(C_INT inner_ask[10],C_INT2 outer_ask[10],int floor,int condition)
	//返回condition方向（1->'u' or -1->'d'）上的等待时间
{
	int i;
	int time=0;//该方向上的客户的等待时间
	
	if (condition==1)//上行
	{
		for (i=floor;i<=9;i++)
		{
			if (inner_ask[i].value==1)//被按下
				time+=(inner_ask[i].time+1);
			if (outer_ask[i].value==2)//两个请求
			{
				time+=(outer_ask[i].time_up+1);
				time+=(outer_ask[i].time_down+1);
			}
			if (outer_ask[i].value==1)//上行
				time+=(outer_ask[i].time_up+1);
			if (outer_ask[i].value==-1)//下行
				time+=(outer_ask[i].time_down+1);
		}
	}
	else//下行
	{
		for (i=floor;i>=1;i--)
		{
			if (inner_ask[i].value==1)//被按下
				time+=(inner_ask[i].time+1);
			if (outer_ask[i].value==2)//两个请求
			{
				time+=(outer_ask[i].time_up+1);
				time+=(outer_ask[i].time_down+1);
			}
			if (outer_ask[i].value==1)//上行
				time+=(outer_ask[i].time_up+1);
			if (outer_ask[i].value==-1)//下行
				time+=(outer_ask[i].time_down+1);
		}
	}

	return time;
}


