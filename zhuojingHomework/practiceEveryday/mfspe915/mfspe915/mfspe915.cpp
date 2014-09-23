// mfspe915.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void* myMemcpy( void * const dest, const void * const src, size_t count )
{
	if ( dest == src )
	{
		return dest;
	}
	else
	{
		char * const pDest = ( char * const )dest;
		const char * const pSrc = ( const char * const )src;

		for ( size_t i=0; i<count; ++i )
		{
			pDest[i] = pSrc[i];
		}
	}

	return dest;
}

void* myMemmove( void * const dest, const void * const src, size_t count )
{
	if ( dest == src )
	{
		return dest;
	}
	else
	{
		char * const pDest = ( char * const )dest;
		const char * const pSrc = ( const char * const )src;

		if ( dest > src )
		{
			for ( int i=(int)count-1; i>-1; --i )
			{
				pDest[i] = pSrc[i];
			}
		} 
		else
		{
			for ( size_t i=0; i<count; ++i )
			{
				pDest[i] = pSrc[i];
			}
		}
	}

	return dest;
}

void* myMemset( void * const dest, char c, size_t count )
{
	char * const pDest = ( char * const )dest;
	for ( size_t i=0; i<count; ++i )
	{
		pDest[i] = c;
	}

	return dest;
}

int myMemcmp( const void * const buf1, const void * const buf2, size_t count )
{
	if ( buf1 == buf2 )
	{
		return 0;
	}
	else
	{
		const char * const pBuf1 = ( const char * const )buf1;
		const char * const pBuf2 = ( const char * const )buf2;

		for ( size_t index=0; index<count; ++index )
		{
			if( pBuf1[index] > pBuf2[index] )
			{
				return 1;
			}
			else
			{
				if( pBuf1[index] < pBuf2[index] )
				{
					return -1;
				}
			}
		}
	}

	return 0;
}

size_t myStrlen( const char * const str )
{
	size_t len = 0;
	while ( str[len] != '\0' )
	{
		++len;
	}

	return len;
}

char* myStrcpy( char * const dest, const char * const src )
{
	if ( dest == src )
	{
		return dest;
	}

	size_t index = 0;
	while ( (dest[index] = src[index]) != '\0' )
	{
		++index;
	}

	return dest;
}

char* myStrmove( char * const dest, const char * const src )
{
	if ( dest == src )
	{
		return dest;
	}

	if ( dest < src )
	{
		size_t index = 0;
		while ( (dest[index] = src[index]) != '\0' )
		{
			++index;
		}
	} 
	else
	{
		for ( int i=(int)myStrlen(src); i>-1; --i )
		{
			dest[i] = src[i];
		}
	}

	return dest;
}

char* myStrcat( char * const dest, const char * const src )
{
	size_t destLen = myStrlen( dest );
	size_t index = 0;
	while ( (dest[destLen+index] = src[index]) != '\0' )
	{
		++index;
	}

	return dest;
}

int myStrcmp( const char * const str1, const char * const str2 )
{
	if ( str1 == str2 )
	{
		return 0;
	}

	size_t index = 0;
	while ( (str1[index] != '\0') ||
			(str2[index] != '\0') )
	{
		if ( str1[index] > str2[index] )
		{
			return 1;
		}

		if ( str1[index] < str2[index] )
		{
			return -1;
		}

		++index;
	}

	return 0;
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
	int c[10] = { 1,2,3,4,5,6,7,8,9,10 };
	int d[10];

	myMemcpy( d, c, sizeof( int )*10 );
	outputArray( c, 10 );
	outputArray( d, 10 );

	printf( "%d\n", myMemcmp( c, d, sizeof( int )*10 ) );

	myMemmove( c, &c[2], sizeof( int )*8 );
	outputArray( c, 10 );

	myMemmove( &c[2], c, sizeof( int )*8 );
	outputArray( c, 10 );

	myMemset( d, 0, sizeof( int )*10 );
	outputArray( d, 10 );

	char a[100] = "123456789";
	char b[100] = "abcdefghijklmn";

	printf( "%d\n", myStrlen( a ) );
	printf( "%d\n", myStrlen( b ) );

	printf( "%s\n", myStrcat( b, a ) );

	printf( "%s\n", myStrmove( a, &a[2] ) );
	printf( "%s\n", a );
	printf( "%s\n", myStrmove( &a[2], a ) );
	printf( "%s\n", a );

	printf( "%d\n", myStrcmp( b, a ) );
	printf( "%s\n", myStrcpy( b, a ) );

	return 0;
}

