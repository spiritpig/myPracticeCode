// myDequeLoop.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DequeLoop.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myDequeLoop<int> mdl;

	for ( int i=0; i<10; ++i )
	{
		mdl.push_back(i);
	}
	for ( int i=30; i<40; ++i )
	{
		mdl.push_front(i);
	}

	myDequeLoop<int>::iterator mdlIter = mdl.begin();
	for ( int i=0; i<(int)(mdl.size()); ++i )
	{
		printf( "%d ", *(mdlIter+i) );
	}
	printf( "\n" );

	return 0;
}

