#include "elevator struct.h"

#define DEFAULT_DELAY 1000
#define DEFAULT_RATIO 5
#define DEFAULT_STRATEGY 1


typedef struct click_set
{
	int leftup_x;
	int leftup_y;
	int rightdown_x;
	int rightdown_y;
	char bitmap_R[27];
	char bitmap_B[27];
} Click;

extern HEGG main_egg;//主蛋

Click click[19]=	{
		{231,547,314,518,"bitmap//红使用默认参数.bmp","bitmap//蓝使用默认参数.bmp"},//0
		{386,547,529,518,"",""},
		{542,547,633,518,"",""},

		{244,470,304,426,"bitmap//红0.5秒.bmp","bitmap//蓝0.5秒.bmp"},//4
		{319,470,379,426,"bitmap//红1秒.bmp","bitmap//蓝1秒.bmp"},
		{398,470,458,426,"bitmap//红1.5秒.bmp","bitmap//蓝1.5秒.bmp"},
		{476,470,536,426,"bitmap//红2秒.bmp","bitmap//蓝2秒.bmp"},
		{556,470,616,426,"bitmap//红3秒.bmp","bitmap//蓝3秒.bmp"},

		{245,372,305,328,"bitmap//红一下.bmp","bitmap//蓝一下.bmp"},//8
		{320,372,380,328,"bitmap//红二下.bmp","bitmap//蓝二下.bmp"},
		{398,372,458,328,"bitmap//红三下.bmp","bitmap//蓝三下.bmp"},
		{476,372,536,328,"bitmap//红四下.bmp","bitmap//蓝四下.bmp"},
		{556,372,616,328,"bitmap//红五下.bmp","bitmap//蓝五下.bmp"},

		{674,521,906,493,"bitmap//红策略1.bmp","bitmap//蓝策略1.bmp"},//13
		{674,481,906,453,"bitmap//红策略2.bmp","bitmap//蓝策略2.bmp"},
		{674,442,906,414,"bitmap//红策略3.bmp","bitmap//蓝策略3.bmp"},
		{674,405,906,377,"bitmap//红策略4.bmp","bitmap//蓝策略4.bmp"},

		{936,554,969,428,"",""},//17
		{936,418,969,310,"",""},//18
		};

void act_string(char *string,int delay);//传进要打印的字符，和字与字的时间间隔,让字符动态打印

void egg_inner_condition(int floor,int dir)//打印egg库版本电梯内部的运行状态提示(floor为楼层 dir为方向 1上 -1下 0停 -2空闲)
{

	while (bitmap==1);
	ng=1;
	SetActiveEgg(main_egg);
	while (bitmap==1);
	MovePen(1046,609);
	if (dir!=-2)//不是空闲
	{
		switch (floor)
		{
		case 1:
			DrawBitmap("bitmap//内1.bmp");
			break;
		case 2:
			DrawBitmap("bitmap//内2.bmp");
			break;
		case 3:
			DrawBitmap("bitmap//内3.bmp");
			break;
		case 4:
			DrawBitmap("bitmap//内4.bmp");
			break;
		case 5:
			DrawBitmap("bitmap//内5.bmp");
			break;
		case 6:
			DrawBitmap("bitmap//内6.bmp");
			break;
		case 7:
			DrawBitmap("bitmap//内7.bmp");
			break;
		case 8:
			DrawBitmap("bitmap//内8.bmp");
			break;
		case 9:
			DrawBitmap("bitmap//内9.bmp");
			break;
		default:
			break;
		}
	}
	ng=0;

	while (bitmap==1);
	ng=0;
	MovePen(1046,542);
	if (dir==1)
		DrawBitmap("bitmap//内部上行.bmp");
	else if (dir==-1)
		DrawBitmap("bitmap//内部下行.bmp");
	else if (dir==-2)
	{
		MovePen(1046,609);
		DrawBitmap("bitmap//内部空闲.bmp");
	}
	else//=0
		DrawBitmap("bitmap//内部停.bmp");
	ng=1;

	return;

}

void egg_outer_condition(int floor,int dir)//打印egg库版本电梯外部的运行状态提示(floor为楼层 dir为方向 1上 -1下 0停 -2空闲)
{
	//static int step=0;

	while (bitmap==1);

	ng=1;
	SetActiveEgg(main_egg);

	if (dir==1)
	{
		MovePen(843,348);
		DrawBitmap("bitmap//外部上2.bmp");
		MovePen(843,282);
		DrawBitmap("bitmap//外部下1.bmp");
	}
	else if (dir==-1)
	{
		MovePen(843,348);
		DrawBitmap("bitmap//外部上1.bmp");
		MovePen(843,282);
		DrawBitmap("bitmap//外部下2.bmp");
	}
	else
	{
		MovePen(843,348);
		DrawBitmap("bitmap//外部上1.bmp");
		MovePen(843,282);
		DrawBitmap("bitmap//外部下1.bmp");
	}
	ng=0;

	while (bitmap==1);
	ng=1;
	MovePen(843,216);
	switch (floor)
	{
	case 1:
		DrawBitmap("bitmap//外部1.bmp");
		break;
	case 2:
		DrawBitmap("bitmap//外部2.bmp");
		break;
	case 3:
		DrawBitmap("bitmap//外部3.bmp");
		break;
	case 4:
		DrawBitmap("bitmap//外部4.bmp");
		break;
	case 5:
		DrawBitmap("bitmap//外部5.bmp");
		break;
	case 6:
		DrawBitmap("bitmap//外部6.bmp");
		break;
	case 7:
		DrawBitmap("bitmap//外部7.bmp");
		break;
	case 8:
		DrawBitmap("bitmap//外部8.bmp");
		break;
	case 9:
		DrawBitmap("bitmap//外部9.bmp");
		break;
	default:
		break;
	}
	ng=0;

	return;
}
/*(843,348)     (902,149)    dx=59    dy=199*/
/*(843,216)*/


int egg_tips()//打印egg库版本的初始化提示信息
{

	HEGG first_egg;//打印初始信息的egg
	char infor1[]="欢迎来到黄金梅里号~~";
	char infor2[]="为了使您“旅途愉快”，请先进行一下电梯参数的参数配置:";

	int situ,i/*counter*/;
	int mouseX,mouseY;

	int dealwith_click(int num);

	first_egg=LayEgg();
	DrawBitmap("bitmap//开始.bmp");

	MovePen(200,670);
	SetPenColor(BLUE);
	act_string(infor1,70);

	MovePen(200,650);
	SetPenColor(DARK_MAGENTA);
	act_string(infor2,60);

	//initialization
	MovePen(200,590);
	DrawBitmap("bitmap//scale.bmp");
	if(delay==DEFAULT_DELAY && ratio==DEFAULT_RATIO && strategy==DEFAULT_STRATEGY)
	{
		MovePen(click[0].leftup_x,click[0].leftup_y);
		DrawBitmap(click[0].bitmap_R);
	}
	switch(delay)
	{
		case 500:
			MovePen(click[3].leftup_x,click[3].leftup_y);
			DrawBitmap(click[3].bitmap_R);
			break;
		case 1000:
			MovePen(click[4].leftup_x,click[4].leftup_y);
			DrawBitmap(click[4].bitmap_R);
			break;
		case 1500:
			MovePen(click[5].leftup_x,click[5].leftup_y);
			DrawBitmap(click[5].bitmap_R);
			break;
		case 2000:
			MovePen(click[6].leftup_x,click[6].leftup_y);
			DrawBitmap(click[6].bitmap_R);
			break;
		case 3000:
			MovePen(click[7].leftup_x,click[7].leftup_y);
			DrawBitmap(click[7].bitmap_R);
			break;
	}
	MovePen(click[7+ratio].leftup_x,click[7+ratio].leftup_y);
	DrawBitmap(click[7+ratio].bitmap_R);
	MovePen(click[12+strategy].leftup_x,click[12+strategy].leftup_y);
	DrawBitmap(click[12+strategy].bitmap_R);

	while((situ=WaitForEvent())!=0)
	{
		mouseX=(int)GetMouseX();
		mouseY=(int)GetMouseY();

		if(situ==KEYDOWN)
		{
			for(i=0;i<19;i++)
			{
				if(click[i].leftup_x<=mouseX &&
					click[i].leftup_y>=mouseY &&
					click[i].rightdown_x>=mouseX &&
					click[i].rightdown_y<=mouseY)
				{
					int r;
					if((r=dealwith_click(i))==1)
					{
						EatEgg();
						return 1;
					}
					else if(r==-1)
					{
						EatEgg();
						return -1;
					}
					break;
				}
			}

		}
	}

	EatEgg();

	return 0;

}

void act_string(char *string,int delay)//传进要打印的字符，和字与字的时间间隔,让字符动态打印(要包含<string.h>)
{
	char ch[3];//缓冲字符串
	int i;

	for (i=1;i<=(int)strlen(string)/2+1;i++)
	{
		ch[0]=string[2*i-2];
		ch[1]=string[2*i-1];
		ch[2]='\0';
		DrawString(ch);
		WaitFor(delay);
	}

	return;
}



int dealwith_click(int num)
{
	void clean(int order);

	switch(num)
	{
	case 0:
		delay=1000;
		ratio=5;
		strategy=1;

		clean(0);clean(1);clean(2);	//unvalue all clicks
		MovePen(click[0].leftup_x,click[0].leftup_y);
		DrawBitmap(click[0].bitmap_R);
		MovePen(click[4].leftup_x,click[4].leftup_y);
		DrawBitmap(click[4].bitmap_R);
		MovePen(click[12].leftup_x,click[12].leftup_y);
		DrawBitmap(click[12].bitmap_R);
		MovePen(click[13].leftup_x,click[13].leftup_y);
		DrawBitmap(click[13].bitmap_R);

		break;

	case 1:
	case 2:
		 break;

	//change delay
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		switch(num)
		{
			case 3: delay=500; break;
			case 4:	delay=1000; break;
			case 5: delay=1500; break;
			case 6: delay=2000; break;
			case 7: delay=3000; break;
		}
		clean(0);
		MovePen(click[num].leftup_x,click[num].leftup_y);
		DrawBitmap(click[num].bitmap_R);
		//unvalue default
		MovePen(click[0].leftup_x,click[0].leftup_y);
		DrawBitmap(click[0].bitmap_B);

		break;

	//change ratio
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		ratio=num-7;
		clean(1);
		MovePen(click[num].leftup_x,click[num].leftup_y);
		DrawBitmap(click[num].bitmap_R);
		//unvalue default
		MovePen(click[0].leftup_x,click[0].leftup_y);
		DrawBitmap(click[0].bitmap_B);

		break;

	//change strategy
	case 13:
	case 14:
	case 15:
	case 16:
		strategy=num-12;
		clean(2);
		MovePen(click[num].leftup_x,click[num].leftup_y);
		DrawBitmap(click[num].bitmap_R);
		//unvalue default
		MovePen(click[0].leftup_x,click[0].leftup_y);
		DrawBitmap(click[0].bitmap_B);

		break;

	case 17: return -1;
	case 18: return 1;
	}
	return 0;
}

void clean(int order)
{
	const int sort[3]={2,7,12};
	int i;/*counter*/
	if(order==2)
		for(i=1;i<=4;i++)
		{
			MovePen(click[sort[2]+i].leftup_x,click[sort[2]+i].leftup_y);
			DrawBitmap(click[sort[2]+i].bitmap_B);
		}
	else
		for(i=1;i<=5;i++)
		{
			MovePen(click[sort[order]+i].leftup_x,click[sort[order]+i].leftup_y);
			DrawBitmap(click[sort[order]+i].bitmap_B);
		}
}
