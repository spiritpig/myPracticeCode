#ifndef MYVECTORCLASS
#define MYVECTORCLASS

#define SAFE_DELARR(p) { if(p) { delete []p; p = NULL; } }

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
		iterator( const T *pt )
			: pointer( (T *)pt )
		{
		}

		int operator-( const iterator &iter )
		{
			return (int)( this->pointer - iter.pointer );
		}
		T* operator-( int n )
		{
			return ( pointer - n );
		}
		T* operator+( int n )
		{
			return ( pointer + n );
		}

		T* operator++()
		{
			return ++pointer;
		}
		T* operator++(int)
		{
			T *temp = pointer;
			++pointer;
			return temp;
		}

		T* operator--()
		{
			return --pointer;
		}
		T* operator--(int)
		{
			T *temp = pointer;
			--pointer;
			return temp;
		}

		T& operator*()
		{
			return *pointer;
		}

		bool operator==( iterator iter )
		{
			return (pointer == iter.pointer);
		}
		bool operator!=( iterator iter )
		{
			return (pointer != iter.pointer);
		}

	public:
		T *pointer;
	};
public:
	myVector();
	myVector( T *start, T *end );
	myVector( const myVector &other );
	myVector( size_t count, T &val );
	~myVector();

	iterator& begin()
	{
		first.pointer = &m_pData[0];
		return first;
	}
	iterator& end()
	{
		last.pointer = &m_pData[m_Size];
		return last;
	}

	void pop_back();
	void push_back( const T &val );
	void insert( iterator pos, iterator first, iterator last );
	void reserve( size_t count );

private:
	T *m_pData;
	size_t m_Size;
	size_t m_Capacity;
	iterator first;
	iterator last;
};

template<class T>
myVector<T>::myVector()
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
}

template<class T>
myVector<T>::myVector( T *start, T *end )
{
	int count = (int)(end-start);
	m_pData = new T[count];

	for ( int i=0; i<count; ++i )
	{
		m_pData[i] = *(start++);
	}

	m_Size = count;
	m_Capacity = count;
}

template<class T>
myVector<T>::myVector( const myVector &other )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	if ( other.m_Size > 0 )
	{
		m_pData = new T[other.m_Size];
		for ( size_t i=0; i<other.m_Size; ++i )
		{
			m_pData[i] = other.m_pData[i];
		}

		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
	}
}

template<class T>
myVector<T>::myVector( size_t count, T &val )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	if ( count > 0 )
	{
		m_pData = new T[other.m_Size];
		for ( size_t i=0; i<other.m_Size; ++i )
		{
			m_pData[i] = val;
		}

		m_Size = other.m_Size;
		m_Capacity = other.m_Capacity;
	}
}

template<class T>
myVector<T>::~myVector()
{
	SAFE_DELARR( m_pData );
}

template<class T>
void myVector<T>::pop_back()
{
	if ( m_Size > 0 )
	{
		--m_Size;
	}
}

template<class T>
void myVector<T>::push_back( const T &val )
{
	if ( m_Size > m_Capacity )
	{
		reserve( m_Capacity + m_Capacity/2 + 1 );
	}

	m_pData[m_Size] = val;
	++m_Size;
}

template<class T>
void myVector<T>::insert( iterator pos, iterator first, iterator last )
{
	int count = last-first;
	if ( m_Size+count > m_Capacity )
	{
		int offset = pos - begin();
		static size_t tempNum = m_Capacity + m_Capacity/2 + 1;
		tempNum = m_Size+count > tempNum ? m_Size+count : tempNum;
		reserve( tempNum );
		pos = begin() + offset;
	}
	// 方便移动的起始位置计算，先改变size了
	m_Size += count;

	iterator rearIter;
	iterator endIter = pos + count-1;
	for ( rearIter=end()-1; rearIter!=endIter; --rearIter )
	{
		*rearIter = *(rearIter-count);
	}

	endIter = pos-1;
	for ( rearIter; rearIter != endIter; --rearIter )
	{
		*rearIter = *(--last);
	}
}

template<class T>
void myVector<T>::reserve( size_t count )
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

#endif	// END MYVECTORCLASS