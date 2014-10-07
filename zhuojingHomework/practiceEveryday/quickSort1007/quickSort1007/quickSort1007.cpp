// quickSort1007.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using std::swap;

int partition( int *a, int left, int right )
{
	int key = a[left];
	int i = left;
	for ( int j=left+1; j<=right; ++j )
	{
		if ( a[j] < key )
		{
			++i;
			swap( a[j], a[i] );
		}
	}
	swap( a[i], a[left] );

	return i;
}

void quickSort( int *a, int left, int right )
{
	if ( left < right )
	{
		int q = partition( a, left, right );
		quickSort( a, left, q-1 );
		quickSort( a, q+1, right );
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = { 1,2,3,2323,5,64,142,8,9,-1 };
	quickSort(a, 0, 9);

	for ( int i=0; i<10; ++i )
	{
		printf( "%d ", a[i] );
	}
	printf( "\n" );

	return 0;
}

