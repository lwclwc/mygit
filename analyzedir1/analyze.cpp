/*************************************************************************
> File Name: analyze.cpp
> Author: luoweichui
> Mail: 1043531734@qq.comgetmyarr
> Created Time: 2017年03月29日 星期三 15时28分31秒
************************************************************************/


#include "analyze.h"

int MyArr::my_split(string strline)
{
	if (strline.empty() || strline.at(0) == '\n')
	{
		cout << "my_split error" << endl;
		return 0;
	}

	int pos = strline.find("\n", 0);
	strline[pos] = '\0';
	strline += " ";
	int size = strline.size();
	for	(int i = 0; i < size;)
	{
		pos = strline.find(" ",i);
		if (pos < size)
		{
			string s = strline.substr(i,pos-i);
			strarr.push_back(s);
			i = pos + 1;
		}
	}
	return 1;
}


int MyArr::get_time(string stime, string &dtime)
{
	if (stime.empty())
	{
		cout << "get_time error" << endl;
		return 0;
	}
	int pos = stime.find("=", 0);
	dtime = stime.substr(pos+1);
	return 1;
}


int MyArr::get_cli_ip(string sourceip, string &desip)
{
	if (sourceip.empty())
	{
		cout << "get_cli_ip error" << endl;
		return 0;
	}
	int pos = sourceip.find("=", 0);
	desip = sourceip.substr(pos+1);
	return 1;
}


int MyArr::get_type_time_cli_str(string &type, string &time, string &clientip)
{

	if (strarr[2].compare("type=v2.bufferStart") == 0)
	{
		type = "t";
	}
	else
	{
		type = "p";
	}
	get_time(strarr[3], time);

	get_cli_ip(strarr[5], clientip);
	return 1;
}


int MyArr::get_my_string(string mystring, string &type, string &time, string&clientip)
{
	if (mystring.empty())
	{
		cout << "get_my_string error" << endl;
		return 0;
	}
	my_split(mystring);
	get_type_time_cli_str(type, time, clientip);
	return 1;
}


int MyArr::clear_strarr()
{
	strarr.clear();
	return 1;
}


int MyArr::input_file()
{
	int i = 0;
	char *path = "./momo-20170323.log";
	FILE *fr;
	fr = fopen(path, "r");
	assert(fr != NULL);

	char strline[MAXLEN] = { 0 };
	string mystring;
	string type;
	string time;
	string clientip;

	while (!feof(fr))
	{
		fgets(strline, MAXLEN, fr);
		if (*strline == '\n' || *strline == '\0')
		{
			break;
		}
		mystring = strline;
		get_my_string(mystring, type, time, clientip);

		arr[i][0] = type;
		arr[i][1] = time;
		arr[i][2] = clientip;
		i++;
		truesize++;
		cout << "continue..." << truesize << endl;
		memset(strline, 0, MAXLEN);
		clear_strarr();
	}

	fclose(fr);
	return true;
}

int MyArr::merge(int gap)
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
	return 1;
}

int MyArr::my_merge_arr_sort()
{
	int i;
	for (i = 1; i < truesize; i *= 2)
	{
		merge(i);
		cout << i <<endl;
	}
	return 1;
}


int MyArr::get_count_dif_ip()
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

int MyArr::my_str_sub(const char *a,const char *b)
{
	if (a == NULL || b == NULL)
	{
		printf("My_Str_Sub error\n");
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
				a_num[i]  += 10;
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
				des[j++] =  b_num[i] - a_num[i];
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


int MyArr::get_my_time() //Get every ip stop of second
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
				intertimearr.numtimes.push_back(thisinternum);
				intertimearr.intertimes.push_back((double)intertotal / (thisinternum * 1000));
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
				w = my_str_sub(arr[i][1] .c_str(), arr[i+1][1].c_str());
				intertotal += w;
				i += 2;
			 	thisinternum++;
			}
		}
	}
	return 1;
}


int MyArr::output_result()
{
	int size1 = intertimearr.numtimes.size();
	int size2 = intertimearr.intertimes.size();
	int total = 0;
	int j = 0;
	int k = 0;
	for (int i = 1; i <= 20; i++)
	{
		cout << "number:" << i << endl;
		for (k = 0; k < 15; k++)
		{	
			for (j = 0; j < size1; j++)
			{
				if (intertimearr.numtimes[j]  == i)
				{
					if (intertimearr.intertimes[j] <= k + 1 && intertimearr.intertimes[j] >= k)
					{
						total++;
					}
				}
			}
			printf("%ds<time<%ds  %f%\n", k, k + 1, (double)total * 100 / totalipj);
			total = 0;
			j = 0;
		}
		total = 0;
		j = 0;
		for (j = 0; j < size1; j++)
		{
			if (intertimearr.numtimes[j] == i)
			{
				if (intertimearr.intertimes[j] > 15)
				{
					total++;
			 	}
			}
		}
		printf("time>15s %f%\n", (double)total * 100 / totalipj);
		total = 0;
		j = 0;
		k = 0;
	}
	return 1;
}
