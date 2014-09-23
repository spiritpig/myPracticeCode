// myStringClass.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

class myString
{
	char *data;
	size_t len, capacity;
	size_t baseFactor;

	void allocMemory( const size_t newSize );
	void adjustCapacity( const size_t newSize );

public:
	myString()
		:len(0), data( NULL ),
		 capacity( 0 ), baseFactor( 3 ) 
	{
		allocMemory( 0 );
	}

	void push_back( const char c );
	void push_back( const char *str );

	const char* getStr()
	{
		return data;
	}

	const size_t size() const
	{
		return len;
	}

	~myString()
	{
		if( data )
		{
			delete [] data;
		}
	}
};

void myString::push_back( const char c )
{
	data[len] = c;
	++len;
	// ���������ˣ����·����ڴ�
	if ( len >= capacity )
	{
		allocMemory( capacity+1 );
	}
}

void myString::push_back( const char *str )
{
	if( str == NULL )
	{
		return;
	}
	else
	{
		size_t strLen = strlen( str );
		if( strLen >= ( capacity-len ) )
		{
			allocMemory( strLen + capacity );
		}
		strcpy( &data[len], str );
		len += strLen;
	}
}

void myString::allocMemory( const size_t newSize )
{
	// ��һ�η�������
	if( newSize == 0 )
	{
		capacity = 2*2*2 - 1;
		data = new char[capacity];
	}
	else
	{
		adjustCapacity( newSize );
		if( data == NULL )
		{
			return;
		}

		char *pData = new char[capacity];
		strcpy( pData, data );
		
		delete [] data;
		data = pData;
	}
}

void myString::adjustCapacity( const size_t newSize )
{
	if( capacity > newSize )
	{
		return;
	}

	size_t count = 0;
	size_t tempCapacity = capacity;

	// ������С��numʱ����������ֵ��
	// ֱ��������numֵ�󣬲Ź������µ�Ԫ��
	while ( tempCapacity <= newSize )
	{
		tempCapacity = ( tempCapacity + 1 ) * 2 - 1;
		++count;
	}

	baseFactor += count;
	capacity = tempCapacity;
}

int _tmain(int argc, _TCHAR* argv[])
{
	myString strNew;

	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );
	strNew.push_back( "123456789" );

	std::cout << strNew.getStr() << std::endl;

	return 0;
}

