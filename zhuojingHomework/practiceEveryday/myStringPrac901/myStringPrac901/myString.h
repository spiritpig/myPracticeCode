#include "stdafx.h"

#ifndef MYSTRING_AFX
#define MYSTRING_AFX

#define SAFE_DELARR(p)	\
{						\
	if( p != NULL )		\
	{					\
		delete [] p;	\
		p = NULL;		\
	}					\
}						\

class myString
{
public:
	myString(void);
	myString( char c, int count );
	myString( const char * const str );
	myString( const myString &other );
	~myString(void);

	myString  operator +( const char * const str );
	myString  operator +( const myString &other );
	myString& operator =( const char * const str );
	myString& operator =( const myString &other );

	const char * const getStr() const;
	void setStr( char *str );

private:
	char *m_Str;
};

#endif // END MYSTRING_AFX