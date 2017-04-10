/*************************************************************************
	> File Name: test.cpp
	> Author: luoweichui
	> Mail: 1043531734@qq.com 
	> Created Time: 2017年04月05日 星期三 11时25分06秒
 ************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string>strarr;
int my_split(string strline)
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

int main()
{
	string str = "aaa bbb ccc dddd";
    my_split(str);
	int size = strarr.size();
	for(int i = 0; i < size; i++)
	{
		cout << strarr.at(i)<<endl;
	}
	return 0;
}
