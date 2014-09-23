#include "StdAfx.h"

myString::myString()
{
	m_Str = NULL;
}

myString::myString( const char *str )
{
	if ( str != NULL )
	{
		m_Str = new char[strlen(str) + 1];
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
	SAFE_DELARR( m_Str );
}

myString& myString::operator =( const char *str )
{
	if ( m_Str != NULL )
	{
		SAFE_DELARR( m_Str );
	}

	if ( str != NULL )
	{
		m_Str = new char[strlen(str) + 1];
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
		m_Str = new char[strlen(other.m_Str) + 1];
		strcpy( m_Str, other.m_Str );
	}

	return *this;
}