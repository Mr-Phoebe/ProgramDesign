#include "cmc.h"

extern char stdCPT[];
extern char stdSML[];//商汝麒童鞋在顺便服务里面的常量

int assistServe(int out[],int time,
				int *direction/*-2 for vacant
								0 for pause
								-1,1 respectively for downward and upward*/,
				Input in[],
				int in_size)
{
	int keySitu[3][9]={0}/*to save situation of keys
							[1][]for internal,[2][]for external up,[0][]for external down,[][n]for n+1 floor
							1 for selected, 0 for not*/,
		floor=out[time]-1,
		drt=-2/*direction prepared*//*-2 for vacant*/;

	int transform(Input*,int,int,int,int[][9],int*);
	int newDirection(int[][9],int,int*,int);
	int killOrder(Input in[],int direction, int floor,int size);

	if(!transform(in,in_size,time,floor,keySitu,&drt))/*empty*/{
		*direction=-2;
		out[time+1]=100*out[time];
		return -2;
	}
	else /*not empty*/
	{
		newDirection(keySitu,floor,&*direction,drt);

		if(keySitu[1][floor] ||
			(keySitu[0][floor] && *direction==-1) || 
			(keySitu[2][floor] && *direction==1))//need to pause
		{
			out[time+1]=out[time];
			//kill keySitu
			keySitu[1][floor]=0; 
			if(*direction==-2)
				keySitu[0][floor]=keySitu[2][floor]=0;
			else
				keySitu[1+*direction][floor]=0;

			killOrder(in,*direction,floor,in_size);//kill orders done
			return 0;/*0 for need to pause*/
		}
		else//needn't to pause, that's to move
		{
			if(*direction==-2)//pause at last interval
				*direction=drt;
			if(*direction==-2){
				out[time+1]=out[time];
				return *direction;//return -2 for didn't move
			}
			else{//direction != -2, is to move
				out[time+1]=out[time]+*direction;
				return *direction;
			}
		}
	}
}

int transform(Input *in,int size,int curTime,int floor,
	/*as result returned*/int keySitu[][9],int *drt)
{


	int i,j/*counters*/,ifEmpty=0/*0 for empty*/;

	for(i=1;i<=size;i++) if(!in[i].is_done && in[i].time<=curTime)
	{
		int is_finished=0/*0 for unfinished*/,ifFirst=1/*1 for first*/;
		for(j=0;j<27;j++) if(stdSML[j]==in[i].order)
		{	
			if (!(j%9==floor && curTime-1==in[i].time))
			{	keySitu[j/9][j%9]=1; is_finished=1;ifEmpty=1; }
			if(ifFirst)
				if(j%9>floor)		{ *drt=1;  ifFirst=0; }
				else if(j%9<floor)  { *drt=-1; ifFirst=0; }
				break;
		}
		if(!is_finished) for(j=0;j<27;j++) if(stdCPT[j]==in[i].order)
		{	
			if (!(j%9==floor && curTime-1==in[i].time))
			{	keySitu[j/9][j%9]=1;ifEmpty=1;} 
			if(ifFirst)
				if(j%9>floor)		{ *drt=1;  ifFirst=0; }
				else if(j%9<floor)  { *drt=-1; ifFirst=0; }
				break;
		}
	}
	return ifEmpty;/*0 for empty, 1 for not empty*/
}

int newDirection(int keySitu[][9],int floor,int *direction,int drt)
{
	int i;/*counter*/

	if(*direction==-2) *direction=drt;
	for(i=floor+*direction;i>=0 && i<9;i+=*direction)
		if(keySitu[1][i] || keySitu[0][i] || keySitu[2][i])
			return 0;
	for(i=floor-*direction;i>=0 && i<9;i-=*direction)
		if(keySitu[1][i] || keySitu[0][i] || keySitu[2][i])
		{ *direction*=-1; return 0; }
	if(keySitu[1+*direction][floor]==1){}
	else if(keySitu[1-*direction][floor]==1) *direction*=-1;
	return 0;//finish successfully
}

int killOrder(Input in[],int direction, int floor,int size)
{
	int i;
	
	for(i=1;i<=size;i++){
		if(in[i].order==stdSML[(direction+1)*9+floor] || in[i].order==stdCPT[(direction+1)*9+floor])
			in[i].is_done=1;//done
		if(in[i].order==stdSML[9+floor] || in[i].order==stdCPT[9+floor])
			in[i].is_done=1;
	}
	return 1;//finish successfully
}