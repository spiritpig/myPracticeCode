// myStlList.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myStlList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myStlList<int> msl;

	msl.push_back(5);
	msl.push_back(4);
	msl.push_back(3);
	msl.push_back(2);
	msl.push_back(1);
	
	msl.pop_back();
	msl.pop_back();
	msl.pop_back();
	msl.pop_back();
	msl.pop_back();

	return 0;
}

