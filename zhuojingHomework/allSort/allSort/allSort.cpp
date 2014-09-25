// allSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

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
	int a[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	outputArray( a, 10 );

	insertSort( a, 10, true );
	outputArray( a, 10 );

	return 0;
}

