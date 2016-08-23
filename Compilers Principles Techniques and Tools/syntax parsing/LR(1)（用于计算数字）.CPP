#include<iostream>
#include<stack>
#include<queue>
#include<fstream>
#include<cstring>
#include<cstdlib>
using namespace std;
string AnalyzeChart[16][11]=
{//LR文法的分析表
	"s5",     "e1",    "e1",      "s4",     "e2",     "e1",     "1",     "2",     "3",      "e1",   "e1",
		"e3",     "s6",    "e1",      "e3",     "e2",     "acc",    "error", "error", "error",  "s7",   "e1",
		"e6",     "r2",    "s8",      "e6",     "r2",     "r2",     "error", "error", "error",  "r2",   "s9",
		"e6",     "r4",    "r4",      "e6",     "r4",     "r4",     "error", "error", "error",  "r4",   "r4",
		"s5",     "e1",    "e1",      "s4",     "e2",     "e1",     "10",     "2",     "3",      "e1",    "e1",
		"e5",     "r6",    "r6",      "e3",     "r6",     "r6",     "error", "error", "error",  "r6",    "r6",
		"s5",     "e1",    "e1",      "s4",     "e2",     "e1",     "error", "11",     "3",      "e1",    "e1",
		"s5",     "e1",    "e1",      "s4",     "e2",     "e1",     "error", "12",    "3",      "e1",    "e1",
		"s5",     "e1",    "e1",      "s4",     "e2",     "e1",     "error", "error", "13",     "e1",    "e1",
		"s5",     "e1",    "e1",      "s4",     "e1",     "e1",     "error", "error", "14",     "e1",    "e1",
		"e3",     "s6",    "e1",      "e3",     "s15",     "r3",     "error", "error", "error",  "s9",    "e1",
		"e6",     "r1",    "s8",      "e6",     "r1",     "r1",     "error", "error", "error",  "r1",    "s9",
		"e6",     "r7",    "s8",      "e6",     "r7",     "r7",     "error", "error", "error",  "r7",    "s9",
		"e6",     "r3",    "r3",      "e6",     "r3",     "r3",     "error", "error", "error",  "r3",    "r3",
		"e6",     "r8",    "r8",      "e6",     "r8",     "r8",     "error", "error", "error",  "r8",    "r8",
		"e6",     "r5",    "r5",      "e6",     "r5",     "r5",     "error", "error", "error",  "r5",    "r5",

};
stack<float> digit;
queue<float> digit1;
queue<int> inputid;
char *FinalSymbol[6]=
{
    "i","+","*","(",")","#"//终结符
};
char *UnfinalSymbol[5]=
{
	"E","E'","T","T'","F"//非终结符
};
stack<char> ufstack;//状态栈
void initialize()
{
	ufstack.push('0');
	inputid.push(0);

}
char * keyword[6] = {"for","if","then","else","while","do"};
int flag1=-1,flag2=-1;
struct sign
{
	int line;
	int token;
	char temp[10];
	int i;
};

void reset(sign & s)
{
	s.i = 0;
	memset(s.temp,'$',10);
	s.token = -1;
}

bool is_key_word(sign & s)
{
	int i,r;
	for(i=0;i<6;i++)
	{
		r = memcmp(s.temp,keyword[i],s.i);
		if(r == 0)
		{
			s.token = i+1;
			return true;
			break;
		}
	}
	return false;
}

bool is_id(sign & s)
{
	int i;
	bool b = false;
	if( (s.temp[0]>='a' && s.temp[0]<='z') | (s.temp[0]>='A' && s.temp[0]<='Z') )
		b = true;
	else
		return b;
	for(i=1;i<strlen(s.temp);i++)
	{
		if( (s.temp[i]>='a' && s.temp[i]<='z') | (s.temp[i]>='A' && s.temp[i]<='Z') | (s.temp[i]>='0' && s.temp[i]<='9'))
			;
		else
		{
			b = false;
			return b;
		}
	}
	return b;
}

bool is_num(sign & s)
{
	digit.push(0);
	bool b = true;
	char c;
	int state = 12;
	for(int i=0;i<strlen(s.temp);i++)
	{
		c = s.temp[i];
		//int tn;
		switch(state)
		{
		case 12:
			{
				if(c>='0' && c<='9' || c=='-')
				{
					state = 13;
				}
				else
					return false;
				break;
			}
		case 13:
			{
				if(c>='0' && c<='9') state = 13;
				else if(c=='.') state=14;
				else if(c=='E' || c=='e') state=16;
				else return false;
				break;
			}
		case 14:
			{
				if(c>='0' && c<='9') state=15;
				else return false;
				break;
			}
		case 15:
			{
				if(c>='0' && c<='9') state=15;
				else if(c=='E' || c=='e') state=16;
				else return false;
				break;
			}
		case 16:
			{
				if(c=='+' || c=='-') state=17;
				else if(c>='0' && c<='9') state=18;
				else return false;
				break;
			}
		case 17:
			{
				if(c>='0' && c<='9') state=18;
				else return false;
				break;
			}
		case 18:
			{
				if(c>='0' && c<='9') state=18;
				else return false;
				break;
			}
		}
	}
	return b;
}

int handle(sign & s)
{
	s.temp[s.i] = '\0';
	if(strlen(s.temp)==0)
		return 0;
	if(is_key_word(s))
	{
		cout<<"("<<s.token<<","<<keyword[s.token-1]<<")";
		inputid.push(s.token);
		return s.token;
	}
	else if(is_id(s))
	{
		cout<<"(10,"<<s.temp<<")";
		inputid.push(10);
		return 10;
	}
	else if(is_num(s))
	{
		cout<<"(11,"<<s.temp<<")";
		inputid.push(11);
		int i=0;
		float n=0;
		int n1=0;
		while(i<s.i)
		{  n1=n1*10;
		if(s.temp[i]=='.')
		{
			n1=1;
			i++;
		}
		else
		{
			n=n*10+(s.temp[i]-'0');
			i++;
		}


		}
		if(n1!=0)
			n=n/n1;
		// cout<<s.i<<"  "<<s.temp<<"  "<<n<<endl;
		digit1.push(n);
		n=0;
		reset(s);
		return 11;
	}
	else
	{
		return 0;
	}
	reset(s);
}

void scan(FILE * fp)
{
	sign mark = {1,-1,{'$','$','$','$','$','$','$','$','$','$'},0};
	char ch;
	do
	{
		ch = fgetc(fp);
		if(ch=='\n')
		{
			mark.line++;
			handle(mark);
		}
		else if(ch==' ')
			handle(mark);

		else if(ch=='+')
		{
			handle(mark);
			cout<<"(13,"<<ch<<")";
			inputid.push(13);
		}
		else if(ch=='-')
		{
			handle(mark);
			cout<<"(14,"<<ch<<")";
			inputid.push(14);
		}
		else if(ch=='*')
		{
			handle (mark);
			cout<<"(15,"<<ch<<")";
			inputid.push(15);
		}
		else if(ch=='/')
		{
			handle (mark);
			cout<<"(16,"<<ch<<")";
			inputid.push(16);
		}
		else if(ch==':')
		{
			handle (mark);
			mark.temp[mark.i++] = ch;
			cout<<"(17,"<<ch<<")";
			inputid.push(17);
		}
		else if(ch=='<')
		{
			handle (mark);
			cout<<"(20,"<<ch<<")";
			inputid.push(20);
		}
		else if(ch=='>')
		{
			handle (mark);
			cout<<"(23,"<<ch<<")";
			inputid.push(23);
		}
		else if(ch=='=')
		{
			if(mark.temp[mark.i-1]==':')
			{
				cout<<"(18,:=)";
				reset(mark);
				inputid.push(18);
			}
			else
			{
				handle(mark);
				cout<<"(25,"<<ch<<")";
				inputid.push(25);
			}
		}
		else if(ch==';')
		{
			handle (mark);
			cout<<"(26,"<<ch<<")";
			inputid.push(26);
		}
		else if(ch=='(')
		{
			handle (mark);
			cout<<"(27,"<<ch<<")";
			inputid.push(27);
		}
		else if(ch==')')
		{
			handle (mark);
			cout<<"(28,"<<ch<<")";
			inputid.push(28);
		}
		else
		{

			mark.temp[mark.i++] = ch;
			handle(mark);
		}
	}while(ch!='#');
	cout<<endl;
}
int main(int argc ,char *argv[])
{
    initialize();//初始化stack

    FILE * fp;
	fp = fopen("Input.txt","r");
	scan(fp);
	//cout<<inputid.size()<<endl;
	string temp;
	int h=0;
	int z=30;
	inputid.pop();
	inputid.push(0);
	while((!inputid.empty()) && z>0)
	{

		z--;


		while(true)
		{
			int state=-1,sflag2=0;
			char temp1=ufstack.top();
			int	 sflag1=inputid.front();
			//cout<<sflag1<<endl;
			{
				if(sflag1==11)
					flag1=0;
				else if(sflag1==13)
					flag1=1;
				else if(sflag1==15)
					flag1=2;
				else if(sflag1==27)
					flag1=3;
				else if(sflag1==28)
					flag1=4;
				else if(sflag1==0)
					flag1=5;
				else if(sflag1==14)
					flag1=9;
				else if(sflag1==16)
					flag1=10;

				else flag1=-1;
			}
			if(flag1==-1)
			{
				cout<<"Unexpected symbol!"<<endl;

			}
			state=temp1-'0';
			//	cout<<state<<"VVVVV"<<flag1<<endl;
			char sta=0;
			char t1=ufstack.top();
			ufstack.pop();
			if(!ufstack.empty() && ufstack.top()>='0' && ufstack.top()<='9')
			{

				sta=ufstack.top()-'0';
				if(sta>0)
					state=state+sta*10;

			}

			else
				ufstack.push(t1);

			cout<<"("<<state<<", "<<flag1<<")  ------"<<AnalyzeChart[state][flag1].c_str ()<<"-----"<<endl;
			if(strcmp(AnalyzeChart[state][flag1].c_str (),"s5")==0)//移近
			{
				ufstack.push('i');
				ufstack.push('5');
				cout<<"shiftid"<<endl;
				//ip++;
				digit.push(digit1.front());
				digit1.pop();
				cout<<inputid.front();
				inputid.pop();
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"s4")==0)//移近
			{
				ufstack.push('(');
				ufstack.push('4');
				cout<<"shift ( "<<endl;
				//ip++;
				inputid.pop();
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"s6")==0)//移近
			{
				ufstack.push('+');
				ufstack.push('6');
				cout<<"shift + "<<endl;
				//ip++;
				inputid.pop();
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"s7")==0)//移近
			{
				ufstack.push('-');
				ufstack.push('7');
				cout<<"shift - "<<endl;
				//ip++;
				inputid.pop();
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"s8")==0)//移近
			{
				ufstack.push('*');
				ufstack.push('8');
				cout<<"shift * "<<endl;
				//ip++;
				inputid.pop();
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"s9")==0)//移近
			{
				ufstack.push('/');
				ufstack.push('9');
				cout<<"shift / "<<endl;
				//ip++;
				inputid.pop();
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"r1")==0)//reduce
			{
				for(int i=0;i<6;i++)
					ufstack.pop();

				cout<<"reduce E->E+T"<<endl;
				float ntop=digit.top();
				//digit.pop();
				digit.pop();
				cout<<ntop<<"+"<<digit.top()<<"=";
				ntop+=digit.top();
				digit.pop();
				digit.push(ntop);
				cout<<digit.top()<<endl;

				int st=ufstack.top()-'0';
				ufstack.push('E');
				char ch=*AnalyzeChart[st][6].c_str ();
				if(strcmp(AnalyzeChart[st][6].c_str (),"10")==0)
				{
					ufstack.push(*AnalyzeChart[st][6].c_str ());
					ufstack.push(*(AnalyzeChart[st][6].c_str ()+1));
				}

				else
					ufstack.push(ch);
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"r7")==0)//reduce
			{
				for(int i=0;i<6;i++)
					ufstack.pop();

				cout<<"reduce E->E-T"<<endl;
				float ntop=digit.top();
				//digit.pop();
				digit.pop();
				cout<<digit.top()<<"-"<<ntop<<"=";
				ntop=digit.top()-ntop;
				digit.pop();
				digit.push(ntop);
				cout<<digit.top()<<endl;

				int st=ufstack.top()-'0';
				ufstack.push('E');
				char ch=*AnalyzeChart[st][6].c_str ();
				if(strcmp(AnalyzeChart[st][6].c_str (),"10")==0)
				{
					ufstack.push(*AnalyzeChart[st][6].c_str ());
					ufstack.push(*(AnalyzeChart[st][6].c_str ()+1));
				}

				else
					ufstack.push(ch);
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"r2")==0)//reduce
			{
				ufstack.pop();
				ufstack.pop();
				cout<<"reduce E->T"<<endl;
				int st=ufstack.top()-'0';
				ufstack.push('E');
				char ch=*AnalyzeChart[st][6].c_str ();
				if(strcmp(AnalyzeChart[st][6].c_str (),"10")==0)
				{
					ufstack.push(*AnalyzeChart[st][6].c_str ());
					ufstack.push(*(AnalyzeChart[st][6].c_str ()+1));
				}

				else
					ufstack.push(ch);
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"r3")==0)//reduce
			{
				for(int i=0;i<6;i++)
					ufstack.pop();

				cout<<"reduce T->T*F"<<endl;
				float ntop=digit.top();
				digit.pop();
				//	digit.pop();
				cout<<ntop<<"*"<<digit.top()<<"=";
				ntop=ntop*digit.top();
				digit.pop();
				digit.push(ntop);
				cout<<ntop<<endl;

				int st=ufstack.top()-'0';

				ufstack.push('T');
				char ch=*AnalyzeChart[st][7].c_str ();
				if(strcmp(AnalyzeChart[st][7].c_str (),"11")==0)
				{
					ufstack.push(*AnalyzeChart[st][7].c_str ());
					ufstack.push(*(AnalyzeChart[st][7].c_str ()+1));
				}
				else if(strcmp(AnalyzeChart[st][7].c_str (),"12")==0)
				{
					ufstack.push(*AnalyzeChart[st][7].c_str ());
					ufstack.push(*(AnalyzeChart[st][7].c_str ()+1));
				}

				else
					ufstack.push(ch);
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"r8")==0)//reduce
			{
				for(int i=0;i<6;i++)
					ufstack.pop();

				cout<<"reduce T->T/F"<<endl;
				float ntop=digit.top();
				digit.pop();
				//	digit.pop();
				cout<<digit.top()<<"/"<<ntop<<"=";
				if(ntop!=0)
					ntop=digit.top()/ntop;
				else
				{
					cout<<"error,除数不能是零"<<endl;
					ntop=0;
				}
                cout<<ntop<<endl;
				digit.pop();
				digit.push(ntop);
				//cout<<ntop<<"_________"<<digit.top()<<endl;

				int st=ufstack.top()-'0';

				ufstack.push('T');
				char ch=*AnalyzeChart[st][7].c_str ();
				if(strcmp(AnalyzeChart[st][7].c_str (),"11")==0)
				{
					ufstack.push(*AnalyzeChart[st][7].c_str ());
					ufstack.push(*(AnalyzeChart[st][7].c_str ()+1));
				}
				else if(strcmp(AnalyzeChart[st][7].c_str (),"12")==0)
				{
					ufstack.push(*AnalyzeChart[st][7].c_str ());
					ufstack.push(*(AnalyzeChart[st][7].c_str ()+1));
				}

				else
					ufstack.push(ch);
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"r4")==0)//reduce
			{
				ufstack.pop();
				ufstack.pop();
				cout<<"reduce T->F"<<endl;
				int st=ufstack.top()-'0';
				ufstack.push('T');
				char ch=*AnalyzeChart[st][7].c_str ();
				if(strcmp(AnalyzeChart[st][7].c_str (),"11")==0)
				{
					ufstack.push(*AnalyzeChart[st][7].c_str ());
					ufstack.push(*(AnalyzeChart[st][7].c_str ()+1));
				}
				else if(strcmp(AnalyzeChart[st][7].c_str (),"12")==0)
				{
					ufstack.push(*AnalyzeChart[st][7].c_str ());
					ufstack.push(*(AnalyzeChart[st][7].c_str ()+1));
				}

				else
					ufstack.push(ch);
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"r5")==0)//reduce
			{
				for(int i=0;i<6;i++)
					ufstack.pop();

				cout<<"reduce F->(E)"<<endl;
				int st=ufstack.top()-'0';

				ufstack.push('F');
				char ch=*AnalyzeChart[st][8].c_str ();
				if(strcmp(AnalyzeChart[st][8].c_str (),"13")==0)
				{
					ufstack.push(*AnalyzeChart[st][8].c_str ());
					ufstack.push(*(AnalyzeChart[st][8].c_str ()+1));
				}
				else if(strcmp(AnalyzeChart[st][8].c_str (),"14")==0)
				{
					ufstack.push(*AnalyzeChart[st][8].c_str ());
					ufstack.push(*(AnalyzeChart[st][8].c_str ()+1));
				}

				else
					ufstack.push(ch);
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"r6")==0)//reduce
			{
				for(int i=0;i<2;i++)
					ufstack.pop();

				cout<<"reduce F->id"<<endl;
				int st=ufstack.top()-'0';
				ufstack.push('F');
				char ch=*AnalyzeChart[st][8].c_str ();
				if(strcmp(AnalyzeChart[st][8].c_str (),"13")==0)
				{
					ufstack.push(*AnalyzeChart[st][8].c_str ());
					ufstack.push(*(AnalyzeChart[st][8].c_str ()+1));
				}
				else if(strcmp(AnalyzeChart[st][8].c_str (),"14")==0)
				{
					ufstack.push(*AnalyzeChart[st][8].c_str ());
					ufstack.push(*(AnalyzeChart[st][8].c_str ()+1));
				}

				else
					ufstack.push(ch);
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"acc")==0)
			{
				cout<<"Analyze complate! "<<endl;
				inputid.pop();
				break;
			}

			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"e2")==0)
			{
				cout<<"不配对的右括号！  "<<endl;
				inputid.pop();
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"e3")==0)
			{
				cout<<"缺少运算符    "<<endl;
				inputid.pop();
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"e1")==0)
			{
				cout<<"缺少运算对象     "<<endl;
				//ufstack.push('i');
				//ufstack.push('5');
				inputid.pop();

			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"e4")==0)
			{
				cout<<"缺少右括号    "<<endl;
				ufstack.push(')');
				ufstack.push('11');
			}
			else if(strcmp(AnalyzeChart[state][flag1].c_str (),"e5")==0)
			{
				cout<<"算符重复    "<<endl;

				inputid.pop();
			}
			else                                                          //M[X,a]=一个产生式
			{
				cout<<"Strange error happen !"<<endl;
				break;
			}
	}
	h++;
	}
    cout<<"最终结果是"<<digit.top()<<endl;
	system("pause");
    return 0;
}
