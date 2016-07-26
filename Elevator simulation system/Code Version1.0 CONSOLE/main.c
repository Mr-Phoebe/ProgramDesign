/*
	被响应后对应请求的is_done的数值在策略函数里面修改
	output[i]=output[i+1]表示响应该楼层的停靠请求
	每个策略函数只写下一时刻的命令
	指令对应的大小写通用
	策略函数必须引用condition变量，但仅有将其改为-2（电梯空闲）的责任	
	  ！！！取消电梯的condition=0的停靠状态
    自动忽略重复指令(新增功能)
	规定input[]的下标为从1开始
	自动忽略错误指令(新增功能)
*/
/*
  指令对应关系：1-9代表电梯内乘客按目标按钮；Q、W、E、R、T、Y、U、I对应8层到1层的上行请求，
				A、S、D、F、G、H、J、K表示9层到2层的下行请求。
*/

#include "elevator struct.h"
 

/*--------------------------------------------------策略函数的声明------------------------------------------------------------*/
extern int orderServe(int out[],
	Input in[],
	int time,
	int in_size,int*
	);
extern void fastest_respond(Input input[],int size,int system_time,int output[],int condition);
extern int assistServe(int out[],int time,
				int *direction/*-2 for vacant
								0 for pause
								-1,1 respectively for downward and upward*/,
				Input in[],
				int in_size);
extern void least_wait(Input input[],int size,int system_time,int output[],int condition);
/*--------------------------------------------------策略函数的声明------------------------------------------------------------*/


/*--------------------------------------------------main.c的函数声明----------------------------------------------------------*/
int is_repeating(char order);//传入用户输入的新指令，判断是否是重复的指令,重复返回1，否则返回0
void get_input();//处理用户的请求输入，并写入到对应的结构体数组中(*size 指向对应当前input数组的大小)
void respond();//转化输出部分,并在响应后更改input中的is_done变量
void print_tips();//打印用户输入指令提示
void gotoxy(int x, int y);//定位到第y行的第x列
void clear_screen();//XP下的代替system("command/ccls")的清屏函数
void run_light();//打印电梯的运行状况
int is_legal(char order);//判断输入是否合法,h合法返回1，否则返回0
void main_trans(int inner[],int outer_up[],int outer_down[]);//主函数中用于遍历转换输入的数组
void order_light();//打印剩余的指令
void print_line(char ch);//打印屏幕分割行，传进字符的值
void deploy();//进行电梯配置
/*--------------------------------------------------main.c的函数声明----------------------------------------------------------*/

/*Mr.Phoebe在顺便服务里面的常量*/
const char stdCPT[]={"LASDFGHJK123456789QWERTYUIO"};//LKJHGFDSA123456789IUYTREWQO
const char stdSML[]={"lasdfghjk123456789qwertyuio"};//lkjhgfdsa123456789iuytrewqo
/*Mr.Phoebe在顺便服务里面的常量*/


/*-------------------------------------------------------全局变量-------------------------------------------------------------*/
//静态全局什么的真讨厌
static int system_time=1;//记录当前仿真时间
static Input input[500];//记录用户的输入请求指令,下标从一开始
static int size=0;//input数组的当前元素个数
static int condition=1;//表示电梯当前的状态（/*0停止*/ 1上升 -1下降 -2空闲）
static int output[1001]={0};//储存每个仿真时刻的电梯状态的数组，下标表示时间（如output[0]=1表示电梯在第0秒处于第一层）
static Output possition[1001];//记录电梯1000内的运行情况
static int is_go=0;//=1表示关门键被按下,-1表示开门键被按下
static int delay=3000;//每次行动等待时间
static int ratio=5;//等待时间与上升时间的比例
static int Tflag=0;//=0表示get_input还不能走
static int output_way=1;//1表示动画方式，2表示快速方式，3表示完全方式
static int strategy=1;//当前采取的策略号
static FILE* out_fptr=NULL;
/*-------------------------------------------------------全局变量-------------------------------------------------------------*/

int main()
{	
	int i;
	DWORD Thread1;
	HANDLE thread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)get_input,NULL,0,&Thread1);//新线程1
	
	print_line(3);
	printf("欢迎您进入模拟学五楼电梯系统(By——Mr.Phoebe coding studio)\n");
	printf(
			"编写小组：201321130301组\n"
			"编写人员:吴浩男、杜宇、金东赫\n"
			"编写时间:2013年5月1日\n");
	print_line(3);
	printf("\n");

	printf("请选择是否进行电梯参数配置:\n");
	printf("1、进入配置\n2、使用默认参数\n");
	scanf("%d",&i);
	fflush(stdin);
	clear_screen();
	if (i==1)
		deploy();

	printf("请输入你准备采用的策略号：\n1、先来先服务策略\n2、顺便服务策略\n3、最快响应策略\n");
	printf("4、最短平均等待时间策略\n");
	scanf("%d",&strategy);
	fflush(stdin);

	Tflag=1;//表示get_input可以走了

	output[1]=1;//初始化
	possition[1].floor=1;
	possition[1].statue=-2;

//	system("command/ccls");
	clear_screen();
	order_light();
	print_tips();

	while (1)
	{
	//	get_input(system_time,input,&size,&condition);//接受用户输入，转化策略
		
		switch (strategy)
		{
			
		case 1://先来先服务策略
			orderServe(output,input,system_time,size,&condition);//先来先服务策略函数
			break;

		case 2://顺便服务策略
		//	printf("调用策略函数在%d时刻\n",system_time);
			assistServe(output,system_time,&condition,input,size);
			//顺便服务策略函数
			break;

		case 3://最快响应策略
		//	printf("调用策略函数在%d时刻\n",system_time);
			fastest_respond(input,size,system_time,output,condition);//最快响应策略函数
			break;

		case 4://最短平均时间策略
		//	printf("调用策略函数在%d时刻\n",system_time);
			least_wait(input,size,system_time,output,condition);//最短平均时间策略函数
			break;

		default:
			break;
		}

/*转化输出部分*/
		respond();
	//	system("command/ccls");
		clear_screen();
		order_light();
		if (output_way!=2)
			run_light();
		print_tips();
/*转化输出部分*/

		Sleep(delay);
		system_time++;//仿真时间向后推进
	}

	return 0;
}

void get_input()//处理用户的请求输入，并写入到对应的结构体数组中(*size 指向对应当前input数组的大小)
{
		char ch[50];//缓冲字符串
		int i=0;

		while (Tflag==0);//等待主函数结束

	//	Sleep(1000);
		while (1)
		{
			i=0;
			gets(ch);

			gotoxy(0,0);
		//	system("command/ccls");
			clear_screen();
			gotoxy(0,0);
			order_light();	
			if (output_way!=2)
				run_light();
			print_tips();

			while (ch[i]!='\0')//'\0'表示输入结束
			{
				if (ch[i]=='O' || ch[i]=='o')//先来先服务
					strategy=1;
				if (ch[i]=='P' || ch[i]=='p')//顺便服务
					strategy=2;
				if (ch[i]=='L' || ch[i]=='l')//最快响应
					strategy=3;
				if (ch[i]=='N' || ch[i]=='n')//最短平均等待时间
					strategy=4;
				if (ch[i]=='Z'||ch[i]=='z')
					is_go=1;
				if (ch[i]=='X'||ch[i]=='x')
					is_go=-1;
				if (ch[i]!=' ' && is_repeating(ch[i])==0 && is_legal(ch[i])==1)
				{
					size++;
					input[size].order=ch[i];
					input[size].is_done=0;
					input[size].time=system_time;	
			//		printf("在%d时刻，输入的%c指令",input[size].time,input[size].order);
					if (condition==-2)
						condition=1;//初始化为上升
				}
				i++;
			}
		}
}

void respond()//转化输出部分,并在响应后更改input中的is_done变量
{

	possition[system_time].floor=output[system_time];
	
	if (output[system_time+1]==output[system_time])//下一个时刻和当前时刻的电梯层数相同（不移动）
	{
		int flag=0;//等待GO的时间
		
		if (output_way!=1 && out_fptr==NULL)
			if ( (out_fptr=fopen("output.txt","a+"))==NULL)
			{
				printf("打开文件失败！\n");
				Sleep(5555);
			}
		if (output_way!=1)
		{
			fprintf(out_fptr,"%d %d\n",system_time,output[system_time]);
			fclose(out_fptr);
			out_fptr=NULL;
		}

		is_go=0;
		possition[system_time].statue=0;	
		while (is_go!=1 && flag<=ratio-2)//GO键还没有被按下
		{
		
		//	system("command/ccls");
			clear_screen();
			order_light();
			run_light();
			print_tips();

			Sleep(delay);
			system_time++;
			output[system_time+1]=output[system_time];
			possition[system_time].floor=output[system_time];
			possition[system_time].statue=0;
			if(is_go==-1)
			{
				flag=0;
				is_go=0;
			}
			else
				flag++;
		}
		possition[system_time].statue=101;
		is_go=0;
	}

	else if (output[system_time+1]==100*output[system_time] || condition==-2)
	{
		condition=-2;
		output[system_time+1]=output[system_time];
		possition[system_time].statue=-2;
	}
	else if (output[system_time+1] > output[system_time])//电梯要上升
	{
		condition=1;
		possition[system_time].statue=1;
	}
	else//电梯要下降
	{
		condition=-1;
		possition[system_time].statue=-1;
	}
}

void run_light()//打印电梯的运行状况
{
	int i;
	int min;

	min=max(1,system_time-10);//打印最多10条记录

	for (i=min;i<=system_time;i++)
	{
		if (possition[i].statue==-2 || condition==-2)//当前时刻为空闲
			printf("第%d时刻:电梯在%d楼，而且处于空闲状态\n",i,possition[i].floor);
		else if (possition[i].statue==0)//当前时刻电梯开门等待
			printf("第%d时刻:在%d层开门等待\n",i,possition[i].floor);
		else if (possition[i].statue==101)//合上门
			printf("第%d时刻:在%d层关门，准备出发啦~\n",i,possition[i].floor);
		else//当前时刻电梯要上升或者下降
			printf("第%d时刻:%d楼->%d楼\n",i,possition[i].floor,possition[i].floor+possition[i].statue);
	}

	return;
}




void print_tips()//打印用户输入指令提示
{
	int i;

//	printf("\n");
	for (i=1;i<=80;i++)
		printf("*");
	printf("随时切换策略:O—先来先服务 P—顺便服务 L—最快响应 N—最短等待\n");
	printf("指令对应关系：1-9代表电梯内乘客按目标按钮 Z代表关门键 X代表开门键\nQ、W、E、R、T、Y、U、I对应1层到8层的上行请求\n");
	printf("A、S、D、F、G、H、J、K表示2层到9层的下行请求\n");
	printf("\t\t\tBY Mr.Phoebe coding studio\n");
	for (i=1;i<=80;i++)
		printf("*");
	printf("请依次输入您的指令，并敲击回车键:\n");
//	printf("\n");

	return;
}

void order_light()//打印剩余的指令
{
	int inner[10]={0};//打表
	int outer_up[10]={0};
	int outer_down[10]={0};
	int i;

	main_trans(inner,outer_up,outer_down);//转换剩余指令

//	printf("\n");
	for (i=1;i<=80;i++)
		printf("#");
	printf("电梯内部未完成指令:");
	for (i=1;i<=9;i++)
		if (inner[i]==1)
			printf("%d  ",i);
	printf("\t\t当前采用的策略为:");
	switch (strategy)
	{
	case 1:
		printf("先来先服务策略");
		break;
	case 2:
		printf("顺便服务策略");
		break;
	case 3:
		printf("最快响应策略");
		break;
	case 4:
		printf("最短平均等待时间策略");
		break;
	default:
		break;
	}

	printf("\n");
	printf("电梯外部未完成指令:");
	for (i=1;i<=8;i++)
		if (outer_up[i]==1)
			printf("%d楼上  ",i);
	printf("\n");
	printf("                   ");
	for (i=2;i<=9;i++)
		if (outer_down[i]==1)
			printf("%d楼下  ",i);
	printf("\n");
	for (i=1;i<=80;i++)
		printf("#");
//	printf("\n");
	
	return;
}

int is_legal(char order)//判断输入是否合法,合法返回1，否则返回0
{
	int i;
	char board[]="oOLl";

	for (i=0;i<=3;i++)
		if (order==board[i])
			return 0;
	
	if (order=='b' || order=='B')
		return 1;
	
	for (i=0;stdSML[i]!='\0' && stdCPT[i]!='\0';i++)
		if (order==stdSML[i] || order==stdCPT[i])
			return 1;
	
	return 0;
}

int is_repeating(char order)//传入用户输入的新指令，判断是否是重复的指令,重复返回1，否则返回0
{
	int i;
	
	for (i=1;i<=size;i++)
		if (input[i].order==order && input[i].is_done==0)
			return 1;

	return 0;
}

void clear_screen()//XP下的代替system("command/ccls")的清屏函数,用光标移动清屏
{
	int i;
	//system ("cls");
	gotoxy(0,0);
	for (i=1;i<=250;i++)
		printf("\t");
	gotoxy(0,0);

	return;
}

void gotoxy(int x, int y)//光标移动到第x行的第y列
{
    int xx=0x0b;
    HANDLE hOutput;
    COORD loc;
    loc.X = y;
    loc.Y=x;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc);
    return;
}

void main_trans(int inner[],int outer_up[],int outer_down[])//主函数中用于遍历转换输入的数组
{  
	int i;
	int floor=0;
/*
	memset(inner,0,sizeof(inner));
	memset(outer_up,0,sizeof(outer_up));
	memset(outer_down,0,sizeof(outer_down));
*/
	for (i=1;i<=size;i++)
	{
		if (input[i].is_done==0)//没有被响应的请求
		{
			if (input[i].order<='9' && input[i].order>='1')//内部请求
				inner[input[i].order-'0']=1;

			else//外部请求
			{
				switch (input[i].order)
				{
				case 'Q':case 'q'://一层上行
					outer_up[1]=1;
					break;
				case 'W':case 'w'://二层上行
					outer_up[2]=1;
					break;
				case 'E':case 'e'://三层上行
					outer_up[3]=1;
					break;
				case 'R':case 'r'://四层上行
					outer_up[4]=1;
					break;
				case 'T':case 't'://五层上行
					outer_up[5]=1;
					break;
				case 'Y':case 'y'://六层上行
					outer_up[6]=1;
					break;
				case 'U':case 'u'://七层上行
					outer_up[7]=1;
					break;
				case 'I':case 'i'://八层上行
					outer_up[8]=1;
					break;
				case 'A':case 'a'://二层下行
					outer_down[2]=1;
					break;
				case 'S':case 's'://三层下行
					outer_down[3]=1;
					break;
				case 'D':case 'd'://四层下行
					outer_down[4]=1;
					break;
				case 'F':case 'f'://五层下行
					outer_down[5]=1;
					break;
				case 'G':case 'g'://六层下行
					outer_down[6]=1;
					break;
				case 'H':case 'h'://七层下行
					outer_down[7]=1;
					break;
				case 'J':case 'j'://八层下行
					outer_down[8]=1;
					break;
				case 'K':case 'k'://九层下行
					outer_down[9]=1;
					break;
				default://九层无上，一层无下
					break;
				}
		
			}
		}
	}//请求转换完毕

	return;
}


void print_line(char ch)//打印屏幕分割行，打印换行呵呵
{
	int i;

	for (i=1;i<=80;i++)
		printf("%c",ch);
	//printf("\n");

	return;
}

void deploy()//进行电梯配置，用户自行更改输入
{
	int flag=0;

	while (flag==0)//输入不正确
	{
		printf("请输入一个正整数，设置每次行动电梯所需要的时间(单位秒):\n");
		scanf("%d",&delay);
		flag=1;
		if (delay<=0)
		{
			flag=0;
			printf("请重新输入输入大于0的整数！\n");
		}
	}
	delay*=1000;
	flag=0;

	while (flag==0)
	{
		printf("请输入一个正整数，设置电梯停靠所需要的仿真时间数:\n");
		scanf("%d",&ratio);
		flag=1;
		if (ratio<=0)
		{
			flag=0;
			printf("请重新输入输入大于0的整数！\n");
		}
	}
	flag=0;

	while (flag==0)
	{
		printf("请选择程序运行方式:\n"
			"1、屏幕输出\n2、快速方式\n3、完全方式\n");
		scanf("%d",&output_way);
		flag=1;
		if (!(output_way<=3 && output_way>=0))
		{
			printf("对不起，请正确输入!\n");
			flag=0;
		}
	}

	return;
}


	