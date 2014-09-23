// myStringPrac827.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class myString
{
	myString();
	myString( const myString &other );
	myString( const char *str );
	myString( char c, int count );
	myString& operator =( const myString &other );
	myString& operator =( const char *str );
	~myString();

private:
	char *m_Str;
};

myString::myString()
{
	m_Str = NULL;
}

myString::myString( const myString &other )
{
	if( other.m_Str != NULL )
	{
		this->m_Str = new char[strlen(other.m_Str)+1];
		strcpy( this->m_Str, other.m_Str );
	}
	else
	{
		this->m_Str = NULL;
	}
}

myString::myString( const char *str )
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
	m_Str = new char[strlen(count)+1];

	int i=0;
	for ( i; i<count; ++i )
	{
		m_Str[i] = c;
	}
	m_Str[i] = '\0';
}

myString& myString::operator=( const myString &other )
{
	if( this->m_Str != NULL )
	{
		delete [] this->m_Str;
		this->m_Str = NULL;
	}

	if ( other.m_Str != NULL )
	{
		m_Str = new char[strlen(other.m_Str)+1];
		strcpy( m_Str, other.m_Str );
	}

	return *this;
}

myString& myString::operator=( const char *str )
{
	if( this->m_Str != NULL )
	{
		delete [] this->m_Str;
		this->m_Str = NULL;
	}

	if( str != NULL )
	{
		m_Str = new char[strlen(str)+1];
		strcpy( m_Str, str );
	}

	return *this;
}

myString::~myString()
{
	if( m_Str != NULL )
	{
		delete [] m_Str;
		m_Str = NULL;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}


