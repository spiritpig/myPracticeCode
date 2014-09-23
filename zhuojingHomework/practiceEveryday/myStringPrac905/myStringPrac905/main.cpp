#include <stdio.h>
#include <string.h>
#include <vld.h>

class myString
{
public:
	myString();
	myString( const char *str );
	myString( const myString &other );
	~myString();

	myString& operator =( const char *str );
	myString& operator =( const myString &other );

	const char * const getStr() const;

private:
	char *m_Str;
};

myString::myString()
{
	m_Str = NULL;
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
	if ( m_Str != NULL )
	{
		delete [] m_Str;
		m_Str = NULL;
	}
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

const char * const myString::getStr() const
{
	return m_Str;
}

int main(int, char **)
{
	myString ms1,
		ms2( "nihaowoshizhu" ),
		ms3 = ms2,
		ms4;

	ms4 = ms2;
	ms1 = "douqusiba";

	printf( "%s\n", ms1.getStr() );
	printf( "%s\n", ms2.getStr() );
	printf( "%s\n", ms3.getStr() );
	printf( "%s\n", ms4.getStr() );

	return 0;
}