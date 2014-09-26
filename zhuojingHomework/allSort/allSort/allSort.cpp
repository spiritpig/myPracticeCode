// allSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>
#pragma comment( lib, "winmm.lib" )

#define SAFE_DELARR(p) {if(p) {delete []p;p=0;}}

template<class T>
void Swap( T &a, T &b )
{
	T temp = a;
	a = b;
	b = temp;
}

template<class T>
void bubbleSort( T *a, int n, bool isUp = true )
{
	bool isOver = true;
	if ( isUp )
	{
		for ( int i=n-1; i>0; --i )
		{
			isOver = true;
			for ( int j=0; j<i; ++j )
			{
				if ( a[j] > a[j+1] )
				{
					Swap( a[j], a[j+1] );
					isOver = false;
				}
			}

			if ( isOver )
			{
				break;
			}
		}
	}
	else
	{
		for ( int i=n-1; i>0; --i )
		{
			isOver = true;
			for ( int j=0; j<i; ++j )
			{
				if ( a[j] < a[j+1] )
				{
					Swap( a[j], a[j+1] );
					isOver = false;
				}
			}

			if ( isOver )
			{
				break;
			}
		}
	}
}

template<class T>
void selectSort( T *a, int n, bool isUp = true )
{
	if ( isUp )
	{
		for ( int i=0; i<n-1; ++i )
		{
			for ( int j=i+1; j<n; ++j )
			{
				if ( a[i] > a[j])
				{
					Swap( a[i], a[j] );
				}
			}
		}	
	}
	else
	{
		for ( int i=0; i<n-1; ++i )
		{
			for ( int j=i+1; j<n; ++j )
			{
				if ( a[i] < a[j])
				{
					Swap( a[i], a[j] );
				}
			}
		}
	}
}

template<class T>
void insertSort( T *a, int n, bool isUp = true )
{
	T temp;
	int j=0;

	if ( isUp )
	{
		for ( int i=1; i<n; ++i )
		{
			temp = a[i];

			j = i-1;
			while ( a[j]>temp && j>-1 )
			{
				a[j+1] = a[j];
				--j;
			}

			a[j+1] = temp;
		}
	}
	else
	{
		for ( int i=1; i<n; ++i )
		{
			temp = a[i];

			j = i-1;
			while ( a[j]<temp && j>-1 )
			{
				a[j+1] = a[j];
				--j;
			}

			a[j+1] = temp;
		}
	}
}

template<class T>
void mergeSort( T *pData, int n, bool isUp = true )
{
	if ( n > 1 )
	{
		mergeSort( pData, n>>1, isUp );
		mergeSort( pData + (n>>1), n - (n>>1), isUp );

		static int aSize;
		static int aPos;
		static int bPos;
		static int tempArrPos;
		static T *pTempArr;

		pTempArr = new T[n];

		aSize = n>>1;
		aPos = 0;
		bPos = aSize;
		tempArrPos = 0;
		while ( (aPos < aSize) && (bPos < n) )
		{
			if ( pData[aPos] < pData[bPos] )
			{
				pTempArr[tempArrPos] = pData[aPos];
				++tempArrPos;
				++aPos;
			}
			else
			{
				pTempArr[tempArrPos] = pData[bPos];
				++tempArrPos;
				++bPos;
			}
		}

		while ( aPos < aSize )
		{
			pTempArr[tempArrPos] = pData[aPos];
			++tempArrPos;
			++aPos;
		}

		while ( bPos < n )
		{
			pTempArr[tempArrPos] = pData[bPos];
			++tempArrPos;
			++bPos;
		}

		for ( int i=0; i<n; ++i )
		{
			pData[i] = pTempArr[i];
		}

		SAFE_DELARR( pTempArr );
	}
}

template<class T>
void shellSort( T *a, int n, bool isUp = true )
{
	int step=n/2;
	int j = 0;
	T key;

	while ( step > 0 )
	{
		for ( int i=step; i<n; ++i )
		{
			j = i-step;
			key = a[i];
			while ( (j>-1) && (a[j]>key) )
			{
				a[j+step] = a[j];

				j -= step;
			}

			a[j+step] = key;
		}
	
		step /= 2;
	}
}

void outputArray( const int *a, int n )
{
	for ( int i=0; i<n; ++i )
	{
		printf( "%d ", a[i] );
	}
	printf( "\n" );
}

int _tmain(int argc, _TCHAR* argv[])
{
	int *a = new int[10000000];
	for ( int i=0; i<10000000; ++i )
	{
		a[i] = rand()*220 % 154932;
	}
//	outputArray( a, 100 );
	printf( "\n\n\n" );

 	double t = timeGetTime()/1000.0;
 	shellSort( a, 10000000, true );
 	printf( "时间: %f", timeGetTime()/1000.0 - t );
//	outputArray( a, 100 );
	printf( "\n" );

	SAFE_DELARR( a );

	return 0;
}

