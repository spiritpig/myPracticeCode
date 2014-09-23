// myStringPrac828.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>

class myString
{
public:
	myString();
	myString( const char * const str );
	myString( char c, int count );
	myString( const myString &other );
	~myString();

	myString& operator=( const myString &other );
	myString& operator=( const char *str );

	char* getStr()
	{
		return m_Str;
	}

private:
	char *m_Str;
};

myString::myString()
{
	m_Str = NULL;
}

myString::myString( const char * const str )
{
	if( str != NULL )
	{
		m_Str = new char[strlen(str)+1];
		strcpy( m_Str, str );
	}
	else
	{
		m_Str = NULL;
	}
}

myString::myString( char c, int count )
{
	m_Str = new char[count+1];

	int i = 0;
	for ( i; i<count; ++i )
	{
		m_Str[i] = c;
	}
	m_Str[i] = '\0';
}


myString::myString( const myString &other )
{
	if( other.m_Str != NULL )
	{
		m_Str = new char[strlen(other.m_Str)+1];
		strcpy( m_Str, other.m_Str );
	}
	else
	{
		m_Str = NULL;
	}
}

myString::~myString()
{
	if( m_Str != NULL )
	{
		delete [] m_Str;
		m_Str = NULL;
	}
}

myString& myString::operator=( const myString &other )
{
	if( m_Str != NULL )
	{
		delete [] m_Str;
		m_Str = NULL;
	}

	if ( other.m_Str != NULL )
	{
		m_Str = new char[strlen(other.m_Str)+1];
		strcpy( m_Str, other.m_Str );
	}

	return *this;
}

myString& myString::operator=( const char * str )
{
	if( m_Str != NULL )
	{
		delete [] m_Str;
		m_Str = NULL;
	}

	if ( str != NULL )
	{
		m_Str = new char[strlen(str)+1];
		strcpy( m_Str, str );
	}

	return *this;
}

int _tmain(int argc, _TCHAR* argv[])
{
	myString m s;
	myString ms1( "123467" );
	myString ms2( ms1 );
	myString ms3 = ms2;
	myString ms4( 'f', 100 );

	ms = ms2;

	printf( "%s\n", ms.getStr() );
	printf( "%s\n", ms1.getStr() );
	printf( "%s\n", ms2.getStr() );
	printf( "%s\n", ms3.getStr() );
	printf( "%s\n", ms4.getStr() );

	return 0;
}

