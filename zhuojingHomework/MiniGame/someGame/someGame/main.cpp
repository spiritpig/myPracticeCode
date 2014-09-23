// firstConsoleCpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#pragma comment( lib, "winmm.lib" )

//int myDivide( int bedivnum, int divnum )
//{
//	int count = 0;
//	while( bedivnum >= divnum )
//	{
//		bedivnum-=divnum;
//		++count;
//	}
//
//	return count;
//}
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	char dir = ' ';
//	if( kbhit() )
//	{
//		dir = getchar();
//	}
//
//	while( 1 )
//	{
//		switch ( dir )
//		{
//		case '\n':
//			{
//				cout << "检测到回车了!" << endl;
//			}
//			break;
//		}
//	}
//
//	return 0;
//}

void bubbleSort( int *a, int n )
{
	bool isSwaped = true;
	for( int i = 0; i < n - 1 && isSwaped; ++i )
	{
		isSwaped = false;
		for( int j = 0; j < n - 1 - i; ++j )
		{
			if( a[j] > a[j+1] )
			{
				int t = a[j];
				a[j]  = a[j+1];
				a[j+1] = t;

				isSwaped = true;
			}
		}
	}
}

int partition( int *a, const int &left, const int &right )
{
	int key = a[right];
	int i = left-1;
	for( int j = left; j < right; ++j )
	{
		if( a[j] < key )
		{
			++i;
			swap( a[j], a[i] );
		}
	}
	++i;
	swap( a[right], a[i] );

	return i;
}

void quickSort( int *a, const int  &left, const int &right )
{
	if( left < right )
	{
		int q = partition( a, left, right );
		quickSort( a, left, q-1 );
		quickSort( a, q+1, right );
	}
}

#define MAX 200000

int main(void)
{
	int *a = new int[MAX];

	for( int i = 0; i < MAX; ++i )
	{
		a[i] = rand();
	}

	float t = timeGetTime()/1000.0f;
	quickSort( a, 0, MAX-1 );
	printf( "%f\n", (timeGetTime()/1000.0f) - t );

	for ( int j = 0; j < 10; ++j )
	{
		printf( "%d ", a[j] );
	}
	printf( "\n\n" );

	// 测试快速排序的部分
	for( int i = 0; i < MAX; ++i )
	{
		a[i] = rand();
	}

	t = timeGetTime()/1000.0f;
	bubbleSort( a, MAX );
	printf( "%f\n", (timeGetTime()/1000.0f) - t );

	for ( int j = 0; j < 10; ++j )
	{
		printf( "%d ", a[j] );
	}
	printf( "\n" );

	delete[] a;
	return 0;
}