// testVirtual.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

class base
{
public:
	void someFun()
	{
		printf( "����ķ��麯����\n" );
	}

	virtual void vfun()
	{
		printf( "������麯����\n" );
	}

	int x, y;
};

class child : public base
{
public:
	virtual void vfun()
	{
		printf( "������麯����\n" );
	}
};

typedef void (*vFun) ();

int _tmain(int argc, _TCHAR* argv[])
{
	child c;
	base b = c;
	//*(int *)(&b) = NULL;//*((int *)(&c) + sizeof(b));
	*((int *)(&b)+1) = 12;
	*((int *)(&b)+2) = 3605;
	*(int *)(&c) = NULL;

	printf( "%d, %d, %d\n", b.x, b.y, sizeof(b) );
	b.vfun();
	c.vfun();

	//vFun childVFun = (vFun)*((int *)*(int *)(&b)+0);
	//childVFun();

	base *newb = new child;
	*(int *)(newb) = *(int *)(&b);

	newb->vfun();

	delete newb;

	return 0;
}


