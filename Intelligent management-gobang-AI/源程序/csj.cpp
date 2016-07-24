#include <iostream>
#include <cstring>
#include <cstdlib>
#include<cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
#define INF 1000000000
#define eps 1e-6
using namespace std;

const int MAX_N=20;
const int N=15;

int cb[MAX_N][MAX_N];
char cc[MAX_N];
int cnt1;
int cnt2;
int admin,another;
int n1,n2;
bool flag;
int state[MAX_N][MAX_N];

void input(char* args[])
{
    cnt1=0;
    cnt2=0;
    memset(cb,0,sizeof(cb));
//    for(int i=1;i<=15;i++){
//        scanf("%s",cc);
//        for(int j=1;j<=15;j++){
//            cb[i][j]=cc[j-1]-'0';
//            if(cb[i][j]==1) cnt1++;
//            else if(cb[i][j]==2)cnt2++;
//        }
//    }
    for(int i=1; i<=15; i++)
    {
        for(int j=1; j<=15; j++)
        {
            cb[i][j]=args[i][j-1]-'0';
            if(cb[i][j]==1) cnt1++;
            else if(cb[i][j]==2)cnt2++;
        }
    }
    if(cnt1==cnt2)
    {
        admin=1;
        another=2;
    }
    else
    {
        admin=2;
        another=1;
    }
}
int p_score(int num,int gg[])
{
    int mid=0;
    if(num>=4) mid+=10000000;  //成5
    else if (num == 3)
    {
        if (!(gg[1]&gg[0])) mid += 500000;
        else if (!(gg[1]|gg[0])) mid += 10000;
        else mid += 0;
    }
    else if(num==2)
    {
        if(gg[1]==1&&gg[0]==1) mid += 0;
        else if(gg[1]==0&&gg[0]==0) mid += 9000;
        else mid += 2000;
    }
    else if(num==1)
    {
        if(gg[0]==0&&gg[1]==0) mid+=200;
        else if(gg[0]==1&&gg[1]==1) mid+=0;
        else mid+=100;
    }
    else if(num==0)
    {
        if(gg[0]==0&&gg[1]==0) mid+=90;
        else if(gg[0]==1&&gg[1]==1) mid+=0;
        else mid+=10;
    }
    return mid;
}
void g_score(int x,int y,int who,int ano)
{
    int gg[2],k,num,mid;
    mid=0;
    //横向比较
    gg[0]=gg[1]=1;
    num=0;
    //右比较
    for(int k=1; k<=N-y; k++)
    {
        if(cb[x][y+k]==who)
        {
            num++;
            continue;
        }
        if(cb[x][y+k]==0)
        {
            gg[1]=0;
            break;
        }
        if(cb[x][y+k]==ano)
        {
            gg[1]=1;
            break;
        }
    }
    //左比较
    for(int k=1; k<y; k++)
    {
        if(cb[x][y-k]==who)
        {
            num++;
            continue;
        }
        if(cb[x][y-k]==0)
        {
            gg[0]=0;
            break;
        }
        if(cb[x][y-k]==ano)
        {
            gg[0]=1;
            break;
        }
    }
    mid+=p_score(num,gg);

    //纵向
    gg[0]=gg[1]=1;
    num=0;
    //向下
    for(int k=1; k<=N-x; k++)
    {
        if(cb[x+k][y]==who)
        {
            num++;
            continue;
        }
        if(cb[x+k][y]==0)
        {
            gg[1]=0;
            break;
        }
        if(cb[x+k][y]==ano)
        {
            gg[1]=1;
            break;
        }
    }
    //向上
    for(int k=1; k<x; k++)
    {
        if(cb[x-k][y]==who)
        {
            num++;
            continue;
        }
        if(cb[x-k][y]==0)
        {
            gg[0]=0;
            break;
        }
        if(cb[x-k][y]==ano)
        {
            gg[0]=1;
            break;
        }
    }
    mid+=p_score(num,gg);

    //左上到右下
    gg[0]=gg[1]=1;
    num=0;
    //右下
    for(int k=1; k<=min(N-x,N-y); k++)
    {
        if(cb[x+k][y+k]==who)
        {
            num++;
            continue;
        }
        if(cb[x+k][y+k]==0)
        {
            gg[1]=0;
            break;
        }
        if(cb[x+k][y+k]==ano)
        {
            gg[1]=1;
            break;
        }
    }
    //左上
    for(int k=1; k<min(x,y); k++)
    {
        if(cb[x-k][y-k]==who)
        {
            num++;
            continue;
        }
        if(cb[x-k][y-k]==0)
        {
            gg[0]=0;
            break;
        }
        if(cb[x-k][y-k]==ano)
        {
            gg[0]=1;
            break;
        }
    }
    mid+=p_score(num,gg);

    //左下到右上
    gg[0]=gg[1]=1;
    num=0;
    //左下
    for(int k=1; k<=min(N-x,y); k++)
    {
        if(cb[x+k][y-k]==who)
        {
            num++;
            continue;
        }
        if(cb[x+k][y-k]==0)
        {
            gg[1]=0;
            break;
        }
        if(cb[x+k][y-k]==ano)
        {
            gg[1]=1;
            break;
        }
    }
    //右上
    for(int k=1; k<min(x,N-y); k++)
    {
        if(cb[x-k][y+k]==who)
        {
            num++;
            continue;
        }
        if(cb[x-k][y+k]==0)
        {
            gg[0]=0;
            break;
        }
        if(cb[x-k][y+k]==ano)
        {
            gg[0]=1;
            break;
        }
    }
    mid+=p_score(num,gg);
    if (admin == 1 && who != admin) mid = mid * 2;
    if (admin == 2 && who != admin) mid = mid * 10;
    if(mid>state[x][y]) state[x][y]=mid;
}
void judge()
{
    if(cnt1==cnt2&&cnt1==0)
    {
        printf("8 8\n");
        return ;
    }
    int res=-INF;
    int midx,midy;
    memset(state,0,sizeof(state));
    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=N; j++)
        {
            if(!cb[i][j])
            {
                //printf("i=%d j=%d\n", i, j);
                g_score(i,j,admin,another);
                g_score(i,j,another,admin);
            }
        }
    }
    for(int i=1; i<=N; i++)
    {
        for(int j=1; j<=N; j++)
        {
            if(!cb[i][j])
            {
                if(state[i][j]>res)
                {
                    midx=i;
                    midy=j;
                    res=state[i][j];
                }
            }
        }
    }
    printf("%d %d\n",midx-1,midy-1);
}
int main(int arg, char* args[])
{
    input(args);
    judge();
    return 0;
}
