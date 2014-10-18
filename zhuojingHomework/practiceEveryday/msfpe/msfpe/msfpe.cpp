// msfpe.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

void* myMemcpy( void * const dest, const void * const src, size_t count )
{
	if ( dest == src )
	{
		return dest;
	}

	char * const pDest = ( char * const )dest;
	const char * const pSrc = ( const char * const )src;
	for ( size_t i=0; i<count; ++i )
	{
		pDest[i] = pSrc[i];
	}

	return dest;
}

void* myMemmove( void * const dest, const void * const src, size_t count )
{
	if ( dest == src )
	{
		return dest;
	}

	char * const pDest = ( char * const )dest;
	const char * const pSrc = ( const char * const )src;

	if ( dest < src )
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

	return dest;
}

void* myMemset( void * const dest, char c, size_t count )
{
	char * const pDest = ( char * const )dest;
	for ( size_t i=0; i<count; ++i )
	{
		pDest[i] = c;
	}

	return pDest;
}

int myMemcmp( const void * const buf1,  const void * const buf2, size_t count )
{
	if ( buf1 == buf2 )
	{
		return 0;
	}

	const char * const pBuf1 = ( const char * const )buf1;
	const char * const pBuf2 = ( const char * const )buf2;
	for ( size_t i=0; i<count; ++i )
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

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

