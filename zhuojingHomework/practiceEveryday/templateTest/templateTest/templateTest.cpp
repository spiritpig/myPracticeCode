// templateTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

template<typename T>
class tp
{
public:
	static T st;
};

int tp<int>::st = 5;
//char tp<char>::st = 5;

int _tmain(int argc, _TCHAR* argv[])
{
	tp<int> ti;
	std::cout << ti.st;
	return 0;
}

