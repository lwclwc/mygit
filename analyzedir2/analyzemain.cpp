/*************************************************************************
	> File Name: analyzemain.cpp
	> Author: luoweichui
	> Mail: 1043531734@qq.com 
	> Created Time: 2017年04月05日 星期三 15时49分29秒
 ************************************************************************/

#include "analyze.h"

int main()
{
	AnalyzeMoMo timeobject;
	std::cout << "start..." <<std::endl;
	timeobject.input_file();
	std::cout << "input_file end" <<std::endl;
	timeobject.my_merge_arr_sort();
	timeobject.get_my_time();
	//timeobject.show_result_data();
	timeobject.output_result();
	//timeobject.get_one_intertime_data();
	//timeobject.show_momo_data();
	return 0;
}

