// linkedlistPrac921.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	linkedList<int> mlist;

	mlist.Insert( 0, 100 );	
	for ( int i=0; i<10; ++i )
	{
		mlist.Insert( mlist.Length()-1, i );
	}
	/*
		1, 0
		2, 1
		3, 2
	*/
/*
	int t = -1;
	while ( !mlist.IsEmpty() )
	{
		mlist.Delete( 1, t );
		printf( "%d ", t );
	}
	printf( "\n" );
*/
	return 0;
}

