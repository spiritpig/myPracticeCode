// firstConsoleCpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

char* myStrcpy( char * const dest, const char * const src )
{
	if( dest == src )
	{
		return dest;
	}
	else
	{
		int index = 0;
		if( dest > src )
		{
			int srcLen = 0;
			while( src[srcLen] != '\0' ) 
			{
				++srcLen;
			}

			for( index = srcLen; index > -1; --index )
			{
				dest[index] = src[index];
			}
		}
		else
		{
			while( ( dest[index] = src[index] ) != '\0' )
			{
				++index;
			}
		}
	}

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
		int index = 0;
		while( str1[index] != '\0' ||
			   str2[index] != '\0' )
		{
			if( str1[index] > str2[index] )
			{
				return 1;
			}
			else
			{
				if( str1[index] < str2[index] )
				{
					return -1;
				}
			}

			++index;
		}
	}

	return 0;
}

size_t myStrlen( const char * const str )
{
	size_t len = 0;
	while( str[len] != '\0' )
	{
		++len;
	}

	return len;
}

char* myStrcat( char * const dest, const char * const src )
{
	size_t destLen = myStrlen( dest );

	size_t index = 0;
	while ( ( dest[index+destLen] = src[index] ) != '\0' )
	{
		++index;
	}
	
	return dest;
}

int myMemcmp( const void * const dest, const void * src, const size_t count )
{
	if( dest == src )
	{
		return 0;
	}
	else
	{
		const char * const pDest = ( const char * const )dest;
		const char * const pSrc = ( const char * const )src;

		for( size_t index = 0; index < count; ++index )
		{
			if( pDest[index] > pSrc[index] )
			{
				return 1;
			}
			else
			{
				if( pDest[index] < pSrc[index] )
				{
					return -1;
				}
			}
		}
	}

	return 0;
}

int main(void)
{
	char a[100] = "bB6789";
	char b[100] = "abcdefghijklmn";

	printf( "%d\n", myStrcmp( a, b ) );
	printf( "%s\n", myStrcat( a, b ) );
	printf( "%s\n", myStrcpy( a, b ) );

	printf( "%s\n", a );
	printf( "%s\n", b );

	printf( "%d\n", myStrlen( a ) );
	printf( "%d\n", myStrlen( b ) );

	short sa[10] = {1,2,3,4,5,6,7,8,9,10};
	short sb[10] = {1,2,3,4,5,6,7,8,9,10};
	printf( "%d\n", myMemcmp( sa, sb, 10 ) );

	return 0;
}