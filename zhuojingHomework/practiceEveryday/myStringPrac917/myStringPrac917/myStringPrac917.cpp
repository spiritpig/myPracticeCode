// myStringPrac917.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string.h>
#include <vld.h>

class MyString
{
public:
	MyString();
	MyString( const char * const str );
	MyString( const MyString &other );
	~MyString();

//const MyString &other 
	MyString& operator =( const char * const str );
	MyString& operator =( const MyString &other );

	const char * const getStr() const
	{
		return m_Str;
	}

private:
	char *m_Str;
};

MyString::MyString()
{
	m_Str = NULL;
}

MyString::MyString( const char * const str )
: m_Str( NULL )
{
	if ( str != NULL )
	{
		m_Str = new char[strlen(str)+1];
		strcpy( m_Str, str );
	}
}

MyString::MyString( const MyString &other )
: m_Str( NULL )
{
	if ( other.m_Str!= NULL )
	{
		m_Str = new char[strlen(other.m_Str)+1];
		strcpy( m_Str, other.m_Str );
	}
}

MyString::~MyString()
{
	if ( m_Str != NULL )
	{
		delete [] m_Str;
		m_Str = NULL;
	}
}

MyString& MyString::operator =( const char * const str )
{
	if ( m_Str != NULL )
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

MyString& MyString::operator=( const MyString &other )
{
	if ( m_Str != NULL )
	{
		delete [] m_Str;
		m_Str = NULL;
	}

	if ( other.m_Str!= NULL )
	{
		m_Str = new char[strlen(other.m_Str)+1];
		strcpy( m_Str, other.m_Str );
	}

	return *this;
}

int _tmain(int argc, _TCHAR* argv[])
{
	MyString ms1,
		ms2( "nishadsodhosa" ),
		ms3( ms2 ),
		ms4 = ms1;

	ms1 = ms2;
	ms2 = "snvdisdnweiv";
	ms4 = NULL;

	printf( "%s\n", ms1.getStr() );
	printf( "%s\n", ms2.getStr() );
	printf( "%s\n", ms3.getStr() );
	printf( "%s\n", ms4.getStr() );

	ms4 = ms2;
	printf( "%s\n", ms4.getStr() );
	ms4 = "someoneStr";
	printf( "%s\n", ms4.getStr() );

	return 0;
}

