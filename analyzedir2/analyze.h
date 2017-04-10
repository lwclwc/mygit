/*************************************************************************
	> File Name: analyze.h
	> Author: luoweichui
	> Mail: 1043531734@qq.com 
	> Created Time: 2017年04月01日 星期六 16时12分45秒
 ************************************************************************/

#ifndef _ANALYZE_H_
#define _ANALYZE_H_

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

const int MAXLEN = 1024;
const int MAXSIZE = 10000;

struct MoMoData
{
	std::string type;
	std::string date;
	std::string time;
	std::string cdnip;
	std::string clientip;
	std::string url;
	std::string place;
};


struct ResultData
{
	int numbertimes;
	std::string type;
	std::vector<double>intertimes;
};


class AnalyzeMoMo
{
public:
	AnalyzeMoMo();
	~AnalyzeMoMo();
	int input_file();
	int my_merge_arr_sort();
	int get_my_time();
	int output_result();
	int show_result_data();
	int get_count_dif_ip();
	int get_one_intertime_data();
	int show_momo_data();
private:
	int my_split(std::string &strline);
	int get_time(const std::string &stime, std::string &dtime);
	int get_cli_ip(const std::string &sourceip, std::string &desip);
	int get_cdn_ip(const std::string &sourceip,std::string &desip);
	int get_url(const std::string &sourceurl,std::string &desurl);
	int get_date(std::string &sourcedate,std::string &sourcedate1,std::string &desdate);
	int get_type_time_cli_str(std::string &type, std::string &time, 
			std::string &clientip,std::string &url,std::string &date,std::string &cdnip);
	int clear_strarr(void);
	int merge(int gap);
	int my_str_sub(const std::string a,const std::string b);
	int get_my_string(std::string &strline, std::string &type, std::string &time,
			std::string &clientip,std::string &url,std::string &date,std::string &cdnip);

	std::vector<std::string>strarr;
	std::vector<MoMoData>momodata;
	std::map<std::string,ResultData>resultdata;
	int totalipj;
	int truesize;
	int max;
};
#endif
