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

	int compare( const myBaseString &other );
	void pop_back();
	void push_back( const T &val );
	T* c_Str() const
	{
		return m_pStr;
	}

	myBaseString& operator=( const myBaseString &other );
	myBaseString operator+( const myBaseString &other );
	T& operator[]( size_t index )
	{
		return m_pStr[index];
	}

private:
	void _stringCat( T * const dest, const T * const src1, const T * const src2 );
	size_t _getStringLen( const T *str );
	void _realloc( size_t count );

	T *m_pStr;
	size_t m_Len;
	size_t m_Capacity;
	size_t m_Index;
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
	size_t len = _getStringLen( str );
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
int myBaseString<T>::compare( const myBaseString &other )
{
	m_Index = 0;
	while ( (this->m_pStr[m_Index] != 0) ||
			(other.m_pStr[m_Index] != 0) )
	{
		if ( this->m_pStr[m_Index] > other.m_pStr[m_Index] )
		{
			return 1;
		}
		else
		if ( this->m_pStr[m_Index] < other.m_pStr[m_Index] )
		{
			return -1;
		}

		++m_Index;
	}

	return 0;
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
myBaseString<T>& myBaseString<T>::operator=( const myBaseString<T> &other )
{
	// 重新分配内存
	if ( this->m_Capacity <= other.m_Len )
	{
		this->_realloc(other.m_Len+1);
	}

	// 复制other的内容
	m_Index = 0;
	while ( (this->m_pStr[m_Index] = other.m_pStr[m_Index]) != '\0' )
	{
		++m_Index;
	}

	return *this;
}

template<class T>
myBaseString<T> myBaseString<T>::operator+( const myBaseString<T> &other )
{
	myBaseString mTemp;

	mTemp.m_Len = _getStringLen( this->m_pStr ) + _getStringLen( other.m_pStr );
	mTemp.m_Capacity = mTemp.m_Len+1;
	mTemp.m_pStr = new T[mTemp.m_Len+1];
	_stringCat( mTemp.m_pStr, this->m_pStr, other.m_pStr );

	return mTemp;
}

template<class T>
void myBaseString<T>::_stringCat( T * const dest, const T * const src1, const T * const src2 )
{
	size_t destIndex = 0;
	m_Index = 0;
	while ( (dest[destIndex] = src1[m_Index]) != '\0' )
	{
		++destIndex;
		++m_Index;
	}

	m_Index = 0;
	while ( (dest[destIndex] = src2[m_Index]) != '\0' )
	{
		++destIndex;
		++m_Index;
	}

}

template<class T>
size_t myBaseString<T>::_getStringLen( const T *str )
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
