// stack.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	stackList<int> sa;

	for ( int i=0; i<10; i+=3 )
	{
		sa.push( i );
		printf( "推入成功, %d\n", i );
	}

	int t = -1;
	sa.getTop( t );
	printf( "top(T): %d\n", t );
	printf( "t top(): %d\n", sa.getTop() );
	
	for ( int i = 0; i<20; ++i )
	{
		
		if( sa.pop( i ) )
		{
			printf( "弹出成功, %d\n", i );
		}
		else
		{
			printf( "弹出失败, %d\n", i );
		}
	}

	for ( int i = 0; i<20; ++i )
	{
		if( sa.pop() )
		{
			printf( "弹出成功\n" );
		}
		else
		{
			printf( "弹出失败\n" );
		}
	}

	sa.setEmpty();
	
	if( sa.isEmpty() )
	{
		printf( "栈为空\n" );
	}

	return 0;
}

