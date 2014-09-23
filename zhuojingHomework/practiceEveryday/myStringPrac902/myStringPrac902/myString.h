#ifndef MYSTRING_AFX
#define MYSTRING_AFX

class myString
{
public:
	myString();
	myString( const char *str );
	myString( const myString &other );
	~myString();

	myString& operator =( const char *str );
	myString& operator =( const myString &other );

	const char * const getStr() const
	{
		return m_Str;
	}

private:
	char *m_Str;
};

#endif // END MYSTRING_AFX