// test.cpp : �������̨Ӧ�ó������ڵ㡣
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

