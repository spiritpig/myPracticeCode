#include "StdAfx.h"

myString::myString(void)
: m_Str( NULL )
{
}


myString::myString( char c, int count )
{
	m_Str = new char[count+1];

	int i=0;
	for ( i; i<count; ++i )
	{
		m_Str[i] = c;
	}
	m_Str[i] = '\0';
}


myString::myString( const char * const str )
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

myString::~myString(void)
{
	SAFE_DELARR( m_Str );
}


myString myString::operator +( const char * const str )
{
	myString temp;
	if( str != NULL )
	{
		char *pTemp = new char[strlen(str)+strlen(m_Str)+1];
		strcpy( pTemp, m_Str );
		strcat( pTemp, str );

		temp.setStr( pTemp );
	}
	else
	{
		temp = m_Str;
	}

	return temp;
}

myString myString::operator +( const myString &other )
{
	myString temp;
	if( other.getStr() != NULL )
	{
		char *pTemp = new char[strlen(other.getStr())+strlen(m_Str)+1];
		strcpy( pTemp, m_Str );
		strcat( pTemp, other.getStr() );

		temp.setStr( pTemp );
	}
	else
	{
		temp = m_Str;
	}

	return temp;
}

myString& myString::operator =( const char * const str )
{
	if ( m_Str != NULL )
	{
		SAFE_DELARR( m_Str );
	}

	if ( str != NULL )
	{
		m_Str = new char[strlen(str)+1];
		strcpy( m_Str, str );
	}

	return *this;
}

myString& myString::operator =( const myString &other )
{
	if ( m_Str != NULL )
	{
		SAFE_DELARR( m_Str );
	}

	if ( other.m_Str != NULL )
	{
		m_Str = new char[strlen(other.m_Str)+1];
		strcpy( m_Str, other.m_Str );
	}

	return *this;
}

const char * const myString::getStr() const
{
	return m_Str;
}

void myString::setStr( char *str )
{
	SAFE_DELARR( m_Str );
	m_Str = str;
}
