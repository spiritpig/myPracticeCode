// linkedList-prac831.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	linkedList<int> lln;

	lln.append( 10 );

	lln.insert( 923, 1 );

	lln.append( 1 );
	lln.append( 20 );
	lln.append( 20 );
	lln.append( 20 );
	lln.append( 3 );

	lln.insert( 15, 1 );
	lln.insert( 1222, 3 );
	lln.insert( 332323, lln.getSize() );
	lln.insert( 332323, lln.getSize() );

	int val = -1;
	if( lln.find( lln.getSize()-2, val ) )
	{
		printf( "find: %d \n", val );
	}
	else
	{
		printf( "find error!\n" );
	}

	printf( "index: %d\n", lln.search( 3 ) );

	//lln.remove( lln.getSize() );
	//printf( "%d\n", lln.getSize() );
	//lln.remove( lln.getSize() );
	//printf( "%d\n", lln.getSize() );
	//lln.remove( lln.getSize() );
	//printf( "%d\n", lln.getSize() );
	//lln.remove( lln.getSize() );
	//printf( "%d\n", lln.getSize() );
	//lln.remove( lln.getSize() );
	//printf( "%d\n", lln.getSize() );
	//lln.remove( lln.getSize() );
	//printf( "%d\n", lln.getSize() );
	//lln.remove( lln.getSize() );
	//printf( "%d\n", lln.getSize() );

	return 0;
}
