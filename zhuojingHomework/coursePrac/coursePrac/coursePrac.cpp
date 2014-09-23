// coursePrac.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class A
{
public:
	A()
	//	: z(mz)
	{
	}

	int getZ() const
	{
		return z;
	}

public:
	int z;
};

class sonA : private A
{
public:
	sonA()
	{
		z = 10;
		printf( "%d\n", z );
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	sonA sa;

	return 0;
}
