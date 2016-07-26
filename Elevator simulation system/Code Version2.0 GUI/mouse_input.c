#include <stdio.h>
#include "egg.h"
#include "cmc.h"

extern int is_asked(char order);//传入用户输入的新指令，判断是否是重复的指令,重复返回1，否则返回0
extern void egg_order();
int hongfu_legal(char order);//判断输入是否合法,合法返回1，否则返回0


int mouse_input()
{
	int i,mx,my,event;
//	EVENT_TYPE WaitForEvent();
//	double GetMouseX(void);
//	double GetMouseY(void);

	while (initial==0);
	while( (event=WaitForEvent()) !=EXIT)
	{
		if (strategy==5 && event==MOUSEMOVE && (GetMouseX()<=610 && GetMouseX()>=590) && (GetMouseY()<=350 && GetMouseY()>=20))//扒门范围内
		{
			printf("\a");

			continue;
		}

		if (event==KEYDOWN)
		{
			mx=(int)GetMouseX();
			my=(int)GetMouseY();
			for(i=0;i<KEY_AMOUNT;i++)
				if(mx>=key_position[i].leftup_x &&
					mx<=key_position[i].rightdown_x &&
					my>=key_position[i].rightdown_y &&
					my<=key_position[i].leftup_y  &&
					is_asked(key_position[i].order)==0 &&
					(strategy!=5 || hongfu_legal(key_position[i].order)==1) )
				{
					if (key_position[i].order=='O' ||
						key_position[i].order=='P' ||
						key_position[i].order=='L' ||
						key_position[i].order=='N' ||
						key_position[i].order=='M' ||
						key_position[i].order=='0' ||
						key_position[i].order=='Z' ||
						key_position[i].order=='B')
					{
						if (key_position[i].order=='O')//先来先服务
							strategy=1;
						if (key_position[i].order=='P')//顺便服务
							strategy=2;
						if (key_position[i].order=='L')//最快响应
							strategy=3;
						if (key_position[i].order=='N')//最短平均等待时间
							strategy=4;
						if (key_position[i].order=='M')//宏福策略
							strategy=5;
						if (key_position[i].order=='0')//GO键
							is_go=1;
						if (key_position[i].order=='Z')//不GO键
							is_go=0;
						if (key_position[i].order=='B')//扒门键
						{
							if (!(strategy==5))
								break;
							else
							{
								input[++size].order=key_position[i].order;
								input[size].time=system_time;
								input[size].is_done=0;

							}
						}
					}
					else
					{
						input[++size].order=key_position[i].order;
						input[size].time=system_time;
						input[size].is_done=0;

						
						if (condition==-2)
							condition=1;//初始化为上升
					}
					break;
				}
				egg_order();
		}
		
	}
	return 0;
}

int hongfu_legal(char order)//判断输入是否合法,合法返回1，否则返回0
{
	int i;
	char hongfu[]="2345KJHGUYTRkjhguytr";//宏福策略中没有的指令
	
	for (i=0;i<=19;i++)
		if (order==hongfu[i])
			return 0;
	
	return 1;
}
