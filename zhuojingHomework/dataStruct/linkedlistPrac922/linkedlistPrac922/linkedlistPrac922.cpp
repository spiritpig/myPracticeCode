// linkedlistPrac922.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myList.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	linkedList<int> ll;

	ll.Insert( 0, 12321 );
	for ( int i=0; i<10; ++i )
	{
		ll.Insert( 0, i );
	}

	int t = -100;
	for ( int i=0; i<11; ++i )
	{
		ll.Delete( ll.Length()-1, t );
		printf( "%d ", t );
		
		t = -100;
	}
	printf( "\n" );

	return 0;
}

