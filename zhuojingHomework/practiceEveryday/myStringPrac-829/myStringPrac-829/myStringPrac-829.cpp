// myStringPrac-829.cpp : 定义控制台应用程序的入口点。 
//

#include "stdafx.h"
#include <vld.h>

class myString
{
public:
	myString();
	myString( char c, int num );
	myString( const char *str );
	myString( const myString &other );
	~myString();

	myString& operator =( const myString &other );
	myString& operator =( const char *str );

	const char * const getStr()
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

myString::myString( char c, int num )
{
	m_Str = new char[num+1];

	int i=0;
	for ( i; i<num; ++i )
	{
		m_Str[i] = c;
	}
	m_Str[i] = '\0';
}

myString::myString( const char *str )
{
	if ( str != NULL )
	{
		m_Str = new char[strlen(str)+1];
		strcpy( m_Str, str );
	}
	else
	{
		m_Str = NULL;
	}
}

myString::myString( const myString &other )
{
	if ( other.m_Str != NULL )
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

myString& myString::operator =( const myString &other )
{
	if( m_Str != NULL ) 
	{
		delete [] m_Str;
		m_Str = NULL;
	}

	if( other.m_Str != NULL )
	{
		m_Str = new char[strlen(other.m_Str)+1];
		strcpy( m_Str, other.m_Str );
	}

	return *this;
}
myString& myString::operator =( const char *str )
{
	if( m_Str != NULL ) 
	{
		delete [] m_Str;
		m_Str = NULL;
	}

	if( str != NULL )
	{
		m_Str = new char[strlen(str)+1];
		strcpy( m_Str, str );
	}

	return *this;
}

int _tmain(int argc, _TCHAR* argv[])
{
	myString ms1,
			ms2( "nishadsodhosa" ),
			ms3( ms2 ),
			ms4( 'a', 20 );


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

