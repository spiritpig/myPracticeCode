#include "stdafx.h"

size_t myStrlen( const char * const str )
{
	size_t len = 0;
	while( str[len] != '\0' )
	{
		++len;
	}

	return len;
}

char* myStrcpy( char * const dest, const char * const src )
{
	if( dest == src )
	{
		return dest;
	}
	else
	{
		if( dest > src )
		{
			size_t srcLen = myStrlen( src );
			for( int i = (int)srcLen; i > -1; --i )
			{
				dest[i] = src[i];
			}
		}
		else
		{
			size_t i = 0;
			while ( ( dest[i] = src[i] ) != '\0' )
			{
				++i;
			}
		}
	}

	return dest;
}

char* myStrcat( char * const dest, const char * const src )
{
	size_t destLen = myStrlen( dest );
	size_t srcLen = myStrlen( src );
	for ( int i = (int)srcLen; i > -1; --i )
	{
		dest[destLen+i] = src[i];
	}

	/*
	while ( ( dest[destLen+i] = src[i] ) != '\0' )
	{
	++i;
	}*/

	return dest;
}

int myStrcmp( const char * const str1, const char * const str2 )
{
	if( str1 == str2 )
	{
		return 0;
	}
	else
	{
		size_t i = 0;
		while ( str1[i] != '\0' ||
				str2[i] != '\0' )
		{
			if( str1[i] > str2[i] )
			{
				return 1;
			}
			else
			{
				if( str1[i] < str2[i] )
				{
					return -1;
				}
			}

			++i;
		}

		return 0;
	}
}

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

		for ( size_t i = 0; i < count; ++i )
		{
			pDest[i] = pSrc[i];
		}
	}

	return dest;
}

int main( void )
{
	char a[100] = "bB6789";
	char b[100] = "abcdefghijklmn";

	printf( "%d\n", myStrcmp( a, b ) );
	printf( "%s\n", myStrcat( a, b ) );
	printf( "cpy: %s\n", myStrcpy( &a[3], a ) );
	printf( "cpy: %s\n", myStrcpy( a, &a[2] ) );

	printf( "%s\n", a );
	printf( "%s\n", b );

	printf( "%d\n", myStrlen( a ) );
	printf( "%d\n", myStrlen( b ) );

	return 0;
}