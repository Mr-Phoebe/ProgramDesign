#include "elevator struct.h"

int is_repeating(char order);//传入用户输入的新指令，判断是否是重复的指令,重复返回1，否则返回0
void egg_order();


int mouse_input()
{
	int i,mx,my,event;

	while(initial==0);
	while((event=WaitForEvent()) !=EXIT)
	{
		if(event==KEYDOWN)
		{
			mx=(int)GetMouseX();
			my=(int)GetMouseY();
			for(i=0;i<KEY_AMOUNT;i++)
				if(mx>=click_position[i].leftup_x &&
					mx<=click_position[i].rightdown_x &&
					my>=click_position[i].rightdown_y &&
					my<=click_position[i].leftup_y  &&
					is_repeating(click_position[i].order)==0)
				{
					if (click_position[i].order=='O' ||
						click_position[i].order=='P' ||
						click_position[i].order=='L' ||
						click_position[i].order=='N' ||
						click_position[i].order=='X' ||
						click_position[i].order=='Z')
					{
					    switch(click_position[i].order)
					    {
					        case 'O'://先来先服务
                                strategy=1;
                                break;
                            case 'P'://顺便服务
                                strategy=2;
                                break;
                            case 'L'://最快响应
                                strategy=3;
                                break;
                            case 'N'://最短平均等待时间
                                strategy=4;
                                 break;
                            case 'X'://GO键
                                is_go=1;
                                break;
                            case 'Z'://不GO键
                                is_go=0;
                                break;
					    }

					}
					else
					{
						input[++size].order=click_position[i].order;
						input[size].time=system_time;
						input[size].is_done=0;

						if (dir==-2)
							dir=1;//初始化为上升
					}
					break;
				}
				egg_order();
		}

	}
	return 0;
}
