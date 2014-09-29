#ifndef MYVECTOR
#define MYVECTOR

#define  SAFE_DELARR(p) { if (p) { delete []p; p=NULL; } }

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
			: pointer( pt ) 
		{
		}

		iterator& operator=( const iterator &iter )
		{
			pointer = (int *)iter.pointer;
			return *this;
		}
		iterator& operator=( const T *pt )
		{
			pointer = (int *)pt;
			return *this;
		}

		iterator& operator--()
		{
			--pointer;
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp = *this;
			--pointer;

			return temp;
		}

		iterator& operator++()
		{
			++pointer;
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp = *this;
			++pointer;

			return temp;
		}

		T* operator+( int i ) const
		{
			return (pointer + i);
		}

		int operator-( const iterator &rIter ) const
		{
			return this->pointer - rIter.pointer;
		}

		bool operator==( const iterator &iter ) const
		{
			return iter.pointer == pointer;
		}
		bool operator!=( const iterator &iter ) const
		{
			return iter.pointer != pointer;
		}

		T& operator*() const
		{
			return *pointer;
		}

	private:
		T *pointer;
	};

	struct reverse_iterator
	{
		reverse_iterator()
			: pointer( NULL ) 
		{
		}

		template<class InputIterator>
		reverse_iterator( const InputIterator &iter )
			: pointer( iter.pointer ) 
		{
		}
		reverse_iterator( const T *pt )
			: pointer( pt ) 
		{
		}

		reverse_iterator& operator=( const reverse_iterator &iter )
		{
			pointer = iter.pointer;
			return *this;
		}
		reverse_iterator& operator=( const T *pt )
		{
			pointer = (T *)pt;
			return *this;
		}

		reverse_iterator& operator--()
		{
			++pointer;
			return *this;
		}
		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			++pointer;

			return temp;
		}

		reverse_iterator& operator++()
		{
			--pointer;
			return *this;
		}
		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			--pointer;

			return temp;
		}

		T* operator+( int i ) const
		{
			return pointer - i;
		}
		int operator-( const reverse_iterator &rIter ) const
		{
			return (int)(this->pointer - rIter.pointer);
		}

		bool operator==( const reverse_iterator &iter ) const
		{
			return iter.pointer == pointer;
		}
		bool operator!=( const reverse_iterator &iter ) const
		{
			return iter.pointer != pointer;
		}

		T& operator*() const
		{
			return *pointer;
		}

	private:
		T *pointer;
	};

	myVector();
	myVector( const myVector &mvec );
	myVector( const T *left, const T *right );
	myVector( const iterator &left, const iterator &right );
	myVector( const reverse_iterator &left, const reverse_iterator &right );
	myVector( size_t count, const T &val );

	void push_back( const T &val );
	void pop_back();

	T& operator[]( size_t pos )
	{
		return m_pData[pos];
	}

	iterator& begin() 
	{
		m_First = &m_pData[0];
		return m_First;
	}
	reverse_iterator& rbegin()
	{
		m_rFirst = &m_pData[m_Size-1];
		return m_rFirst;
	}

	iterator& end()
	{
		m_Last = &m_pData[m_Size];
		return m_Last;
	}
	reverse_iterator& rend()
	{
		m_rLast = (m_pData - 1);
		return m_rLast;
	}

	void reverse( size_t count );

private:
	T *m_pData;
	size_t m_Size;
	size_t m_Capacity;
	iterator m_First;
	iterator m_Last;
	reverse_iterator m_rFirst;
	reverse_iterator m_rLast;
};

template<class T>
myVector<T>::myVector()
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
}

template<class T>
myVector<T>::myVector( const myVector &mvec )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	if ( mvec.m_pData != NULL )
	{
		m_pData = new T[mvec.m_Size];
		m_Size = mvec.m_Size;
		m_Capacity = m_Size;
	}
}

template<class T>
myVector<T>::myVector( size_t count, const T &val )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	m_pData = new T[count];
	m_Size = count;
	m_Capacity = count;
}

template<class T>
myVector<T>::myVector( const T *left, const T *right )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	size_t count = right-left;

	if ( count>0 )
	{
		m_pData = new T[count];
		m_Size = count;
		m_Capacity = count;
		
		for ( size_t i=0; i<count; ++i )
		{
			m_pData[i] = left[i];
		}
	}
}

template<class T>
myVector<T>::myVector( const iterator &left, const iterator &right )
{
	int count = right-left;

	if ( count>0 )
	{
		m_pData = new T[count];
		m_Size = count;
		m_Capacity = count;

		for ( int i=0; i<count; ++i )
		{
			m_pData[i] = *(left+i);
		}
	}
}

template<class T>
myVector<T>::myVector( const reverse_iterator &left, const reverse_iterator &right )
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
	int count = left-right;

	if ( count>0 )
	{
		m_pData = new T[count];
		m_Size = count;
		m_Capacity = count;

		for ( int i=0; i<count; ++i )
		{
			m_pData[i] = *(left+i);
		}
	}
}

template<class T>
void myVector<T>::push_back( const T &val )
{
	if ( m_Size >= m_Capacity )
	{
		reverse( m_Capacity*2 );
	}

	m_pData[m_Size] = val;
	++m_Size;
}

template<class T>
void myVector<T>::pop_back()
{
	if ( m_Size > 0  )
	{
		--m_Size;
	}
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
	}
}

#endif	// END MYVECTOR