// jiecheng.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int func( int n )
{
	if ( n > 1 )
	{
		return n*func( n-1 );
	}
	else
	{
		return 1;
	}
}

template<class T>
bool binarySearch( T *pData, const T &key, int right, int left= 0 )
{
	int mid;
	while ( left < right )
	{
		mid = (left + right)/2;

		if ( pData[mid] == key )
		{
			return true;
		}
		else
		if ( pData[mid] > key )
		{
			right = mid-1;
		}
		else
		{
			left = mid+1;
		}
	}

	return false;
}

int houzi( int n, int m )
{
	bool *isIn = new bool[n];
	memset( isIn, 1, sizeof(bool) );

	int curI = m%n;
	while ( isIn[curI] )
	{
		isIn[curI] = false;
		curI = (curI + m)%n;
	}

	delete []isIn;
	return curI+1;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int a[] = { 1,2,3,4,5,6,7,8,9,10 };
	if ( binarySearch( a, -1, 10 ) )
	{
		printf( "找到\n" );
	}

	printf ( "%d \n", houzi(3, 2));
	//printf( "%d \n", func(10) );
	return 0;
}

