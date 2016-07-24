#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;
char board[20][20];//存棋盘
int dx[10]={0,0,-1,1,-1,1,-1,1},dy[10]={1,-1,0,0,-1,1,1,-1};//上，下，左，右，左上，右下，左下，右上
struct node
{
    int px,py,rprice;
}p[5];
int price(int j,int yes)
{
    if(j>=5)
        return 1000000;
    if(j==4&&yes==2)
        return 100000;
    if(j==3&&yes==2)
        return 15000;
    if(j==4&&yes==1)
        return 10000;
    if(j==3&&yes==1)
        return 1000;
    if(j==2&&yes==2)
        return 100;
    if(j==2&&yes==1)
        return 10;
    if(yes==1)
        return 1;
    else
        return 0;
}
char my_color;//己方棋子的颜色
void judge(char color,int x,int y)
{
    int pr=0;
    for(int i=0;i<8;i+=2)
    {
        int yes,yes1=0,yes2=0,j=1,nx=x+dx[i],ny=y+dy[i];
        while(nx>=1&&nx<=15&&ny>=1&&ny<=15&&color==board[nx][ny])
        {
            j++;
            nx+=dx[i];
            ny+=dy[i];
        }
        while(yes1<=4&&nx>=1&&nx<=15&&ny>=1&&ny<=15&&board[nx][ny]=='0')
        {
            yes1++;
        }
        nx=x+dx[i+1];ny=y+dy[i+1];
        while(nx>=1&&nx<=15&&ny>=1&&ny<=15&&color==board[nx][ny])
        {
            j++;
            nx+=dx[i+1];
            ny+=dy[i+1];
        }
        while(yes2<=4&&nx>=1&&nx<=15&&ny>=1&&ny<=15&&board[nx][ny]=='0')
        {
            yes2++;
        }
        if(j>=5)
            yes=0;
        else if(j==4)
        {
            if(yes1&&yes2)
                yes=2;
            else if(yes1||yes2)
                yes=1;
            else
                yes=0;
        }
        else if(j==3)
        {
            if(yes1&&yes2&&yes1+yes2>=3)
                yes=2;
            else if(yes1+yes2==2)
                yes=1;
            else
                yes=0;
        }
        else if(j==2)
        {
            if(yes1&&yes2&&yes1+yes2>=4)
                yes=2;
            else if(yes1+yes2==3)
                yes=1;
            else
                yes=0;
        }
        pr+=price(j,yes);
    }
    if(pr>p[color-'0'].rprice)
    {
        p[color-'0'].rprice=pr;
        p[color-'0'].px=x;
        p[color-'0'].py=y;
    }
}
int main()
{
    int i,j,cnt[3]={0},maxx=0,maxy=0,minx=20,miny=20;
    p[1].rprice=-1;
    p[2].rprice=-1;
    for(i=1;i<=15;i++)
    {
        scanf("%s",board[i]+1);
        for(j=1;j<=15;j++)
        {
            if(board[i][j]!='0')
            {
                cnt[board[i][j]-'0']++;
                maxx=max(maxx,i);
                minx=min(minx,i);
                maxy=max(maxy,j);
                miny=min(miny,j);
            }
        }
    }
    if(cnt[1]==cnt[2])
        my_color='1';
    else
        my_color='2';
    if(cnt[1]==0)
        printf("8 8\n");
    else if(cnt[2]==0)
    {
        if(board[8][8]=='0')
            printf("8 8\n");
        else
            printf("8 7\n");
    }
    else
    {
        for(i=minx-3;i<=maxx+3;i++)
        {
            for(j=miny-3;j<=maxy+3;j++)
            {
                if(i>=1&&i<=15&&j>=1&&j<=15&&board[i][j]=='0')
                {
                    judge('1',i,j);
                    judge('2',i,j);
                }
            }
        }
        if(p[my_color-'0'].rprice>=1000000)
            printf("%d %d\n",p[my_color-'0'].px,p[my_color-'0'].py);
        else if(p[3-my_color+'0'].rprice>=1000000)
            printf("%d %d\n",p[3-my_color+'0'].px,p[3-my_color+'0'].py);
        else if(p[my_color-'0'].rprice>=100000)
            printf("%d %d\n",p[my_color-'0'].px,p[my_color-'0'].py);
        else if(p[3-my_color+'0'].rprice>=100000)
            printf("%d %d\n",p[3-my_color+'0'].px,p[3-my_color+'0'].py);
        else if(p[my_color-'0'].rprice>=20000)
            printf("%d %d\n",p[my_color-'0'].px,p[my_color-'0'].py);
        else if(p[3-my_color+'0'].rprice>=20000)
            printf("%d %d\n",p[3-my_color+'0'].px,p[3-my_color+'0'].py);
        else if(p[my_color-'0'].rprice>=10000)
            printf("%d %d\n",p[my_color-'0'].px,p[my_color-'0'].py);
        else if(p[3-my_color+'0'].rprice>=10000)
            printf("%d %d\n",p[3-my_color+'0'].px,p[3-my_color+'0'].py);
        else if(p[my_color-'0'].rprice>=p[3+'0'-my_color].rprice)
            printf("%d %d\n",p[my_color-'0'].px,p[my_color-'0'].py);
        else
            printf("%d %d\n",p[3-my_color+'0'].px,p[3-my_color+'0'].py);
    }
    return 0;
}
