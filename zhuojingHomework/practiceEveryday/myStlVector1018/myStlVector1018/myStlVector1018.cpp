// myStlVector1018.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "myStlVector1018.h"

int _tmain(int argc, _TCHAR* argv[])
{

	myStlVector<int> msv;

	msv.push_back(10);
	msv.push_back(10);
	msv.push_back(10);
	msv.push_back(10);

	msv.pop_back();
	msv.pop_back();
	msv.pop_back();
	msv.pop_back();
	msv.pop_back();

	return 0;
}

