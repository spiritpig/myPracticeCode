// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int Function(int n)
{
	if (n > 1)
	{
		return n * Function(--n);
	}
	else
	{
		return 1;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{

	printf("n! = %d\n",Function(8));

	return 0;
}

