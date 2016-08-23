//
//  词法分析.cpp
//  Main
//  Created by 吴浩男 on 15/10/30.
//  Copyright © 2015年 吴浩男. All rights reserved.
//  Mr.Phoebe的专栏 http://blog.csdn.net/u013007900
#include<bits/stdc++.h>
using namespace std;

set<string> S[8+5];

vector<pair<int,int> > error;

void output(int type,string &buffer)//将buffer的[0..len-2]推入S[type]这个集合里
{
    int Size=buffer.size();
    S[type].insert(buffer.substr(0,Size-1));
    buffer.clear();
}

int main()
{
	freopen("data.txt","r",stdin);
    string line;
    int row=0,col=0;
    for(int i=0; i<8; i++)S[i].clear(); //对应的每个符号的单词数组
    int state=0;
    string buffer;
    while(getline(cin,line))
    {
        line+='\n';
        row++;
        col=0;
        if(state!=10)state=0;

        for(int i=0; i<line.size(); i++)
        {
            col++;
            buffer+=line[i];
            if(state==0)
            {
                if(isalpha(line[i]))state=1;
                else if(isdigit(line[i]))state=2;
                else if(line[i]=='<'||line[i]=='>'||line[i]=='='||line[i]=='!')state=8;
                else if(line[i]=='/')state=9;
                else if(line[i]=='+'||line[i]=='-'||line[i]=='*'||line[i]=='('||line[i]==')'||line[i]==';'||line[i]=='\'')state=13;
                else if(line[i]!='\n')
                {
                    error.push_back(make_pair(row,col));
                    state=0;
                    buffer.clear();
                }
                continue;
            }
            if(state==1)
            {
                if(isalpha(line[i])||isdigit(line[i]))state=1;
                else
                {
                    output(0,buffer);
                    state=0;
                    i--;
                    col--;
                }
                continue;
            }
            if(state==2)
            {
                if(isdigit(line[i]))state=2;
                else if(line[i]=='.')state=3;
                else if(line[i]=='E')state=5;
                else
                {
                    output(1,buffer);
                    state=0;
                    i--;
                    col--;
                }
                continue;
            }
            if(state==3)
            {
                if(isdigit(line[i]))state=4;
                else
                {
                    error.push_back(make_pair(row,col));
                    state=0;
                    buffer.clear();
                }
                continue;
            }
            if(state==4)
            {
                if(isdigit(line[i]))state=4;
                else
                {
                    output(1,buffer);
                    state=0;
                    i--;
                    col--;
                }
                continue;
            }
            if(state==5)
            {
                if(isdigit(line[i]))state=7;
                else if(line[i]=='+'||line[i]=='-')state=6;
                else
                {
                    error.push_back(make_pair(row,col));
                    state=0;
                    buffer.clear();
                }
                continue;
            }
            if(state==6)
            {
                if(isdigit(line[i]))state=7;
                else
                {
                    error.push_back(make_pair(row,col));
                    state=0;
                    buffer.clear();
                }
                continue;
            }
            if(state==7)
            {
                if(isdigit(line[i]))state=7;
                else
                {
                    output(1,buffer);
                    state=0;
                    i--;
                    col--;
                }
                continue;
            }
            if(state==8)
            {
                if(line[i]=='=')state=14;
                else
                {
                    if(buffer[0]=='<'||buffer[0]=='>')  output(2,buffer);
                    else    output(5,buffer);
                    state=0;
                    i--;
                    col--;
                }
                continue;
            }
            if(state==9)
            {
                if(line[i]=='*')state=10;
                else
                {
                    output(3,buffer);
                    state=0;
                    i--;
                    col--;
                }
                continue;
            }
            if(state==10)
            {
                if(line[i]=='*')    state=11;
                else state=10;
                continue;
            }
            if(state==11)
            {
                if(line[i]=='/')    state=12;
                else state=10;
                continue;
            }
            if(state==12)
            {
                output(4,buffer);
                state=0;
                i--;
                col--;
                continue;
            }
            if(state==13)
            {
                output(3,buffer);
                state=0;
                i--;
                col--;
                continue;
            }
            if(state==14)
            {
                output(2,buffer);
                state=0;
                i--;
                col--;
                continue;
            }
        }
    }
    printf("标识符:\n");
    for(set<string>::iterator it=S[0].begin(); it!=S[0].end(); it++)
        cout<<(*it)<<' ';
    cout<<endl;
    printf("无符号数：\n");
    for(set<string>::iterator it=S[1].begin(); it!=S[1].end(); it++)
        cout<<(*it)<<' ';
    cout<<endl;
    printf("关系运算符:\n");
    for(set<string>::iterator it=S[2].begin(); it!=S[2].end(); it++)
        cout<<(*it)<<' ';
    cout<<endl;
    printf("赋值号:\n");
    for(set<string>::iterator it=S[5].begin(); it!=S[5].end(); it++)
        cout<<(*it)<<' ';
    cout<<endl;
    printf("注释：\n");
    for(set<string>::iterator it=S[4].begin(); it!=S[4].end(); it++)
        cout<<(*it)<<' ';
    cout<<endl;
    return 0;
}
