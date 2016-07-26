#include <string.h>
#include "egg.h"
#include "cmc.h"

extern HEGG main_egg;//主蛋的句柄
void act_string(char *string,int delay);//传进要打印的字符，和字与字的时间间隔,让字符动态打印(要包含<string.h>)

void egg_tips2()//电梯界面中各按键功能介绍
{
	HEGG second_egg; 
	char infor3[]="大家不要心急，在使用之前先来看看相关说明吧，有助于你更好的使用201021131603小组的模拟电梯"; 
	
    second_egg=LayEgg();
    DrawBitmap("bitmap//开始2.bmp");
	ChangeEggLayer(TOP);
    
    MovePen(300,670);
    SetPenColor(BLUE);
    act_string(infor3,50);
    
    //策略选择盘使用说明 
    SetPenColor(MAGENTA);
    MovePen(10,650);
    DrawBitmap("bitmap//celue1.bmp");
    MovePen(260,630);
    DrawString("1:先来先服务策略");
	MovePen(260,587);
	DrawString("2:顺便服务策略"); 
	MovePen(260,544);
	DrawString("3:最快响应策略");
	MovePen(260,501);
	DrawString("4:最短平均时间策略");
	MovePen(260,458);
	DrawString("5:宏福策略");
	MovePen(260,420);
	SetPenColor(BLACK);
	DrawString("(注:点击数字可以");
	MovePen(260,400);
	DrawString("改变成对应的策略)");
	SetPenColor(MAGENTA);
	WaitFor(500);
	
	//电梯内部箭头使用说明
	MovePen(10,300);
	DrawBitmap("bitmap//内部上行.bmp");
	MovePen(150,280);
	DrawString("电梯内部，向上运行中");
	
	MovePen(10,210);
	DrawBitmap("bitmap//内部下行.bmp");
	MovePen(150,190);
	DrawString("电梯内部，向下运行中"); 
	
	MovePen(10,120);
	DrawBitmap("bitmap//内部停.bmp");
	MovePen(150,100); 
	DrawString("电梯内部，电梯处于停止状态");
	
	MovePen(10,45);
	DrawBitmap("bitmap//不GO1.bmp");
	MovePen(100,30);
	DrawString("电梯内部，不使用GO键，开门请求");
	WaitFor(500);
	
	//电梯外部箭头说明
	SetPenColor(DARK_MAGENTA);
    MovePen(430,650);
    DrawBitmap("bitmap//外部上1.bmp"); 
    MovePen(500,630);
    DrawString("此时未点亮，表示电梯当");
	MovePen(500,610);
	DrawString("前不在上行(向下箭头同此)");
    
    MovePen(430,550);
    DrawBitmap("bitmap//外部上2.bmp");
    MovePen(500,530);
    DrawString("此时已点亮，表示电梯当"); 
	MovePen(500,510);
    DrawString("前正在上行(向下箭头同此)"); 

	WaitFor(500);

    MovePen(430,450);
    DrawBitmap("bitmap//外部上行2.bmp");
    MovePen(500,450);
    DrawString("电梯外部某一楼层向上请求处于空闲状态");
	
	MovePen(430,400);
	DrawBitmap("bitmap//外部下行2.bmp");
	MovePen(500,400);
	DrawString("电梯外部某一楼层向下请求处于空闲状态");
	
	MovePen(430,350);
	DrawBitmap("bitmap//外部上行.bmp");
	MovePen(500,350);
	DrawString("电梯外部某一楼层有向上请求");
	
	MovePen(430,300);
	DrawBitmap("bitmap//外部下行.bmp");
	MovePen(500,300);
	DrawString("电梯外部某一楼层有向下请求");
	
	MovePen(430,45);
	DrawBitmap("bitmap//GO1.bmp");
	MovePen(500,30);
	DrawString("电梯内部，使用GO键，开门请求"); 
	
	MovePen(400,200);
	DrawBitmap("bitmap//strategy1-1.bmp");
	MovePen(420,130);
	DrawString("实时显示电梯正在使用的策略"); 
	WaitFor(500);
	
	//电梯内部数字说明
	SetPenColor(BLACK);
	MovePen(830,650);
	DrawBitmap("bitmap//内1.bmp");
	MovePen(960,620);
	DrawString("电梯内部显示的当前电梯所在楼层"); 
	
	MovePen(830,550);
	DrawBitmap("bitmap//内部1-2.bmp");
	MovePen(905,545);
	DrawString("电梯内部该数字楼层未被请求");
	
	MovePen(830,450);
	DrawBitmap("bitmap//内部1-1.bmp");
	MovePen(905,445);
	DrawString("电梯内部有对去往该楼层的请求"); 
		
	//电梯外部数字说明
	MovePen(830,380);
	DrawBitmap("bitmap//外部1.bmp");
	MovePen(905,360);
	DrawString
	("电梯外部显示当前电梯所处于的楼层");
	WaitFor(500);
	
	MovePen(840,310);
	DrawBitmap("bitmap//提示.bmp");

	WaitFor(5000);

	EatEgg();

	return; 
} 

