#include "fileSystem.h"

void init()
{
	char *dir = "disk";
	_mkdir(dir);
	for (int i = 0; i < TotalBlockCnt; i++)
	{
		char path[MaxCharLen];
		sprintf(path, "%s\\%d.txt", dir, i);
		FILE *fp = fopen(path, "r");
		if (!fp)
			fp = fopen(path, "w");
		fclose(fp);
	}
}

void getCurTime(char* currtime) //获取当前时间
{
	char dbuffer[9];
	char tbuffer[9];
	_strdate(dbuffer);
	_strtime(tbuffer);
	strcpy(currtime, dbuffer);
	strcat(currtime, " ");
	strcat(currtime, tbuffer);
}

vector<string> split(string str, string pattern)	//	把string以特定分隔符作切分
{
	string::size_type pos;
	vector<string> result;
	str += pattern;//扩展字符串以方便操作  
	int size = str.size();

	for (int i = 0; i<size; i++)
	{
		pos = str.find(pattern, i);
		if (pos<size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

bool stringAreEqual(string a, string b)
{
	int alen = a.length();
	int blen = b.length();
	if (alen != blen)
		return false;
	for (int i = 0; i < alen; i++)
	{
		char atmp = tolower(a[i]);
		char btmp = tolower(b[i]);
		if (atmp != btmp)
			return false;
	}
	return true;
}