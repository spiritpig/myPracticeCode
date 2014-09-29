#ifndef MYVECTOR
#define MYVECTOR

#define SAFE_DELARR( p ) { if(p) { delete []p; p = NULL; } }

template<class T>
class myVector
{
public:
	struct iterator
	{
		iterator()
			: pointer( NULL )
		{
		}
		iterator( const iterator &iter )
			: pointer( iter.pointer )
		{
		}
		
		T& operator*()
		{
			return *pointer;
		}
 
		iterator& operator =( const iterator &iter )
		{
			pointer = iter.pointer;
			return *this;
		}
		iterator& operator =( const T *pt )
		{
			pointer = (T *)pt;
			return *this;
		}

		T* operator +( int index )
		{
			return (pointer + index);
		}

		int operator -( const iterator &iter )
		{
			return (int)(this->pointer - iter.pointer);
		}
		int operator -( const T *pt )
		{
			return (int)(this->pointer - pt);
		}

		iterator& operator++()
		{
			++pointer;
			return *this;
		}
		iterator  operator++(int)
		{
			static iterator temp = *this;

			++pointer;
			return temp;
		}
		iterator& operator--()
		{
			--pointer;
			return *this;
		}
		iterator  operator--(int)
		{
			static iterator temp = *this;

			--pointer;
			return temp;
		}

		bool operator==( const iterator &iter )
		{
			return (this->pointer == iter.pointer);
		}
		bool operator!=( const iterator &iter )
		{
			return (this->pointer != iter.pointer);
		}

	public:
		T *pointer;
	};

public:
	myVector();
	myVector( size_t count, const T &val );
	myVector( const T *left, const T *right );
	myVector( const iterator *left, const iterator *right );
	myVector( const myVector &mvec );
	~myVector();

	void push_back( const T &val );
	void pop_back()
	{
		if ( m_Size > 0 )
		{
			--m_Size;
		}
	}

	T& operator[]( size_t index )
	{
		return m_pData[index];
	}

	size_t size() const
	{
		return m_Size;
	}
	size_t capacity() const
	{
		return m_Capacity;
	}

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

	void reverse( size_t count );

private:
	T *m_pData;
	size_t m_Size;
	size_t m_Capacity;

	iterator first, last;
};

template<class T>
myVector<T>::myVector()
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
}

template<class T>
myVector<T>::myVector( size_t count, const T &val )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	if ( count > 0 )
	{
		m_pData = new T[count];
		for ( int i=0; i<count; ++i )
		{
			m_pData[i] = val;
		}
		m_Size = count;
		m_Capacity = count;
	}
}

template<class T>
myVector<T>::myVector( const T *left, const T *right )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	int count = (int)(right-left);

	if ( count > 0 )
	{
		m_pData = new T[count];

		for ( int i=0; i<count; ++i )
		{
			m_pData[i] = *(left + i);
		}

		m_Size = count;
		m_Capacity = count;
	}
}

template<class T>
myVector<T>::myVector( const iterator *left, const iterator *right )
{
	int count = left-right;

	if ( count > 0 )
	{
		for ( int i=0; i<count; ++i )
		{
			m_pData[i] = *(left + count);
		}

		m_Size = count;
		m_Capacity = count;
	}
}

template<class T>
myVector<T>::myVector( const myVector &mvec )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	if ( mvec.m_Size > 0 )
	{
		m_pData = new T[mvec.m_Size];
		for ( int i=0; i<mvec.m_Size; ++i )
		{
			m_pData[i] = mvec.m_pData[i];
		}

		m_Size = mvec.m_Size;
		m_Capacity = mvec.m_Size;
	}
}

template<class T>
myVector<T>::~myVector()
{
	SAFE_DELARR( m_pData );
}

template<class T>
void myVector<T>::push_back( const T &val )
{
	if ( m_Size < m_Capacity )
	{
		reverse( m_Capacity*2 );
	}

	m_pData[m_Size] = val;
	++m_Size;
}

template<class T>
void myVector<T>::reverse( size_t count )
{
	if ( count > m_Capacity )
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
}

#endif	// END MYVECTOR