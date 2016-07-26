/*先来先服务策略：
将所有的呼叫和目标按照到达时间的先后进行排队，然后一一响应（或完成）。
这是相当简单的策略，只需要设计一个将呼叫和目标排队的数据结构(队列)。
因为该策略效率也很低，所以也没有实际的电梯采用这种策略。
*/

#include"elevator struct.h"


int orderServe(int out[],
	Input in[],
	int time,
	int in_size,
	int *direction)//size存储指令
{
	int floor=out[time],
		target=0;//floor当前层数，out【】记录上一时刻层数
	Input *Ptr=NULL;

	int scanInput(Input in[],int,Input**);//确定target楼层

	if((target=scanInput(in,in_size,&Ptr))==0)//空闲
	{
		out[time+1]=out[time];
		*direction=-2;
	}
	else if(target==floor)
	{
		out[time+1]=out[time];
		if(Ptr!=NULL)//队列处理
		{
			Ptr->is_done=1;
			Ptr=NULL;
		}
	}
	else
	{
		*direction=(target>floor?1:-1);//方向
		out[time+1]=out[time]+*direction;//下一个状态
	}

	return 0;

}

int scanInput(Input in[],int size,Input **nPtr)//用于确定目标楼层
{
	int i/*循环变量*/,minTime=0,isFirst=0/*不是第一个*/,Tgt;//mintime记录输入最短时间的指令
	int returnFloor(char);
	for(i=1;i<=size;i++) if(in[i].is_done==0)
	{
		if(!isFirst)
		{
			minTime=in[i].time;
			Tgt=returnFloor(in[i].order);
			*nPtr=&in[i];
			isFirst=1;
		}
		else if(minTime>in[i].time)
		{
			minTime=in[i].time;
			Tgt=returnFloor(in[i].order);
			*nPtr=&in[i];
		}
	}

	if(!minTime)
		return 0;
	else
		return Tgt;
}

int returnFloor(char order)//将字符串指令转化成数字楼层
{
	extern char stdCPT[];//标准大写字母
	extern char stdSML[];//标准小写字母
	int i;
	for(i=0;i<27;i++)
		if(stdCPT[i]==order || stdSML[i]==order)
//		{
//			printf("%d\n",)
			return i%9+1;//转化为数字楼层
//		}
	return 0;
}