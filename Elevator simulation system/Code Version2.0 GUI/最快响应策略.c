/*
  problem:如果要区分外部的请求（上下行），那它们有什么不同的影响呢？貌似对本策略没有影响……
		  另外欢迎各位指出调试过程中的各种Bug~敝人不胜感激~ ——Mr.Phoebe coding studio(4-27)
		  最快响应策略：
		响应所有现在存在的所有呼叫和目标所需时间（采用不同方案电梯停靠时间相同，所以不必考虑）最短的策略。
		可选方案一是电梯先向上运行响应经过各层的目标和向上呼叫，再向下运行响应所有向下呼叫以及途经各层的目标，
		最后再向上响应剩余的向上呼叫。二是恰好相反，先向下，再向上，最后再向下运行。
		由于呼叫和目标会随时增加，所以实际上有时这种策略并不好。另外有时这将导致电梯突然向相反的方向运行。
		为了防止经常性的改变方向，我们采用设定只有当原来的运行方向比相反方向的代价高20%的时候才切换方向。 

*/
#include "elevator struct.h"


void fastest_respond(Input input[],int size,int system_time,int output[],int direction)
/*
	函数功能:最快相应策略函数，通过分析电梯的状态和用户请求，将指令存入output[]，并改变direction
	参数说明:input[]是存储用户的输入指令，包含char order 和 int time两个参数，size是当前结构体数组input[]
			 的指令个数。system_time表示当前的系统时间，output[]储存电梯的指令(下标为时刻)，conditon表示
			 电梯当前的状态（0表示停止 1上升 -1下降 -2表示空闲无请求）
	指令对应关系:1-9代表电梯内乘客按目标按钮；Q、W、E、R、T、Y、I、O对应1层到8层的上行请求，
				A、S、D、F、G、H、J、K表示2层到9层的下行请求。
*/
{		

	void trans(Input input[],int size,C_fast1 inner_ask[10],C_fast2 outer_ask[10],int system_time,int current_floor);
	/*
		函数功能:将用户的指令转换成数字
		参数说明:inner_ask[10].value(=1表示已经按下 =0表示没有按下)
				 outer_ask[10].value(=0表示无请求 =1表示有上行请求 =-1表示有下行请求 =2表示有两种请求)
	*/
	int count_time(C_fast1 inner_ask[10],C_fast2 outer_ask[10],int floor,int direction);
	//返回优先direction方向（1表示'up'，-1表示'down'）所需的时间

	int max_3(int a,int b,int c);//返回3个数的最大值
	int min_3(int a,int b,int c);//返回3个数的最小值

	C_fast1 inner_ask[10]={0,0};//电梯外部指令,下标从1开始
	C_fast2 outer_ask[10]={0,0};//电梯内部指令,下标从1开始
	int current_floor;
	

	current_floor=output[system_time];
	trans(input,size,inner_ask,outer_ask,system_time,current_floor);//转换用户的输入
	if (inner_ask[0].value==-2)//direction为空闲
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
		if (outer_ask[current_floor].value==direction)//外部恰有且仅有一个可以响应的请求	
		{
			outer_ask[current_floor].value=0;
			if (direction==1)//方向相同的响应完成
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
			outer_ask[current_floor].value=(-direction);
	
			if (direction==1)
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
			if (count_time(inner_ask,outer_ask,current_floor+direction,direction)*5 > count_time(inner_ask,outer_ask,current_floor+direction,-direction)*6) //20%则掉头
			//需要响应此请求并掉头
			{
				outer_ask[current_floor].value=0;
				if (direction==1)
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
	if (count_time(inner_ask,outer_ask,current_floor,direction)*5 < count_time(inner_ask,outer_ask,current_floor,-direction)*6) 
		output[system_time+1]=current_floor+direction;//保持当前行进状态

	else
		output[system_time+1]=current_floor-direction;//掉头

	return;
}

int max_3(int a,int b,int c)//返回3个数的最大值
{
	int maxn=max(a,b);
	return max(maxn,c);
}

int min_3(int a,int b,int c)//返回3个数的最小值
{
	int mi=min(a,b);
	return min(mi,c);
}

 void trans(Input input[],int size,C_fast1 inner_ask[10],C_fast2 outer_ask[10],int system_time,int current_floor)
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
		if (!input[i].is_done)//没有被响应的请求
		{
			flag=1;
			if (input[i].order<='9' && input[i].order>='1' && !(input[i].time==system_time-1 && input[i].order==current_floor+48) )//内部请求
			{
				inner_ask[input[i].order-48].time=system_time-input[i].time;
				inner_ask[input[i].order-48].value=1;
				inner_ask[input[i].order-48].index=i;
			}

			else//外部请求
			{
				switch (input[i].order)
				{
					case 'Q':case 'q'://一层上行
						floor=1;
						break;
					case 'W':case 'w'://二层上行
						floor=2;
						break;
					case 'E':case 'e'://三层上行
						floor=3;
						break;
					case 'R':case 'r'://四层上行
						floor=4;
						break;
					case 'T':case 't'://五层上行
						floor=5;
						break;
					case 'Y':case 'y'://六层上行
						floor=6;
						break;
					case 'U':case 'u'://七层上行
						floor=7;
						break;
					case 'I':case 'i'://八层上行
						floor=8;
						break;
					case 'A':case 'a'://二层下行
						floor=-2;
						break;
					case 'S':case 's'://三层下行
						floor=-3;
						break;
					case 'D':case 'd'://四层下行
						floor=-4;
						break;
					case 'F':case 'f'://五层下行
						floor=-5;
						break;
					case 'G':case 'g'://六层下行
						floor=-6;
						break;
					case 'H':case 'h'://七层下行
						floor=-7;
						break;
					case 'J':case 'j'://八层下行
						floor=-8;
						break;
					case 'K':case 'k'://九层下行
						floor=-9;
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
	if (!flag)
		inner_ask[0].value=-2;

	return;
}	

int count_time(C_fast1 inner_ask[10],C_fast2 outer_ask[10],int current_floor,int direction)
	//返回优先direction方向（1->'u' or -1->'d'）所需的时间
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

	for (i=1;i<=current_floor-1;i++)
	{
		if ((outer_ask[i].value==1 || outer_ask[i].value==2) && (low_up < i || low_up==10))//最大上行（当前楼层下面）
			low_up=i;
		if ((outer_ask[i].value==-1 || outer_ask[i].value==2) && (low_down < i || low_down==10))//最大下行（当前楼层下面）
			low_down=i;
	}	
	for (i=current_floor+1;i<=9;i++)
	{
		if ((outer_ask[i].value==1 || outer_ask[i].value==2) && high_up < i)//最大上行（当前楼层上面）
			high_up=i;
		if ((outer_ask[i].value==-1 || outer_ask[i].value==2) && high_down < i)//最大下行（当前楼层上面）
			high_down=i;
	}//寻找外部最值

	if (direction==1)
	{
		if (max_3(max_in,high_up,high_down) > current_floor)//需要上行
		{
			time+=max_3(max_in,high_up,high_down)-current_floor;

			if (min_3(min_in,low_up,low_down) >= current_floor)//不需要再下行
				return high_down==0?time:time+max_3(max_in,high_up,high_down)-high_down;//没有向下的请求（停在最高点）：有向下的请求（停在向下请求的最高点）
			else
			{
				time*=2;//下行到原位置(来回)
				time+=current_floor-min_3(min_in,low_up,low_down);

				return low_up==10?time:time+low_up-min_3(min_in,low_up,low_down);
			}
		}
		else
			return 360;//针对此策略必然先上行不行，因此返回最大值
	}	
	else 
	{
		if (min_3(min_in,low_up,low_down) < current_floor)//需要下行
		{
			time+=current_floor-min_3(min_in,low_up,low_down);

			if (max_3(max_in,high_up,high_down) <= current_floor)//不需要上行
				return low_up==10?time:time+low_up-min_3(min_in,low_up,low_down);
			else
			{
				time*=2;//上行到原位置
				time+=max_3(max_in,high_up,high_down)-current_floor;

				return high_down==0?time:time+max_3(max_in,high_up,high_down)-high_down;
			}
		}	
		else
			return 360;
	}
	
}


