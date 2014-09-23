//
//	说明： 重写mem有关的四个函数 memcpy、memcmp、memset、memmove
//
//	日期： 2014.08.05
//
//	作者： 陈少滨
//

#include "stdafx.h"
#include <Windows.h>
#pragma comment( lib, "winmm.lib" )

/*
void* myMemcpy( void *dest, const void *src, size_t count )
{
if( dest == src )
{
return dest;
}

int *destPtr = ( int * )dest;
const int *srcPtr = ( const int * )src;

// 以4个字节为一块
// 处理整块整块赋值的情况
size_t blockNum = count/4;
size_t i = 0;
while ( i < blockNum )
{
destPtr[i] = srcPtr[i];
++i;
}


char *destPtrChar = ( char * )&destPtr[i];
const char *srcPtrChar = ( const char * )&srcPtr[i];

size_t leftByteNum = count - blockNum*4;
for ( size_t j = 0; j < leftByteNum; ++j )
{
destPtrChar[j] = srcPtrChar[j];
}

return dest;
}


void* myMemcpy( void *dest, const void *src, size_t count )
{
if( dest == src )
{
return dest;
}

char *destPtr = ( char * )dest;
const char *srcPtr = ( const char * )src;

// 以4个字节为一块
// 处理整块整块赋值的情况
size_t blockNum = count/4;
size_t i = 0;
while ( i < blockNum )
{
(*(int*)destPtr) = (*(int*)srcPtr);

destPtr += 4;
srcPtr += 4;
++i;
}

size_t leftByteNum = count - blockNum*4;
for ( size_t j = 0; j < leftByteNum; ++j )
{
destPtr[j] = srcPtr[j];
}

return dest;
}


*/

//////////////////////////////////////////////////////////////////////////
//
//	myMemcpy_oneByte
//	
//	将从src开始的count个字节的值，复制到dest开始的count字节中
//	未解决内存区域重叠的问题
//
//	参数
//	
//		dest		目标内存区域的起始位置
//		src			原始内存区域的起始位置
//		count		需要复制的字节数
//
//	返回值
//
//		目标内存区域的首地址
//
//////////////////////////////////////////////////////////////////////////
void* myMemcpy_oneByte( void *dest, const void *src, size_t count )
{
	char *destPtr = ( char * )dest;
	const char *srcPtr = ( const char * )src;

	// 以4个字节为一块
	// 处理整块整块赋值的情况
	for ( size_t i = 0; i < count; ++i )
	{
		destPtr[i] = srcPtr[i];
	}

	return dest;
}

//////////////////////////////////////////////////////////////////////////
//
//	myMemmove
//	
//	将从src开始的count个字节的值，复制到dest开始的count字节中。
//	解决了内存区域重叠的问题
//
//	参数
//	
//		dest		目标内存区域的起始位置
//		src			原始内存区域的起始位置
//		count		需要复制的字节数
//
//	返回值
//
//		目标内存区域的首地址
//
//////////////////////////////////////////////////////////////////////////
void* myMemmove( void *dest, const void *src, size_t count )
{
	if( dest == src )
	{
		return dest;
	}

	char *destPtr = (char *)dest;
	const char *srcPtr = ( const char * )src;

	// 为了解决内存区域重叠的问题，分情况采取两种
	// 赋值的方式
	if( destPtr > srcPtr )
	{
		for( int i = (int)(count - 1); i > -1; --i )
		{
			destPtr[i] = srcPtr[i];
		}
	}
	else
	{
		for( size_t i = 0; i < count; ++i )
		{
			destPtr[i] = srcPtr[i];
		}
	}

	return dest;
}


//////////////////////////////////////////////////////////////////////////
//
//	myMemcmp
//	
//	比较从src开始的count个字节的值和dest开始的count字节的值的关系
//	大小关系按照我们先比较的字节为准。
//
//	参数
//	
//		buf1		比较的其中一个内存区域的首地址
//		buf2		比较的其中一个内存区域的首地址
//		count		比较的字节数
//
//	返回值
//
//		buf1 > buf2,  返回1
//		buf1 < buf2,  返回-1
//      buf1 == buf2, 返回0
//
//////////////////////////////////////////////////////////////////////////
int myMemcmp( const void *buf1, const void *buf2, size_t count )
{
	const char *buf1Ptr = ( const char * )buf1;
	const char *buf2Ptr = ( const char * )buf2;
	
	for( size_t i = 0; i < count; ++i )
	{
		if( buf1Ptr[i] > buf2Ptr[i] )
		{
			return 1;
		}
		else
		if( buf1Ptr[i] < buf2Ptr[i] )
		{
			return -1;
		}
	}

	// 只有全部都相等才可以返回相等
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//	myMemset
//	
//	按字节将从dest开始的count个字节赋值为c的值
//
//	参数
//	
//		dest	目标内存区域的首地址
//		c		每个字节赋予的值
//		count	需要赋值的字节数
//
//	返回值
//
//		buf1 > buf2,  返回1
//		buf1 < buf2,  返回-1
//      buf1 == buf2, 返回0
//////////////////////////////////////////////////////////////////////////
void* myMemset( void *dest, int c, size_t count )
{
	char *destPtr = ( char * )dest;
	char v = c;

	for( size_t i = 0; i < count; ++i )
	{
		destPtr[i] = v;
	}

	return dest;
}


void* myMemcpy( void *dest, const void *src, size_t count )
{
	if( dest == src )
	{
		return dest;
	}

	int *destPtr = ( int * )dest;
	const int *srcPtr = ( const int * )src;

	// 以4个字节为一块
	// 处理整块整块赋值的情况
	size_t blockNum = count/4;
	size_t i = 0;
	while ( i < blockNum )
	{
		destPtr[i] = srcPtr[i];
		++i;
	}


	char *destPtrChar = ( char * )&destPtr[i];
	const char *srcPtrChar = ( const char * )&srcPtr[i];

	size_t leftByteNum = count - blockNum*4;
	for ( size_t j = 0; j < leftByteNum; ++j )
	{
		destPtrChar[j] = srcPtrChar[j];
	}

	return dest;
}

#define MAX 100000

int _tmain( void )
{	
	int *a = new int[MAX*100];
	int *b = new int[MAX*100];

	int f = GetTickCount();	
	myMemcpy( b, a, sizeof( int ) * MAX * 100 );
	printf( "一字节， 用了多少时间\t%d\n", GetTickCount() - f );

	f = GetTickCount();	
	myMemcpy_oneByte( b, a, sizeof( int ) * MAX * 100 );
	printf( "块， 用了多少时间\t%d\n", GetTickCount() - f );
//	printf( "%d\n", myMemcmp( a, b, sizeof(int)*10 ) );

//	myMemset( b, 1, sizeof(int)*10 );
	for ( int i = 0; i < 10; ++i )
	{
		printf( "%d ", b[i] );
	}
	printf( "\n" );

	delete[] a;
	delete[] b;

	return 0;
}