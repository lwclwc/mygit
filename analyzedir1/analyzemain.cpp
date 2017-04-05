/*************************************************************************
	> File Name: analyzemain.cpp
	> Author: luoweichui
	> Mail: 1043531734@qq.com 
	> Created Time: 2017年04月05日 星期三 15时49分29秒
 ************************************************************************/

#include "analyze.h"
using namespace std;

int main()
{
	MyArr timeobject;
	cout << "start..." <<endl;
	timeobject.input_file();
	cout << "input_file end" <<endl;
	timeobject.my_merge_arr_sort();
	timeobject.get_my_time();
	timeobject.output_result();
	return 0;
}

