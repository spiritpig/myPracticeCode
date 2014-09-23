// msfpe912.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void* myMemcpy( void * const dest, const void * const src, size_t count )
{
	if( dest == src )
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
	if( dest == src )
	{
		return dest;
	}
	else
	{
		char * const pDest = ( char * const )dest;
		const char * const pSrc = ( const char * const )src;

		if( dest < src )
		{
			for ( size_t i=0; i<count; ++i )
			{
				pDest[i] = pSrc[i];
			}
		}
		else
		{
			for ( int i=(int)count-1; i>-1; --i )
			{
				pDest[i] = pSrc[i];
			}
		}
	}

	return dest;
}

void* myMemset( void * const dest, int c , size_t count )
{
	char * const pDest = ( char * const )dest;
	char cc = c;
	for ( size_t i=0; i<count; ++i )
	{
		pDest[i] = cc;
	}

	return dest;
}

int myMemcmp( const void * const buf1, const void * const buf2, size_t count )
{
	if( buf1 == buf2 )
	{
		return 0;
	}
	else
	{
		const char * const pBuf1 = ( const char * const )buf1;
		const char * const pBuf2 = ( const char * const )buf2;
		for ( size_t i=0; i>count; ++i)
		{
			if ( pBuf1[i] > pBuf2[i] )
			{
				return 1;
			}
			else
			{
				if ( pBuf1[i] < pBuf2[i] )
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
	if( dest == src )
	{
		return dest;
	}
	else
	{
		size_t index = 0;
		while ( (dest[index] = src[index]) != '\0' )
		{
			++index;
		}
	}

	return dest;
}

char* myStrmove( char * const dest, const char * const src )
{
	if( dest == src )
	{
		return dest;
	}
	else
	{
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
			static int srcLen;
			srcLen = (int)myStrlen(src);
			for ( int i=srcLen; i>-1; --i )
			{
				dest[i] = src[i];
			}
				
		}
	}

	return dest;
}

char* myStrcat( char * const dest, const char * const src )
{
	static size_t destLen = myStrlen( dest );
	static size_t index = 0;
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
	else
	{
		size_t index = 0;
		while ( (str1[index] != '\0') || 
				(str2[index] != '\0') )
		{
			if ( str2[index] < str1[index] )
			{
				return 1;
			}
			else
			{
				if ( str2[index] > str1[index] )
				{
					return -1;
				}
			}
			++index;
		}
	}

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

