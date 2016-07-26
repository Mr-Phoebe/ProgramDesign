#include "cmc.h"
#include<stdlib.h>
#include<time.h>

extern char stdCPT[];
extern char stdSML[];//商汝麒童鞋在顺便服务里面的常量

int hongfu(int out[],int T,
				int *direction/*-2 for vacant
								0 for pause
								-1,1 respectively for downward and upward*/,
				Input in[],
				int in_size,
				int *ifB)
{
	int keySitu[3][9]={0}/*to save situation of keys
							[1][]for internal,[2][]for external up,[0][]for external down,[][n]for n+1 floor
							1 for selected, 0 for not*/,
		floor=out[T]-1,
		drt=-2/*direction prepared*//*-2 for vacant*/;

	int transform_hongfu(Input*,int,int,int,int[][9],int*,int*);
	int newDirection(int[][9],int,int*,int);
	int killOrder(Input in[],int direction, int floor,int size);

	//hongfu need random
	srand(time(NULL));

	//hongfu
	if(!floor) *ifB=0;
	if(!transform_hongfu(in,in_size,T,floor,keySitu,&drt,ifB) && *ifB!=1)/*empty*/{
		*direction=-2;
		out[T+1]=100*out[T];
		return -2;
	}
	else /*not empty*/
	{
		newDirection(keySitu,floor,&*direction,drt);
		if(*ifB==1) 
		{
			*direction=-1;
			out[T+1]=out[T]-1;
			return 0;
		}
		if(keySitu[1][floor] ||
			(keySitu[0][floor] && *direction==-1) || 
			(keySitu[2][floor] && *direction==1))//need to pause
		{
			out[T+1]=out[T];
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
				out[T+1]=out[T];
				return *direction;//return -2 for didn't move
			}
			else{//direction != -2, is to move
				out[T+1]=out[T]+*direction;

				//Hongfu's fall
				if(out[T]==2 || out[T]==3)
				{
					int see;
					see=rand()%4;
					if(!see)
					{	*ifB=-1; out[T+1]=1; *direction=-3; }
				}

				return *direction;
			}
		}
	}
}

int transform_hongfu(Input *in,int size,int curT,int floor,
	/*as result returned*/int keySitu[][9],int *drt,int *ifB)
{
	int i,j/*counters*/,ifEmpty=0/*0 for empty*/;

	for(i=1;i<=size;i++) if(!in[i].is_done && in[i].time<=curT)
	{
		int is_finished=0/*0 for unfinished*/,ifFirst=1/*1 for first*/;

		//hongfu key of bamen
		if(in[i].order=='b' || in[i].order=='B')
		{	
			*ifB=1; 
			is_finished=1; 
			for(j=0;j<27;j++) keySitu[j/9][j%9]=0;
			for(j=1;j<=size;j++) in[j].is_done=1;
			return 1;
		}
		else for(j=0;j<27;j++) if(stdSML[j]==in[i].order)
		{	
			//hongfu 2 to 5 floor is banned
			if(j%9>0 && j%9<5)
			{	in[i].is_done=1; is_finished=1; }
			else if (!(j%9==floor && curT-1==in[i].time))
			{	keySitu[j/9][j%9]=1; is_finished=1;ifEmpty=1; }
			if(ifFirst)
				if(j%9>floor)		{ *drt=1;  ifFirst=0; }
				else if(j%9<floor)  { *drt=-1; ifFirst=0; }
				break;
		}
		if(!is_finished) for(j=0;j<27;j++) if(stdCPT[j]==in[i].order)
		{	
			//hongfu 2 to 5 floor is banned
			if(j%9>0 && j%9<5) in[i].is_done=1;
			else if (!(j%9==floor && curT-1==in[i].time))
			{	keySitu[j/9][j%9]=1;ifEmpty=1;} 
			if(ifFirst)
				if(j%9>floor)		{ *drt=1;  ifFirst=0; }
				else if(j%9<floor)  { *drt=-1; ifFirst=0; }
				break;
		}
	}
	return ifEmpty;/*0 for empty, 1 for not empty*/
}