#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#define TOTAL 294
#define POS 210
#define NEG 84
#define TRAIN 100
#define TEST TOTAL-TRAIN
using namespace std;

string badge[TOTAL];
string name[TOTAL];

void readfile()
{
    ifstream in("badges.txt");
    string temp;
    for(int m=0; m < TOTAL; m++)
        name[m].clear();

    if(! in.is_open())
    {
        cout << "error opening file" << endl;
        exit(1);
    }
    else
    {
        int bi=0,ni=0;
        while(getline(in, temp))
        {
            name[ni++] = temp.substr(temp.find(' '));
            badge[bi++] = temp[0];
        }
    }
    in.close();
}

int main()
{
    readfile();
    for(int i =0; i < TOTAL; i++)
    {
        cout << badge[i] <<' ';
        cout << name[i] << endl;
    }

    system("pause");
    return 0;
}
