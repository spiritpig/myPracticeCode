// heapTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "heap.h"

#define UPPER_VAL 100

int _tmain(int argc, _TCHAR* argv[])
{
	srand( (unsigned int)time( NULL ) );

	heap<int> hi;
	int temp = -1;
	for ( int i=0; i< 10; ++i )
	{
		temp = rand()%UPPER_VAL+1;
		printf( "添加 %d\n", temp );
		hi.add( temp );
	}
	printf( "\n" );

	int t = 0;
	while ( hi.remove_Top( t ) )
	{
		printf( "删除: %d\n", t );
	}
	printf( "\n" );

	return 0;
}

