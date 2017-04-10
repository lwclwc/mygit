/*************************************************************************
> File Name: analyze.cpp
> Author: luoweichui
> Mail: 1043531734@qq.comgetAnalyzeMoMo
> Created Time: 2017年03月29日 星期三 15时28分31秒
************************************************************************/


#include "analyze.h"

AnalyzeMoMo::AnalyzeMoMo()
	:totalipj(0),
	truesize(0),
	max(0)
	{}

AnalyzeMoMo::~AnalyzeMoMo(){}

int AnalyzeMoMo::my_split(std::string &strline)
{
	if (strline.empty() || strline.at(0) == '\n')
	{
		std::cout << "my_split error" << std::endl;
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
			std::string s = strline.substr(i,pos-i);
			strarr.push_back(s);
			i = pos + 1;
		}
	}
	return 1;
}


int AnalyzeMoMo::get_time(const std::string &stime, std::string &dtime)
{
	if (stime.empty())
	{
		std::cout << "get_time error" << std::endl;
		return 0;
	}
	int pos = stime.find("=", 0);
	dtime = stime.substr(pos+1);
	return 1;
}


int AnalyzeMoMo::get_cli_ip(const std::string &sourceip, std::string &desip)
{
	if (sourceip.empty())
	{
		std::cout << "get_cli_ip error" << std::endl;
		return 0;
	}
	int pos = sourceip.find("=", 0);
	desip = sourceip.substr(pos+1);
	return 1;
}


int AnalyzeMoMo::get_cdn_ip(const std::string &sourceip,std::string &desip)
{
	if (sourceip.empty())
	{
		std::cout << "get_cdn_ip error" << std::endl;
		return 0;
	}
	int pos = sourceip.find("=",0);
	desip = sourceip.substr(pos+1);
	return 1;
}


int AnalyzeMoMo::get_url(const std::string &sourceurl,std::string &desurl)
{
	if (sourceurl.empty())
	{
		std::cout << "get_url error" << std::endl;
		return 0;
	}
	int pos = sourceurl.find("=",0);
	desurl = sourceurl.substr(pos+1);
	return 1;

}


int AnalyzeMoMo::get_date(std::string &sourcedate,std::string &sourcedate1,std::string &desdate)
{
	if (sourcedate.empty() || sourcedate1.empty())
	{
		std::cout << "get_date" <<std::endl;
		return 0;
	}

	int pos = sourcedate.find("[",0);
	desdate = sourcedate.find(pos+1);
	pos = sourcedate1.find("]",0);
	sourcedate1[pos] = '\0';
	desdate += sourcedate1;
	return 1;
}

int AnalyzeMoMo::get_type_time_cli_str(std::string &type, std::string &time, std::string &clientip,
		std::string &url,std::string &date,std::string &cdnip)
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

	get_cdn_ip(strarr[4],cdnip);

	get_url(strarr[6],url);

	get_date(strarr[0],strarr[1],date);
	return 1;
}


int AnalyzeMoMo::get_my_string(std::string &mystring, std::string &type, std::string &time, 
		std::string&clientip,std::string &url,std::string &date,std::string &cdnip)
{
	if (mystring.empty())
	{
		std::cout << "get_my_string error" << std::endl;
		return 0;
	}
	my_split(mystring);
	get_type_time_cli_str(type, time, clientip, url, date, cdnip);
	return 1;
}


int AnalyzeMoMo::clear_strarr()
{
	strarr.clear();
	return 1;
}

int AnalyzeMoMo::my_str_sub(const std::string a,const std::string b)
{
	if (a.empty() || b.empty())
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

	a_len = a.size();
	b_len = b.size();

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
		cmd = a.compare(b);
	}

	len = a_len > b_len ? a_len : b_len;

	if (cmd > 0)
	{
		for (i = 0; i < len; i++)
		{
			if (a_num[i] < b_num[i])
			{
				a_num [i]  += 10;
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


int AnalyzeMoMo::input_file()
{
	int i = 0;
	std::string p = "./momo-20170323.log";
	const char *path =p.c_str();
	FILE *fr;
	fr = fopen(path, "r");
	assert(fr != NULL);

	char strline[MAXLEN] = { 0 };
	std::string mystring;
	std::string type;
	std::string time;
	std::string clientip;
	std::string cdnip;
	std::string url;
	std::string date;
	struct MoMoData ctrl;
	while (!feof(fr))
	{
		fgets(strline, MAXLEN, fr);
		if (*strline == '\n' || *strline == '\0')
		{
			break;
		}
		mystring = strline;
		get_my_string(mystring,type,time,clientip,url,date,cdnip);

		ctrl.type = type;
		ctrl.time = time;
		ctrl.clientip = clientip;
		ctrl.url = url;
		ctrl.date = date;
		ctrl.cdnip = cdnip;
		momodata.push_back(ctrl);

		++i;
		memset(strline, 0, MAXLEN);
		clear_strarr();
	}

	fclose(fr);
	return 1;
}


int AnalyzeMoMo::merge(int gap)
{
	int len = momodata.size();
	int i = 0;
	int low1 = 0;
	int high1 = low1 + gap - 1;
	int low2 = high1 + 1;
	int high2 = low2 + gap - 1 < len - 1 ? low2 + gap - 1 : len - 1;
	std::map<int,MoMoData>datatmp;
	while (low2 < len)
	{
		while (low1 <= high1 && low2 <= high2)
		{
			if (momodata[low1].clientip <= momodata[low2].clientip)
			{
				datatmp[i].clientip = momodata[low1].clientip;
				datatmp[i].type = momodata[low1].type;
				datatmp[i].time = momodata[low1].time;
				datatmp[i].cdnip = momodata[low1].cdnip;
				datatmp[i].url = momodata[low1].url;
				datatmp[i].date = momodata[low1].date;
				i++;
				low1++;
			}
			else
			{
				datatmp[i].clientip = momodata[low2].clientip;
				datatmp[i].type = momodata[low2].type;
				datatmp[i].time = momodata[low2].time;
				datatmp[i].cdnip = momodata[low2].cdnip;
				datatmp[i].url = momodata[low2].url;
				datatmp[i].date = momodata[low2].date;
				i++;
				low2++;

			}
		}

		while (low1 <= high1)
		{
			datatmp[i].clientip = momodata[low1].clientip;
			datatmp[i].type = momodata[low1].type;
			datatmp[i].time = momodata[low1].time;
			datatmp[i].cdnip = momodata[low1].cdnip;
			datatmp[i].url = momodata[low1].url;
			datatmp[i].date = momodata[low1].date;
			i++;
			low1++;
		}
		while (low2 <= high2)
		{
			datatmp[i].clientip = momodata[low2].clientip;
			datatmp[i].type = momodata[low2].type;
			datatmp[i].time = momodata[low2].time;
			datatmp[i].cdnip = momodata[low2].cdnip;
			datatmp[i].url = momodata[low2].url;
			datatmp[i].date = momodata[low2].date;
			i++;
			low2++;
		}

		low1 = high2 + 1;
		high1 = low1 + gap - 1;
		low2 = high1 + 1;
		high2 = low2 + gap - 1 < len - 1 ? low2 + gap - 1 : len - 1;
	}

	while (low1 < len)
	{
		datatmp[i].clientip = momodata[low1].clientip;
		datatmp[i].type = momodata[low1].type;
		datatmp[i].time = momodata[low1].time;
		datatmp[i].cdnip = momodata[low1].cdnip;
		datatmp[i].url = momodata[low1].url;
		datatmp[i].date = momodata[low1].date;
		i++;
		low1++;
	}

	for (i = 0; i < len; i++)
	{
		momodata[i].clientip = datatmp[i].clientip;
		momodata[i].type = datatmp[i].type;
		momodata[i].time = datatmp[i].time;
		momodata[i].cdnip = datatmp[i].cdnip;
		momodata[i].url = datatmp[i].url;
		momodata[i].date = datatmp[i].date;
	}
	return 1;
}


int AnalyzeMoMo::my_merge_arr_sort()
{
	int len = momodata.size();
	int i;
	for (i = 1; i < len; i *= 2)
	{
		merge(i);
	}
	return 1;
}


int AnalyzeMoMo::get_my_time()
{
	int i = 0;
	int w = 0;
	int len = momodata.size();

	for (i = 0; i < len - 1;)
	{
		if (momodata[i].clientip != momodata[i+1].clientip)
		{
			++i;
		}
		else
		{
			if (momodata[i].type == momodata[i+1].type)
			{
				++i;
			}
			else
			{
			 	w = my_str_sub(momodata[i].time, momodata[i+1].time);
				double ws = static_cast<double>(w)/1000;
				resultdata[momodata[i].clientip].intertimes.push_back(ws);
				resultdata[momodata[i].clientip].numbertimes++;
				resultdata[momodata[i].clientip].type = momodata[i].type;
				i += 2;
			}
		}
	}
	return 1;
}

int AnalyzeMoMo::show_result_data()
{
	std::map<std::string,ResultData>::iterator it;
	for (it=resultdata.begin();it!=resultdata.end();++it)
	{
		std::cout<<it->first<<" "<<it->second.numbertimes<<" " ;
		for (int i = 0; i < it->second.numbertimes; ++i)
		{
			std::cout<<it->second.intertimes[i]<<" ";
		}
		std::cout<<" "<<std::endl;
	}
	return 1;
}


int AnalyzeMoMo::get_one_intertime_data()
{
	int total = 0;
	std::map<std::string,ResultData>::iterator it;
	for (it=resultdata.begin();it!=resultdata.end();++it)
	{
		if (it->second.numbertimes == 1)
		{
			for (int i = 0; i < it->second.numbertimes;++i)
			{
 				std::cout<<it->first<<" "<<it->second.numbertimes<<" "<<it->second.type<<" ";
				std::cout<<it->second.intertimes[i]<<" ";
			}
			std::cout<<" "<<std::endl;
		}
	}

	for (it=resultdata.begin();it!=resultdata.end();++it)
	{
		if (it->second.numbertimes == 1)
		{
			for (int i = 0; i < it->second.numbertimes;++i)
			{
				if (it->second.intertimes[i] >= 15)
				{
					++total;	
				}
			}
		}
	}
	std::cout<<total<<std::endl;
	return 1;
}


int AnalyzeMoMo::show_momo_data()
{
	int size = momodata.size();
	for (int i = 0; i < size; ++i)
	{
		std::cout<<momodata[i].type<<" "<<momodata[i].time<<" "<<momodata[i].clientip<<" ";
		std::cout<<" "<<std::endl;
	}
}


int AnalyzeMoMo::output_result()
{
	int k = 0;
	int i = 0;
	int t = 0;
	int total = 0;
	int subtotal = 0;
	std::map<std::string,ResultData>::iterator it;
	for (it=resultdata.begin(); it!=resultdata.end(); ++it)
	{
		total += it->second.numbertimes;
	}

	for (k=1; k<=20; ++k)
	{
		printf("number:%d\n",k);
		for (t=0; t<15; ++t)
		{
			for (it=resultdata.begin(); it!=resultdata.end(); ++it)
			{
				if (it->second.numbertimes == k)
				{
					for(i=0; i<it->second.numbertimes; ++i)
					{
						if (it->second.intertimes[i]>=t && it->second.intertimes[i]<t+1)
						{
							++subtotal;		
						}
					}
				}
			}
			printf("%ds=<time<%ds  %f%\n", t, t + 1, (double)subtotal * 100 / total);
			subtotal = 0;
		}

		subtotal = 0;
		for (it=resultdata.begin(); it!=resultdata.end(); ++it)
		{
			if (it->second.numbertimes == k)
			{
				for(i=0; i<it->second.numbertimes; ++i)
				{
					if (it->second.intertimes[i]>=15)
					{
						++subtotal;		
					}
				}
			}
		}
		printf("time>=15s  %f%\n", (double)subtotal * 100 / total);
		subtotal = 0;
	}
	return 1;
}
