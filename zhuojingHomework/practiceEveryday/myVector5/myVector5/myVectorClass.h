#ifndef MYVECTOR
#define MYVECTOR

#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }

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
			: pointer( (int *)pt )
		{
		}

		int operator-( const iterator &iter )
		{
			return (int)( this->pointer - iter.pointer );
		}
		T* operator-( size_t n )
		{
			return (pointer - n);
		}

		T* operator+( size_t n )
		{
			return (pointer + n);
		}

		iterator& operator ++()
		{
			++pointer;
			return *this;
		}
		iterator& operator ++(int)
		{
			iterator temp = *this;
			++pointer;
			return temp;
		}

		iterator& operator --()
		{
			--pointer;
			return *this;
		}
		iterator& operator --(int)
		{
			iterator temp = *this;
			--pointer;
			return temp;
		}

		bool operator==( const iterator &iter )
		{
			return pointer == iter.pointer;
		}
		bool operator!=( const iterator &iter )
		{
			return pointer != iter.pointer;
		}

		T& operator*()
		{
			return *pointer;
		}
	public:
		T *pointer;
	};

public:
	myVector();
	myVector( const myVector &other );
	myVector( size_t count, const T &val );
	~myVector();

	T& operator []( size_t index )
	{
		return m_pData[index];
	}

	void pop_back()
	{
		if ( m_Size > 0 )
		{
			--m_Size;
		}
	}
	void push_back( const T &val );
	void resize( size_t count );
	void resize( size_t count, const T &val );
	void reserve( size_t count );

	size_t size() const 
	{
		return m_Size;
	}
	size_t capacity() const
	{
		return m_Capacity;
	}
	void clear();

	void insert( iterator pos, iterator left, iterator right );

	iterator& begin()
	{
		first.pointer = m_pData;
		return first;
	}
	iterator& end()
	{
		last.pointer = m_pData+m_Size;
		return last;
	}

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
myVector<T>::myVector( size_t count, const T &val )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	if ( count > 0 )
	{
		m_pData = new T[count];
		for ( size_t i=0; i<count; ++i )
		{
			m_pData[i] = val;
		}

		m_Size = count;
		m_Capacity = count;
	}
}

template<class T>
myVector<T>::~myVector()
{
	SAFE_DELARR(m_pData);
}

template<class T>
void myVector<T>::push_back( const T &val )
{
	if ( m_Size >= m_Capacity )
	{
		reserve( m_Capacity + m_Capacity/2 + 1 );
	}

	m_pData[m_Size] = val;
	++m_Size;
}

template<class T>
void myVector<T>::resize( size_t count )
{
	if ( count > m_Capacity )
	{
		reserve( m_Capacity + m_Capacity/2 + 1 );
	}
	else
	if ( count < m_Size )
	{
		m_Size = count;
	}
}

template<class T>
void myVector<T>::resize( size_t count, const T &val )
{
	if ( count > m_Capacity )
	{
		reserve( m_Capacity + m_Capacity/2 + 1 );

		for ( size_t i=m_Size; i<count; ++i )
		{
			m_pData[i] = val;
		}
	}
	else
	if ( count < m_Size )
	{
		m_Size = count;
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
		SAFE_DELARR(m_pData);

		m_pData = pTemp;
		m_Capacity = count;
	}
}

template<class T>
void myVector<T>::clear()
{
	SAFE_DELARR(m_pData);
	m_Size = 0;
}

template<class T>
void myVector<T>::insert( iterator pos, iterator left, iterator right )
{
	size_t count = right-left;
	if ( m_Size+count > m_Capacity )
	{
		int offset = pos-begin();
		reserve( m_Size+count > m_Capacity+m_Capacity/2 + 1 ? 
			m_Size+count : m_Capacity+m_Capacity/2 + 1 );
		pos = begin()+offset;
	}

	// 将现有元素后移
	iterator rearIter = end()-1;
	iterator endIter = pos-1;
	for ( rearIter; rearIter != endIter; --rearIter )
	{
		*(rearIter+count) = *(rearIter);
	}

	// 拷贝新的元素
	for ( size_t i=0; i<count; ++i  )
	{
		*(pos+i) = *(left+i);
	}

	m_Size += count;
}

#endif	// END MYVECTOR