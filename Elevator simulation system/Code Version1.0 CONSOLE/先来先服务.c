#include"elevator struct.h"


int orderServe(int out[],
	Input in[],
	int time,
	int in_size,
	int *condition)//size存储指令
{
	int floor=out[time],
		target=0;//floor当前层数，out【】记录上一时刻层数
	Input *Ptr=NULL;

	int scanInput(Input in[],int,Input**);//确定target楼层

	if((target=scanInput(in,in_size,&Ptr))==0)
	{
		out[time+1]=out[time];
		*condition=-2;
	}
	else if(target==floor)
	{
		out[time+1]=out[time];
		if(Ptr!=NULL){
			Ptr->is_done=1;
			Ptr=NULL;
		}
	}
	else
	{
		*condition=(target>floor?1:-1);
		out[time+1]=out[time]+*condition;
	}

	return 0;

}

int scanInput(Input in[],int size,Input **nPtr)//用于确定目标楼层
{
	int i/*循环变量*/,minTime=0,isFirst=0/*不是第一个*/,Tgt;//mintime记录输入最短时间的指令
	int returnFloor(char);
	for(i=1;i<=size;i++) if(in[i].is_done==0)
	{
		if(isFirst==0){
			minTime=in[i].time;
			Tgt=returnFloor(in[i].order);
			*nPtr=&in[i];
			isFirst=1;
		}
		else if(minTime>in[i].time){
			minTime=in[i].time;
			Tgt=returnFloor(in[i].order);
			*nPtr=&in[i];
		}
	}

	if(minTime==0)
		return 0;
	else return Tgt;
}

int returnFloor(char order)//将字符串指令转化成数字楼层
{
	extern char stdCPT[];//标准大写字母
	extern char stdSML[];//标准小写字母
	int j/*循环变量*/;
	for(j=0;j<27;j++)
		if(stdCPT[j]==order || stdSML[j]==order)
//		{
//			printf("%d\n",)
			return j%9+1;//转化为数字楼层
//		}
	return 0;
}