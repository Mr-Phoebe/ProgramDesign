/*
  problem:如果要区分外部的请求（上下行），那它们有什么不同的影响呢？貌似对本策略没有影响……
		  另外欢迎各位指出调试过程中的各种Bug~敝人不胜感激~ ——Map.Blair(4-27)
*/
#include "cmc.h"
#include <stdio.h>

void fastest_respond(Input input[],int size,int system_time,int output[],int condition)
/*
	函数功能:最快相应策略函数，通过分析电梯的状态和用户请求，将指令存入output[]，并改变condition
	参数说明:input[]是存储用户的输入指令，包含char order 和 int time两个参数，size是当前结构体数组input[]
			 的指令个数。system_time表示当前的系统时间，output[]储存电梯的指令(下标为时刻)，conditon表示
			 电梯当前的状态（0表示停止 1上升 -1下降 -2表示空闲无请求）
	指令对应关系:1-9代表电梯内乘客按目标按钮；Q、W、E、R、T、Y、I、O对应8层到1层的上行请求，
				A、S、D、F、G、H、J、K表示9层到2层的下行请求。
*/
{		

	void trans(Input input[],int size,C_INT inner_ask[10],C_INT2 outer_ask[10],int system_time,int current_floor);
	/*
		函数功能:将用户的指令转换成数字
		参数说明:inner_ask[10].value(=1表示已经按下 =0表示没有按下)
				 outer_ask[10].value(=0表示无请求 =1表示有上行请求 =-1表示有下行请求 =2表示有两种请求)
	*/
	int count_time(C_INT inner_ask[10],C_INT2 outer_ask[10],int floor,int condition);
	//返回优先condition方向（1->'u' or -1->'d'）所需的时间

	int max3(int a,int b,int c);//返回3个数的最大值
	int min3(int a,int b,int c);//返回3个数的最小值

	C_INT inner_ask[10]={0,0};//电梯外部指令,下标从1开始
	C_INT2 outer_ask[10]={0,0};//电梯内部指令,下标从1开始
	int current_floor;
	

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
			if (count_time(inner_ask,outer_ask,current_floor+condition,condition)*5 > count_time(inner_ask,outer_ask,current_floor+condition,-condition)*6) 
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
	if (count_time(inner_ask,outer_ask,current_floor,condition)*5 < count_time(inner_ask,outer_ask,current_floor,-condition)*6) 
		output[system_time+1]=current_floor+condition;//保持当前行进状态

	else
		output[system_time+1]=current_floor-condition;//掉头

	return;
}

 void trans(Input input[],int size,C_INT inner_ask[10],C_INT2 outer_ask[10],int system_time,int current_floor)
/*
	函数功能:将用户的指令转换成数字
	参数说明:inner_ask[10].value(=1表示已经按下 =0表示没有按下)
			 outer_ask[10].value(=0表示无请求 =1表示有上行请求 =-1表示有下行请求 =2表示有两种请求)
*/
{
	int i;
	int floor=0;
	int flag=0;

	for (i=1;i<=size;i++)
	{
		if (input[i].is_done==0)//没有被响应的请求
		{
			flag=1;
			if (input[i].order<='9' && input[i].order>=1 && !(input[i].time==system_time-1 && input[i].order==current_floor+48) )//内部请求
			{
				inner_ask[input[i].order-48].time=system_time-input[i].time;
				inner_ask[input[i].order-48].value=1;
				inner_ask[input[i].order-48].index=i;
			}

			else//外部请求
			{
				switch (input[i].order)
				{
				case 'Q':case 'q'://八层上行
					floor=8;
					break;
				case 'W':case 'w'://七层上行
					floor=7;
					break;
				case 'E':case 'e'://六层上行
					floor=6;
					break;
				case 'R':case 'r'://五层上行
					floor=5;
					break;
				case 'T':case 't'://四层上行
					floor=4;
					break;
				case 'Y':case 'y'://三层上行
					floor=3;
					break;
				case 'U':case 'u'://二层上行
					floor=2;
					break;
				case 'I':case 'i'://一层上行
					floor=1;
					break;
				case 'A':case 'a'://九层下行
					floor=-9;
					break;
				case 'S':case 's'://八层下行
					floor=-8;
					break;
				case 'D':case 'd'://七层下行
					floor=-7;
					break;
				case 'F':case 'f'://六层下行
					floor=-6;
					break;
				case 'G':case 'g'://五层下行
					floor=-5;
					break;
				case 'H':case 'h'://四层下行
					floor=-4;
					break;
				case 'J':case 'j'://三层下行
					floor=-3;
					break;
				case 'K':case 'k'://二层下行
					floor=-2;
					break;
				default:
					break;
				}
				if (floor<0 && !(current_floor==(-floor) && input[i].time==system_time-1))
				{
					if (outer_ask[-floor].value==1)//已经有上行请求
						outer_ask[-floor].value=2;			
					else
						outer_ask[-floor].value=-1;

					outer_ask[-floor].time_down=system_time-input[i].time;
					outer_ask[-floor].index_down=i;
				}
				else if (floor>0 && !(current_floor==floor && input[i].time==system_time-1))
				{
					if (outer_ask[floor].value==-1)//已经有下行请求
						outer_ask[floor].value=2;
					else
						outer_ask[floor].value=1;

					outer_ask[-floor].time_up=system_time-input[i].time;
					outer_ask[floor].index_up=i;
				}
			}
		}
	}//请求转换完毕
	if (flag==0)
		inner_ask[0].value=-2;

	return;
}	

int count_time(C_INT inner_ask[10],C_INT2 outer_ask[10],int floor,int condition)
	//返回优先condition方向（1->'u' or -1->'d'）所需的时间
{
	int max_in=0,min_in=10;//储存当前请求楼层内部和外部的最大最小楼层
	int i,time=0;
	int high_up=0,high_down=0,low_up=10,low_down=10;
	
	for (i=1;i<=9;i++)
	{
		if (inner_ask[i].value==1 && min_in > i)
			min_in=i;
		if (inner_ask[i].value==1 && max_in < i)
			max_in=i;
	}//寻找内部最值

	for (i=1;i<=floor-1;i++)
	{
		if ((outer_ask[i].value==1 || outer_ask[i].value==2) && (low_up < i || low_up==10))//最大上行（当前楼层下面）
			low_up=i;
		if ((outer_ask[i].value==-1 || outer_ask[i].value==2) && (low_down < i || low_down==10))//最大下行（当前楼层下面）
			low_down=i;
	}	
	for (i=floor+1;i<=9;i++)
	{
		if ((outer_ask[i].value==1 || outer_ask[i].value==2) && high_up < i)//最大上行（当前楼层上面）
			high_up=i;
		if ((outer_ask[i].value==-1 || outer_ask[i].value==2) && high_down < i)//最大下行（当前楼层上面）
			high_down=i;
	}

	if (condition==1)
	{
		if (max3(max_in,high_up,high_down) > floor)//需要上行
		{
			time+=max3(max_in,high_up,high_down)-floor;

			if (min3(min_in,low_up,low_down) >= floor)//不需要再下行
				return high_down==0?time:time+max3(max_in,high_up,high_down)-high_down;
			else
			{
				time*=2;//下行到原位置
				time+=floor-min3(min_in,low_up,low_down);

				return low_up==10?time:time+low_up-min3(min_in,low_up,low_down);
			}
		}
		else
			return 360;//针对此策略必然先上行不行，因此返回最大值
	}	
	else 
	{
		if (min3(min_in,low_up,low_down) < floor)//需要下行
		{
			time+=floor-min3(min_in,low_up,low_down);

			if (max3(max_in,high_up,high_down) <= floor)//不需要上行
				return low_up==10?time:time+low_up-min3(min_in,low_up,low_down);
			else
			{
				time*=2;//上行到原位置
				time+=max3(max_in,high_up,high_down)-floor;

				return high_down==0?time:time+max3(max_in,high_up,high_down)-high_down;
			}
		}	
		else
			return 360;
	}
	
}

int max3(int a,int b,int c)//返回3个数的最大值
{
	int max;

	max=a;
	if (max<b)
		max=b;
	if (max<c)
		max=c;

	return max;
}

int min3(int a,int b,int c)//返回3个数的最小值
{
	int min;

	min=a;
	if (min>b)
		min=b;
	if (min>c)
		min=c;

	return min;
}
