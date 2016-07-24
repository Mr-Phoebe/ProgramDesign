#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <climits>
#include <complex>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <bitset>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <ctime>
#include <set>
#include <map>
#include <cmath>
#define eps 1e-9
#define ll long long

using namespace std;


template<class T>
inline bool read(T &n)
{
    T x = 0, tmp = 1;
    char c = getchar();
    while((c < '0' || c > '9') && c != '-' && c != EOF) c = getchar();
    if(c == EOF) return false;
    if(c == '-') c = getchar(), tmp = -1;
    while(c >= '0' && c <= '9') x *= 10, x += (c - '0'),c = getchar();
    n = x*tmp;
    return true;
}

//-----------------------------------------------------------------------

const int MAXN=2014;

int chess[16][16],tot=0;
int FF,SS;

struct win_kind
{
    bool ok;                //  初始化为false，有些点下了往后就是不会赢
    int x[6],y[6];          //  神奇的落子地点
    bool is_used[5];        //  胜利的五个神奇的点，初始化为false
} first[MAXN],second[MAXN]; //  把棋盘展开成为直线，笑尿人工计算的策略

int panfen[16][16] =
{
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
    { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
    { 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },
    { 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },
    { 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },
    { 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0 },
    { 1, 2, 3, 4, 5, 6, 7, 7, 7, 6, 5, 4, 3, 2, 1, 0 },
    { 1, 2, 3, 4, 5, 6, 7, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
    { 1, 2, 3, 4, 5, 6, 7, 7, 7, 6, 5, 4, 3, 2, 1, 0 },
    { 1, 2, 3, 4, 5, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0 },
    { 1, 2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 4, 3, 2, 1, 0 },
    { 1, 2, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 2, 1, 0 },
    { 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 0 },
    { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};
int com[16][16];

inline bool in(int x,int y)
{
    return x>=0 && x<15 && y>=0 && y<15;
}

void init()
{
    tot=0;
    for(int i=0;i<15;i++)
        for(int j=0;j<=10;j++)  // 从i,j落子，横五个
        {
            if(chess[i][j]==FF)
            {
                first[tot+11*i+j].ok=true;
                second[tot+11*i+j].ok=false;
            }
            else if(chess[i][j]==SS)
            {
                first[tot+11*i+j].ok=false;
                second[tot+11*i+j].ok=true;
            }
            for(int k=0; k<5; k++)
            {
                first[tot+11*i+j].is_used[k]=false;
                first[tot+11*i+j].x[k]=i;
                first[tot+11*i+j].y[k]=j+k;
                second[tot+11*i+j].is_used[k]=false;
                second[tot+11*i+j].x[k]=i;
                second[tot+11*i+j].y[k]=j+k;
            }
        }
    tot+=165;  //共计165个可能落子点

    for(int i=0;i<=10;i++)  //  竖五个
        for(int j=0;j<15;j++)
        {
            if(chess[i][j]==FF)
            {
                first[tot+15*i+j].ok=true;
                second[tot+15*i+j].ok=false;
            }
            else if(chess[i][j]==SS)
            {
                first[tot+15*i+j].ok=false;
                second[tot+15*i+j].ok=true;
            }
            for(int k=0;k<5;k++)
            {
                first[tot+15*i+j].is_used[k]=false;
                first[tot+15*i+j].x[k]=i+k;
                first[tot+15*i+j].y[k]=j;
                second[tot+15*i+j].is_used[k]=false;
                second[tot+15*i+j].x[k]=i+k;
                second[tot+15*i+j].y[k]=j;
            }
        }
    tot+=165;

    for(int i=0;i<=10;i++)     //向右下斜↘
        for(int j=0;j<=10;j++)
        {
            if(chess[i][j]==FF)
            {
                first[tot+11*i+j].ok=true;
                second[tot+11*i+j].ok=false;
            }
            else if(chess[i][j]==SS)
            {
                first[tot+11*i+j].ok=false;
                second[tot+11*i+j].ok=true;
            }
            for(int k=0; k<5; k++)
            {
                first[tot+11*i+j].is_used[k]=false;
                first[tot+11*i+j].x[k]=i+k;
                first[tot+11*i+j].y[k]=j+k;
                second[tot+11*i+j].is_used[k]=false;
                second[tot+11*i+j].x[k]=i+k;
                second[tot+11*i+j].y[k]=j+k;
            }
        }
    tot+=121;

    for(int i=4;i<15;i++)       //向右上斜↗
        for(int j=0;j<=10;j++)
        {
            if(chess[i][j]==FF)
            {
                first[tot+11*(i-4)+j].ok=true;
                second[tot+11*(i-4)+j].ok=false;
            }
            else if(chess[i][j]==SS)
            {
                first[tot+11*(i-4)+j].ok=false;
                second[tot+11*(i-4)+j].ok=true;
            }
            for(int k=0;k<5;k++)
            {
                first[tot+11*(i-4)+j].is_used[k]=false;
                first[tot+11*(i-4)+j].x[k]=i-k;
                first[tot+11*(i-4)+j].y[k]=j+k;
                second[tot+11*(i-4)+j].is_used[k]=false;
                second[tot+11*(i-4)+j].x[k]=i-k;
                second[tot+11*(i-4)+j].y[k]=j+k;
            }
        }
    tot+=121;

    for(int i=0; i<tot; i++)
        second[i]=first[i];   //说好的人和电脑的输赢应该是一样的呢？
}

void judgehelp(int x,int y,int w)
{
    int score=1;
    if(w==FF)
    {
        for(int i=0;i<tot;i++)
        {
            score=1;
            if(first[i].ok==false)
                continue;
            for(int j=0;j<5;j++)
            {
                if(first[i].x[j]==x && first[i].y[j]==y)
                {
                    int k=j-1;
                    while(k>=0 && first[i].is_used[k]==true)
                    {
                        k--;
                        score+=10;
                    }
                    k=j+1;
                    while(k<5 && first[i].is_used[k]==true)
                    {
                        k++;
                        score+=10;
                    }
                    break;
                }
            }
            com[x][y]+=score;
        }
    }
    else
    {
        for(int i=0;i<tot;i++)
        {
            score=1;
            if(second[i].ok==false)
                continue;
            for(int j=0;j<5;j++)
            {
                if (second[i].x[j]==x && second[i].y[j]==y)
                {
                    int k=j-1;
                    while(k>=0 && second[i].is_used[k]==true)
                    {
                        k--;
                        score+=4;
                    }
                    k=j+1;
                    while(k<5 && second[i].is_used[k]==true)
                    {
                        k++;
                        score+=4;
                    }
                    break;
                }
            }
            com[x][y]+=score;
        }
    }
}

/*
bool over(int x,int y,int w)
{
    int score;
    if(w==FF)
    {
        for(int i=0;i<tot;i++)
        {
            score=1;
            if(first[i].ok==false)
                continue;
            for(int j=0;j<5;j++)
            {
                if(first[i].x[j]==x && first[i].y[j]==y)
                {
                    int k=j-1;
                    while(k>=0 && first[i].is_used[k]==true)
                    {
                        k--;
                        score++;
                    }
                    k=j+1;
                    while(k<5 && first[i].is_used[k]==true)
                    {
                        k++;
                        score++;
                    }
                    if(score==5)
                        return true;  //赢了
                    break;      // 找到了某些点，但是没有赢
                }
            }
        }
    }
    else
    {
        for(int i=0;i<tot;i++)
        {
            score=1;
            if(second[i].ok==false)
                continue;
            for(int j=0;j<5;j++)
            {
                if(second[i].x[j]==x && second[i].y[j]==y)
                {
                    int k=j-1;
                    while(k>=0 && second[i].is_used[k]==true)
                    {
                        k--;
                        score++;
                    }
                    k=j+1;
                    while(k<5 && second[i].is_used[k]==true)
                    {
                        k++;
                        score++;
                    }
                    if(score==5)
                        return true;
                    break;
                }
            }
        }
    }
    return false;       //整个棋盘扫过没有赢

    ?????写完才发现.....是不是平台就可以自己判断了？
}
*/

void judge()                                   //判断落子,传入当下要下者
{
    int lianzi1=0,lianzi2=0,life=0,d=0;
    for(int i=0;i<16;i++)
        for(int j=0;j<16;j++)
            com[i][j]=panfen[i][j];
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++)
        {
            int lianul=0,lianu=0,lianur=0,lianl=0;
            int duishou1=0,duishou2=0;
            if(chess[i][j]==0)
            {
                judgehelp(i,j,SS);
                judgehelp(i,j,FF);
                for(int m=-1; m<=1; m++)
                    for(int n=-1; n<=1; n++)
                    {
                        if(m!=0 || n!=0)    //  八个方向，正向搜4个点，到了空位则退出
                        {
                            for(int k=1;k<5;k++)
                            {
                                if( in(i+k*m,j+k*n) && chess[i+k*m][j+k*n]==SS )    //对手
                                    lianzi1++;
                                else if(chess[i+k*m][j+k*n]==0)
                                {
                                    life++;
                                    break;
                                }
                                else
                                    break;
                            }
                            for(int k=-1;k>-5;k--)   //反向搜4个点，到了空位则退出
                            {
                                if( in(i+k*m,j+k*n) && chess[i+k*m][j+k*n]==SS )
                                    lianzi1++;
                                else if( in(i+k*m,j+k*n) && chess[i+k*m][j+k*n]==0)
                                {
                                    life++;
                                    break;
                                }
                                else
                                    break;
                            }
                            if(lianzi1==1)
                                com[i][j]+=2;
                            else if(lianzi1==2)
                            {
                                if(life==1)
                                    com[i][j]+=10;
                                else if(life==2)
                                    com[i][j]+=15;
                            }
                            else if(lianzi1==3)
                            {
                                if(life==1)
                                    com[i][j]+=20;
                                else if(life==2)
                                    com[i][j]+=1200;
                            }
                            else if(lianzi1==4)
                            {
                                com[i][j]+=7000;
                            }
                            else if(lianzi1>=5)
                            {
                                com[i][j]+=100000;
                            }
                            life=0;
                            for(int k=1;k<5;k++)
                            {
                                if( in(i+k*m,j+k*n) && chess[i+k*m][j+k*n]==FF )
                                    lianzi2++;
                                else if( in(i+k*m,j+k*n) && chess[i+k*m][i+k*n]==0)
                                {
                                    k++;
                                    if( in(i+k*m,j+k*n) && chess[i+k*m][j+k*n]==SS)
                                        duishou1++;
                                    life++;
                                    break;
                                }
                                else
                                {
                                    duishou1++;
                                    break;
                                }
                            }
                            for(int k=-1;k>-5;k--)
                            {
                                if( in(i+k*m,j+k*n) && chess[i+k*m][j+k*n]==FF )
                                    lianzi2++;
                                else if( in(i+k*m,j+k*n) && chess[i+k*m][j+k*n]==0)
                                {
                                    k--;
                                    if( in(i+k*m,j+k*n) && chess[i+k*m][j+k*n]==SS)
                                        duishou2++;
                                    life++;
                                    break;
                                }
                                else
                                {
                                    duishou2++;
                                    break;
                                }
                            }
                            if(i<=1||i>=14||j<=1||j>=14)
                                com[i][j]-=200;
                            if(lianzi2==1)
                            {
                                com[i][j]+=4;
                                if(lianzi1==1)
                                    com[i][j]+=10;
                                if(lianzi1>=3)
                                    com[i][j]+=200;
                                if(lianul||lianu||lianur||lianl)
                                    com[i][j]+=5;
                                if(duishou1||duishou1)
                                    com[i][j]-=2;
                            }
                            else if(lianzi2==2)
                            {
                                if(life==1)
                                    com[i][j]+=20;
                                else if(life==2)
                                    com[i][j]+=40;
                                if(duishou1||duishou1)
                                    com[i][j]-=15;
                                if(lianzi1==2)
                                    com[i][j]+=10000;
                                if(lianul==3||lianu==3||lianur==3||lianl==3)
                                    com[i][j]+=250;
                            }
                            else if(lianzi2==3)
                            {
                                if(life==1)
                                    com[i][j]+=250;
                                else if(life==2)
                                    com[i][j]+=1300;
                                if(duishou2||duishou1)
                                    com[i][j]-=200;
                                if(!duishou2&&!duishou1&&lianzi1==1)
                                    com[i][j]+=10000;
                                if(!duishou2&&!duishou1&&lianul>=3||lianu>=3||lianur>=3||lianl>=3)
                                    com[i][j]+=500;
                            }
                            else if(lianzi2==4)
                            {
                                com[i][j]+=10000;
                                if(duishou2||duishou1)
                                    com[i][j]-=500;
                                if(!duishou2&&!duishou1&&lianzi1>=1)
                                    com[i][j]+=10000;
                                if(!duishou2&&!duishou1&&(lianul>=3||lianu>=3||lianur>=3||lianl>=3))
                                    com[i][j]+=2500;
                            }
                            //判断双三等等
                            if(m==-1&&n==-1)
                            {
                                lianul=max(lianzi1,lianzi2);
                            }
                            else if(m==-1&&n==0)
                            {
                                lianu=max(lianzi1,lianzi2);
                            }
                            else if(m==-1&&n==1)
                            {
                                lianur=max(lianzi1,lianzi2);
                            }
                            else if(m==0)
                            {
                                lianl=max(lianzi1,lianzi2);
                            }
                            lianzi1=0;
                            lianzi2=0;
                            life=0;
                        }
                    }
            }
        }
}


void find()           //这是电脑落子的函数
{
    int maxn=-1;
    int c,d;
    judge();
    for(int i=0;i<15;i++)
        for(int j=0;j<15;j++)
        {
            if(com[i][j]>maxn)
            {
                maxn=com[i][j];
                c=i;
                d=j;
            }
        }
    printf("%d %d\n",c,d);
}

int main(int arg, char* args[])
{
    int sum=0;
    char ch;
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            ch=args[i+1][j];
            chess[i][j]=ch-'0';
            if(chess[i][j])
                sum++;
        }
    }
    init();
    if(sum&1)   //奇数为second
    {
        FF=2;SS=1;
    }
    else
    {
        FF=1;SS=2;
    }
    find();
    return 0;
}
