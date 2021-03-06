/*************************************************************************
> File Name: analyze.cpp
> Author: luoweichui
> Mail: 1043531734@qq.comgetmyarr
> Created Time: 2017年03月29日 星期三 15时28分31秒
************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string>
#include <iostream>
#include <string.h>
#include <map>
#include <vector>

using namespace std;
const int MAXLEN = 1024;
const int MAXSIZE = 10000;

class MyArr
{
private:
	char *tmp[8];
	int   truesize;
	map<int, map<int,string> >arr;
	bool MySplit(char *Strline);
	bool GetTime(char *stime, char *&dtime);
	bool GetCliIp(char *sourceip, char *&desip);
	bool GetTypeTimeCliStr(char *&type, char *&time, char *&clientip);
	bool ClearTmp();
	bool Merge(int gap);
	int  MyStrSub(const char *a,const char *b);
	bool GetMyString(char *Strline, char * &type, char * &time, char * &clientip);

public:
	int    count_dif_ip;
	vector<double>intertimearr;
	vector<double>oneinter;
	int    totalipj;
	int    internumz;
	int    max;
	int    one_to_end;
	int    count;

public:
	bool GetMyArr();
	bool MyMergeArrSort();
	int  GetCountDifIp();
	bool GetMytime();
	bool GetOneTime();
	MyArr()
	{
		count_dif_ip = 0;
		totalipj = 0;
		internumz = 0;
		max = 0;
		one_to_end = 0;
		count = 0;
		truesize = 0;
		intertimearr.reserve(MAXSIZE);
		oneinter.reserve(MAXSIZE);
	}
};



bool MyArr::MySplit(char *Strline)
{
	if (Strline == NULL || *Strline == '\n')
	{
		cout << "MySplit error" << endl;
		return false;
	}

	string str = Strline;
	int pos = str.find("\n", 0);
	Strline[pos] = '\0';

	char *ptr = strtok(Strline, " ");
	while (ptr != NULL)
	{
		tmp[this->count++] = ptr;
		ptr = strtok(NULL, " ");
	}
	return true;
}

bool MyArr::GetTime(char *stime, char *&dtime)
{
	if (stime == NULL)
	{
		cout << "GetTime error" << endl;
		return false;
	}
	string str = stime;
	int pos = str.find("=", 0);
	dtime = stime+pos+1;
	return true;
}


bool MyArr::GetCliIp(char *sourceip, char *&desip)
{
	if (sourceip == NULL)
	{
		cout << "GetCliIp error" << endl;
		return false;
	}
	string str = sourceip;
	int pos = str.find("=", 0);
	desip = sourceip + pos +1;
	return true;
}


bool MyArr::GetTypeTimeCliStr(char *&type, char *&time, char *&clientip)
{

	if (strncmp(tmp[2], "type=v2.bufferStart", strlen("type=v2.bufferStart")) == 0)
	{
		type = "t";
	}
	else
	{
		type = "p";
	}
	GetTime(tmp[3], time);

	GetCliIp(tmp[5], clientip);
	return true;
}


bool MyArr::GetMyString(char *Strline, char *&type, char *&time, char *&clientip)
{
	if (Strline == NULL)
	{
		cout << "GetMyString error" << endl;
		return false;
	}
	MySplit(Strline);
	GetTypeTimeCliStr(type, time, clientip);
	return true;
}


bool MyArr::ClearTmp()
{
	int i;
	for (i = 0; i < count; i++)
	{
		tmp[i] = NULL;
	}
	count = 0;
	return true;
}


bool MyArr::GetMyArr()
{
	int i = 0;
	char *path = "./momo-20170323.log";
	FILE *fr;
	fr = fopen(path, "r");
	assert(fr != NULL);

	char Strline[MAXLEN] = { 0 };
	string Mystring;
	char *type;
	char *time;
	char *clientip;

	while (!feof(fr))
	{
		fgets(Strline, MAXLEN, fr);
		if (*Strline == '\n' || *Strline == '\0')
		{
			break;
		}
		GetMyString(Strline, type, time, clientip);

		arr[i][0] = type;
		arr[i][1] = time;
		arr[i][2] = clientip;
		i++;
		truesize++;
		cout << "continue..." << truesize << endl;
		memset(Strline, 0, MAXLEN);
		ClearTmp();
	}

	fclose(fr);
	return true;
}

bool MyArr::Merge(int gap)
{
	int i = 0;
	int low1 = 0;
	int high1 = low1 + gap - 1;
	int low2 = high1 + 1;
	int high2 = low2 + gap - 1 < truesize - 1 ? low2 + gap - 1 : truesize - 1;
	map<int,map<int,string> >arrtmp;
	while (low2 < truesize)
	{
		while (low1 <= high1 && low2 <= high2)
		{
			if (arr[low1][2] < arr[low2][2])
			{
				arrtmp[i][0] = arr[low1][0];
				arrtmp[i][1] = arr[low1][1];
				arrtmp[i][2] = arr[low1][2];			
				i++;
				low1++;
			}
			else
			{
				arrtmp[i][0] = arr[low2][0];
				arrtmp[i][1] = arr[low2][1];
				arrtmp[i][2] = arr[low2][2];
				i++;
				low2++;

			}
		}

		while (low1 <= high1)
		{
			arrtmp[i][2] = arr[low1][2];
			arrtmp[i][0] = arr[low1][0];
			arrtmp[i][1] = arr[low1][1];
			i++;
			low1++;
		}
		while (low2 <= high2)
		{
			arrtmp[i][2] = arr[low2][2];
			arrtmp[i][0] = arr[low2][0];
			arrtmp[i][1] = arr[low2][1];
			i++;
			low2++;
		}

		low1 = high2 + 1;
		high1 = low1 + gap - 1;
		low2 = high1 + 1;
		high2 = low2 + gap - 1 < truesize - 1 ? low2 + gap - 1 : truesize - 1;
	}

	while (low1 < truesize)
	{
		arrtmp[i][2] = arr[low1][2];
		arrtmp[i][0] = arr[low1][0];
		arrtmp[i][1] = arr[low1][1];
		i++;
		low1++;
	}

	for (i = 0; i < truesize; i++)
	{
		arr[i][0] = arrtmp[i][0];
		arr[i][1] = arrtmp[i][1];
		arr[i][2] = arrtmp[i][2];
	}
	return true;
}

bool MyArr::MyMergeArrSort()
{
	int i;
	for (i = 1; i < truesize; i *= 2)
	{
		Merge(i);
		cout << i <<endl;
	}
	return true;
}


int MyArr::GetCountDifIp()
{
	int i;
	int total = 0;
	for (i = 0; i < truesize - 1;)
	{
		if (arr[i][2] == arr[i+1][2])
		{
			i++;
		}
		else
		{
			total++;
			i++;
		}
	}
	return total;
}

int MyArr::MyStrSub(const char *a,const char *b)
{
	if (a == NULL || b == NULL)
	{
		printf("MyStrSub error\n");
		exit(1);
	}

	int a_len;
	int b_len;
	int i;
	int cmd;
	int len;
	int j = 0;

	a_len = strlen(a);
	b_len = strlen(b);

	int *a_num = new int[a_len];
	int *b_num = new int[b_len];
	int des[100] = { 0 };
	char result[100];
	for (i = 0; i < a_len; i++)
	{
		a_num[a_len - i - 1] = a[i] - '0';
	}
	for (i = 0; i < b_len; i++)
	{
		b_num[b_len - i - 1] = b[i] - '0';
	}

	if (a_len > b_len)
	{
		cmd = 1;
	}
	else if (a_len < b_len)
	{
		cmd = -1;
	}
	else
	{
		cmd = strcmp(a, b);
	}

	len = a_len > b_len ? a_len : b_len;

	if (cmd > 0)
	{
		for (i = 0; i < len; i++)
		{
			if (a_num[i] < b_num[i])
			{
				a_num[i] += 10;
				a_num[i + 1] -= 1;
				des[j++] = a_num[i] - b_num[i];
			}
			else
			{
				des[j++] = a_num[i] - b_num[i];
			}
		}
	}
	else if (cmd < 0)
	{
		for (i = 0; i < len; i++)
		{
			if (b_num[i] < a_num[i])
			{
				b_num[i] += 10;
				b_num[i + 1] -= 1;
				des[j++] = b_num[i] - a_num[i];
			}
			else
			{
				des[j++] = b_num[i] - a_num[i];
			}
		}
	}
	else
	{
		for (i = 0; i < len; i++)
		{
			des[j++] = b_num[i] - a_num[i];
		}
	}

	j = 0;
	i = len - 1;
	while (des[i] == 0)i--; //until des[i] not 0

	for (i; i >= 0; i--)
	{
		result[j++] = des[i] + '0';
	}
	result[j] = '\0';

	delete[]a_num;
	delete[]b_num;
	return atoi(result);
}


bool MyArr::GetMytime() //Get every ip stop of second
{
	int i;
	int thisinternum = 0;
	int intertotal = 0;
	int w = 0;

	for (i = 0; i < truesize - 1;)
	{
		if (arr[i][2] != arr[i + 1][2])
		{
			if (thisinternum != 0)
			{
				if (max < thisinternum)
				{
					max = thisinternum;
				}
				intertimearr.push_back((double)intertotal / (thisinternum * 1000)); // ++ 优先级高
				totalipj++;
			}

			intertotal = 0;
			thisinternum = 0;
			i++;
		}
		else
		{
			if (arr[i][0] == arr[i+1][0])
			{
				i++;
			}
			else
			{
				w = MyStrSub(arr[i][1].c_str(), arr[i+1][1].c_str());
				intertotal += w;
				i += 2;
				thisinternum++;
			}
		}
	}
	return true;
}


bool MyArr::GetOneTime()
{
	int i;
	int thisinternum = 0;
	int intertotal = 0;
	int w = 0;

	for (i = 0; i < truesize - 1;)
	{
		if (arr[i][2] != arr[i + 1][2])
		{
			if (thisinternum == one_to_end)
			{
				oneinter.push_back((double)intertotal / (thisinternum * 1000));
				internumz++;
			}
			intertotal = 0;
			thisinternum = 0;
			i++;
		}
		else
		{
			if (arr[i][0] == arr[i+1][0])
			{
				i++;
			}
			else
			{
				w = MyStrSub(arr[i][1].c_str(), arr[i + 1][1].c_str());
				intertotal += w;
				i += 2;
				thisinternum++;
			}
		}
	}
	return true;
}

int main()
{
	int total = 0;
	int j = 0;
	int k = 0;
	int i = 0;
	MyArr timeobject;
	timeobject.GetMyArr();
	timeobject.MyMergeArrSort();
	timeobject.count_dif_ip = timeobject.GetCountDifIp();
	timeobject.GetMytime();
	for (timeobject.one_to_end = 1; timeobject.one_to_end <= 20; timeobject.one_to_end++)
	{
		cout << "number:" << timeobject.one_to_end << endl;
		timeobject.GetOneTime();
		for (k = 0; k < 15; k++)
		{
			for (i = 0; i < timeobject.internumz; i++)
			{
				if (timeobject.oneinter[i] <= k + 1 && timeobject.oneinter[i] >= k)
				{
					total++;
				}
			}
			printf("%ds<time<%ds  %f%\n", k, k + 1, (double)total * 100 / timeobject.totalipj);
			total = 0;
		}
		total = 0;
		for (i = 0; i < timeobject.internumz; i++)
		{
			if (timeobject.oneinter[i] > 15)
			{
				total++;
			}
		}
		printf("time>15s %f%\n", (double)total * 100 / timeobject.totalipj);
		timeobject.internumz = 0;
	}
	return 0;
}
