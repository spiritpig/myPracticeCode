#ifndef MYSTLVECTOR1019
#define MYSTLVECTOR1019

#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }
#define GET_NEW_CAPACITY(c) ( c + c/2 + 1 )

template<class T>
class myStlVector
{
public:
	typedef T *iterator;

public:
	myStlVector();
	~myStlVector();

	iterator& begin() 
	{
		first = &m_pData[0];
		return first;
	}
	iterator& end() 
	{
		last = &m_pData[m_Size];
		return last;
	}

	T& front() const
	{
		return m_pData[0];
	}
	T& back() const
	{
		return m_pData[m_Size-1];
	}

	void pop_back();
	void push_back( const T &val );

private:
	void _realloc( size_t count );

	T *m_pData;
	size_t m_Size;
	size_t m_Capacity;

	iterator first, last;
};

template<class T>
myStlVector<T>::myStlVector()
:	m_pData( NULL ),
	m_Size( 0 ), m_Capacity( 0 )
{
}

template<class T>
myStlVector<T>::~myStlVector()
{
	SAFE_DELARR( m_pData );
}

template<class T>
void myStlVector<T>::pop_back()
{
	if ( m_Size > 0 )
	{
		--m_Size;
	}
}

template<class T>
void myStlVector<T>::push_back( const T &val )
{
	if ( m_Size >= m_Capacity )
	{
		_realloc( GET_NEW_CAPACITY(m_Capacity) );
	}

	m_pData[m_Size] = val;
	++m_Size;
}

template<class T>
void myStlVector<T>::_realloc( size_t count )
{
	static T *pTemp;
	pTemp = new T[count];
	for ( size_t i=0; i<m_Size; ++i )
	{
		pTemp[i] = m_pData[i];
	}
	SAFE_DELARR( m_pData );

	m_pData = pTemp;
	m_Capacity = count;
}

#endif	// END MYSTLVECTOR1019