// myStringPrac.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>

class myString
{
public:
	myString();
	myString( char *str );
	myString( char c, int count );
	myString( int num );
	myString( bool b );
	myString( const myString &other );
	~myString();

	const char* getStr();

private:
	char *m_str;
};

myString::myString()
{
	m_str = NULL;
}

myString::myString( char *str )
{
	if( str == NULL )
	{
		m_str = NULL;
	}
	else
	{
		m_str = new char[strlen(str) + 1];
		strcpy( m_str, str );
	}
}

myString::myString( char c, int count )
{
	m_str = new char[count + 1];
	memset( m_str, c, count );
	m_str[count] = '\0';
}

myString::myString( int num )  
{
	char temp[20] = "\0";
	itoa( num, temp, 10 );
	
	m_str = new char[strlen(temp) + 1];
	strcpy( m_str, temp );
}

myString::myString( bool b )
{
	if( b )
	{
		m_str = new char[5];
		strcpy( m_str, "true" );
	}
	else
	{
		m_str = new char[6];
		strcpy( m_str, "false" );
	}
}

myString::myString( const myString &other )
{
	if( other.m_str != NULL )
	{
		m_str = new char[strlen( other.m_str ) + 1];
		strcpy( m_str, other.m_str );
	}
	else
	{
		m_str = NULL;
	}
}

myString::~myString()
{
	if( m_str != NULL )
	{
		delete []m_str;
		m_str = NULL;
	}
}

const char* myString::getStr()
{
	return m_str;
}


int _tmain(int argc, _TCHAR* argv[])
{
	myString ms( "abcdjksldjaskld" );
	myString ms2( true );
	myString ms3( 'm', 100 );
	myString ms4( 192382942 );
	myString ms5( NULL );
	myString ms6( ms5 );
	myString ms7( ms );

	printf( "%s\n", ms.getStr() );
	printf( "%s\n", ms2.getStr() );
	printf( "%s\n", ms3.getStr() );
	printf( "%s\n", ms4.getStr() );
	printf( "%s\n", ms5.getStr() );
	printf( "%s\n", ms6.getStr() );
	printf( "%s\n", ms7.getStr() );

	return 0;
}