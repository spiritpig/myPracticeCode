//
//	˵���� ��дmem�йص��ĸ����� memcpy��memcmp��memset��memmove
//
//	���ڣ� 2014.08.05
//
//	���ߣ� ���ٱ�
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

// ��4���ֽ�Ϊһ��
// �����������鸳ֵ�����
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

// ��4���ֽ�Ϊһ��
// �����������鸳ֵ�����
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
//	����src��ʼ��count���ֽڵ�ֵ�����Ƶ�dest��ʼ��count�ֽ���
//	δ����ڴ������ص�������
//
//	����
//	
//		dest		Ŀ���ڴ��������ʼλ��
//		src			ԭʼ�ڴ��������ʼλ��
//		count		��Ҫ���Ƶ��ֽ���
//
//	����ֵ
//
//		Ŀ���ڴ�������׵�ַ
//
//////////////////////////////////////////////////////////////////////////
void* myMemcpy_oneByte( void *dest, const void *src, size_t count )
{
	char *destPtr = ( char * )dest;
	const char *srcPtr = ( const char * )src;

	// ��4���ֽ�Ϊһ��
	// �����������鸳ֵ�����
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
//	����src��ʼ��count���ֽڵ�ֵ�����Ƶ�dest��ʼ��count�ֽ��С�
//	������ڴ������ص�������
//
//	����
//	
//		dest		Ŀ���ڴ��������ʼλ��
//		src			ԭʼ�ڴ��������ʼλ��
//		count		��Ҫ���Ƶ��ֽ���
//
//	����ֵ
//
//		Ŀ���ڴ�������׵�ַ
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

	// Ϊ�˽���ڴ������ص������⣬�������ȡ����
	// ��ֵ�ķ�ʽ
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
//	�Ƚϴ�src��ʼ��count���ֽڵ�ֵ��dest��ʼ��count�ֽڵ�ֵ�Ĺ�ϵ
//	��С��ϵ���������ȱȽϵ��ֽ�Ϊ׼��
//
//	����
//	
//		buf1		�Ƚϵ�����һ���ڴ�������׵�ַ
//		buf2		�Ƚϵ�����һ���ڴ�������׵�ַ
//		count		�Ƚϵ��ֽ���
//
//	����ֵ
//
//		buf1 > buf2,  ����1
//		buf1 < buf2,  ����-1
//      buf1 == buf2, ����0
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

	// ֻ��ȫ������Ȳſ��Է������
	return 0;
}


//////////////////////////////////////////////////////////////////////////
//
//	myMemset
//	
//	���ֽڽ���dest��ʼ��count���ֽڸ�ֵΪc��ֵ
//
//	����
//	
//		dest	Ŀ���ڴ�������׵�ַ
//		c		ÿ���ֽڸ����ֵ
//		count	��Ҫ��ֵ���ֽ���
//
//	����ֵ
//
//		buf1 > buf2,  ����1
//		buf1 < buf2,  ����-1
//      buf1 == buf2, ����0
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

	// ��4���ֽ�Ϊһ��
	// �����������鸳ֵ�����
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
	printf( "һ�ֽڣ� ���˶���ʱ��\t%d\n", GetTickCount() - f );

	f = GetTickCount();	
	myMemcpy_oneByte( b, a, sizeof( int ) * MAX * 100 );
	printf( "�飬 ���˶���ʱ��\t%d\n", GetTickCount() - f );
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