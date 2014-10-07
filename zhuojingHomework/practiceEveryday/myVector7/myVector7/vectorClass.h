#ifndef MYVECTOR
#define MYVECTOR

#define SAFE_DELARR(p) { if(p) { delete []p; p = NULL; } }
#define GET_NEW_CAPACITY(i) ( i + i/2 + 1 )

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

		iterator& operator=( const iterator &iter )
		{
			this->pointer = iter.pointer;
			return *this;
		}

		iterator operator+( int n )
		{
			iterator temp;
			temp.pointer = this->pointer + n;

			return temp;
		}

		iterator operator-( int n )
		{
			iterator temp;
			temp.pointer = this->pointer - n;

			return temp;
		}

		int operator-( const iterator &iter )
		{
			return (int)(this->pointer - iter.pointer);
		}

		iterator operator++(int)
		{
			iterator temp = *this;
			++pointer;
			return temp;
		}
		iterator& operator++()
		{
			++pointer;
			return *this;
		}

		iterator operator--(int)
		{
			iterator temp = *this;
			--pointer;
			return temp;
		}
		iterator& operator--()
		{
			--pointer;
			return *this;
		}

		T& operator*()
		{
			return *pointer;
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
	myVector( const T *start, const T *end );
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

	void push_back( const T &val );
	void pop_back();

	void erase( iterator pos );
	void insert( iterator pos, const T &val );
	template<class InputIterator>
	void insert( iterator pos, InputIterator start, InputIterator end )
	{
		int count = (int)(end - start);
		if ( m_Size+count > m_Capacity )
		{
			int offset = pos-begin();
			_realloc( m_Size+count );
			pos = begin()+offset;
		}
		m_Size += count;

		iterator rearIter;
		rearIter.pointer = &m_pData[m_Size-1];
		pos.pointer = pos.pointer + (count - 1);
		for ( rearIter; rearIter != pos; --rearIter )
		{
			*rearIter = *(rearIter-count);
		}

		pos.pointer = pos.pointer - (count);
		for ( rearIter; rearIter != pos; --rearIter )
		{
			*rearIter = *(--end);
		}
	}

private:
	void _realloc( size_t count );

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
myVector<T>::myVector( const T *start, const T *end )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 ) 
{
	int count = (int)(end - start);
	if ( count > 0 )
	{
		m_pData = new T[count];
		for ( int i=0; i<count; ++i )
		{
			m_pData[i] = start[i];
		}

		m_Size = count;
		m_Capacity = count;
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
	if ( m_Size >= m_Capacity )
	{
		_realloc( GET_NEW_CAPACITY(m_Capacity) );
	}

	m_pData[m_Size] = val;
	++m_Size;
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
void myVector<T>::erase( iterator pos )
{
	T *endPos = &m_pData[m_Size-1];
	T *pTemp = pos.pointer;
	for ( pTemp; pTemp != endPos; ++pTemp  )
	{
		*pTemp = *(pTemp+1);
	}

	--m_Size;
}

template<class T>
void myVector<T>::insert( iterator pos, const T &val )
{
	if ( m_Size >= m_Capacity )
	{
		static int offset;
		offset = pos - begin();
		_realloc( GET_NEW_CAPACITY(m_Capacity) );
		pos = begin() + offset;
	}

	T *pTemp = &m_pData[m_Size];
	for ( pTemp; pTemp != pos.pointer; --pTemp  )
	{
		*pTemp = *(pTemp-1);
	}

	*pTemp = val;
	++m_Size;
}

template<class T>
void myVector<T>::_realloc( size_t count )
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

#endif	// END MYVECTOR