/*************************************************************************
	> File Name: analyze.h
	> Author: luoweichui
	> Mail: 1043531734@qq.com 
	> Created Time: 2017年04月01日 星期六 16时12分45秒
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
	vector<string>strarr;
	int   truesize;
	map<int, map<int,string> >arr;
	int my_split(string strline);
	int get_time(string stime, string &dtime);
	int get_cli_ip(string sourceip, string &desip);
	int get_type_time_cli_str(string &type, string &time, string &clientip);
	int clear_strarr(void);
	int merge(int gap);
	int my_str_sub(const char* a,const char* b);
	int get_my_string(string strline, string &type, string &time, string &clientip);

public:
	int    countdifip;
//	vector<double>intertimearr;
	struct InterTimeList
	{
		vector<int>numtimes;
		vector<double>intertimes;
	}intertimearr;

	int    totalipj;
	int    internumz;
	int    max;
	int    onetoend;
	int    count;

public:
	int input_file();
	int my_merge_arr_sort();
	int get_count_dif_ip();
	int get_my_time();
	int output_result();
	MyArr()
	{
		countdifip = 0;
		totalipj = 0;
		internumz = 0;
		max = 0;
		onetoend = 0;
		count = 0;
		truesize = 0;

		intertimearr.intertimes.reserve(MAXSIZE);
		intertimearr.numtimes.reserve(MAXSIZE);
	}
};

