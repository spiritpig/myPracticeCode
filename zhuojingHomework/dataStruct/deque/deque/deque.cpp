// deque.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	myDequeList<int> mda;

	for ( int i=0; i<30; i+=2 )
	{
		mda.push( i );
		printf( "推入成功,%d\n", i );
	}

	printf( "%d\n", mda.First() );

	int t=0;
	for ( int i=0; i<40; i+=2 )
	{
		if( mda.pop( t ) )
		{
			printf( "弹出成功,%d\n", t );
		}
		else
		{
			printf( "弹出失败,%d\n", i );
		}
	}

	if( mda.pop() )
	{
		printf( "弹出成功\n" );
	}
	else
	{
		printf( "弹出失败\n" );
	}

	mda.setEmpty();
	if( mda.isEmpty() )
	{
		printf( "栈为空\n" );
	}
	return 0;
}

