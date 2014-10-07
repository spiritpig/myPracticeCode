#ifndef MY_BASESTRING
#define MY_BASESTRING

#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }
#define GET_BIGGER_CAPACITY(a) ( a+a/2+1 )


template<class T>
class myBaseString
{
public:
	myBaseString();
	myBaseString( size_t count, const T &val );
	myBaseString( const T *str );
	myBaseString( const myBaseString &other );
	~myBaseString();

	void pop_back();
	void push_back( const T &val );
	T* c_Str() const
	{
		return m_pStr;
	}

private:
	size_t getStrLen( const T *str );
	void _realloc( size_t count );

	T *m_pStr;
	size_t m_Len;
	size_t m_Capacity;
};

template<class T>
myBaseString<T>::myBaseString()
:	m_pStr( NULL ), 
	m_Len( 0 ),	m_Capacity( 0 )
{
}

template<class T>
myBaseString<T>::myBaseString( size_t count, const T &val )
:	m_pStr( NULL ), 
	m_Len( 0 ),	m_Capacity( 0 )
{
	if ( count > 0 )
	{
		m_pStr = new T[count+1];
		size_t i=0;
		for ( i; i<count; ++i )
		{
			m_pStr[i] = val;
		}
		m_pStr[i] = 0;

		m_Len = count;
		m_Capacity = count+1;
	}
}

template<class T>
myBaseString<T>::myBaseString( const T *str )
:	m_pStr( NULL ), 
	m_Len( 0 ),	m_Capacity( 0 )
{
	size_t len = getStrLen( str );
	if ( len > 0 )
	{
		m_pStr = new T[len+1];

		size_t i=0;
		for ( i; i<len; ++i )
		{
			m_pStr[i] = str[i];
		}
		m_pStr[i] = 0;

		this->m_Len = len;
		this->m_Capacity = len+1;
	}
}

template<class T>
myBaseString<T>::myBaseString( const myBaseString &other )
:	m_pStr( NULL ), 
	m_Len( 0 ),	m_Capacity( 0 )
{
	if ( other.m_Len > 0 )
	{
		m_pStr = new T[other.m_Len+1];
		memcpy( m_pStr, other.m_pStr, sizeof(T)*(other.m_Len+1) );

		m_Len = other.m_Len;
		m_Capacity = m_Len+1;
	}
}

template<class T>
myBaseString<T>::~myBaseString()
{
	SAFE_DELARR(m_pStr);
}

template<class T>
void myBaseString<T>::pop_back()
{
	if ( m_Len > 0 )
	{
		--m_Len;
		m_pStr[m_Len] = 0;
	}
}

template<class T>
void myBaseString<T>::push_back( const T &val )
{
	if ( m_Len+1 >= m_Capacity )
	{
		_realloc( GET_BIGGER_CAPACITY( m_Capacity ) );
	}

	m_pStr[m_Len] = val;
	++m_Len;
	m_pStr[m_Len] = 0;
}

template<class T>
size_t myBaseString<T>::getStrLen( const T *str )
{
	size_t len=0;
	while ( str[len] != 0 )
	{
		++len;
	}

	return len;
}

template<class T>
void myBaseString<T>::_realloc( size_t count )
{
	static T *pTemp;
	pTemp = new T[count];

	size_t i=0;
	for ( i; i<m_Len; ++i )
	{
		pTemp[i] = m_pStr[i];
	}
	pTemp[i] = 0;

	SAFE_DELARR( m_pStr );
	m_pStr = pTemp;
	m_Capacity = count;
}

typedef myBaseString<char> myString;
typedef myBaseString<wchar_t> myWCString;

#endif	// END MY_BASESTRING
