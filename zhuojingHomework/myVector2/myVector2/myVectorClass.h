#ifndef MYVECTORCLASS
#define MYVECTORCLASS

#define SAFE_DELARR(p) { if(p) { delete []p; p = NULL; } }
#define MAX(a,b) ( a>b ? a : b )

template<typename T>
class myVectorClass
{
public:
	struct iterator
	{
		iterator()
			: pointer( NULL ) {}
		iterator( const iterator &iter )
			: pointer( iter.pointer ) {}

		T& operator*()
		{
			return (*pointer);
		}

		iterator& operator=( const iterator &iter )
		{
			this->pointer = iter.pointer;
			return *this;
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
		T& operator[]( size_t pos )
		{
			return pointer[pos];
		}
		T* operator+( size_t pos )
		{
			return (pointer + pos);
		}
		T* operator-( size_t pos )
		{
			return (pointer - pos);
		}

		bool operator==(const iterator &other)
		{
			return pointer == other.pointer;
		}
		bool operator!=(const iterator &other)
		{
			return pointer != other.pointer;
		}
		bool operator!()
		{
			return !pointer;
		}

		T *pointer;
	};

public:
	myVectorClass();
	myVectorClass( size_t count );
	myVectorClass( size_t count, const T &data );
	~myVectorClass();

	void assign( size_t count, const T &data );

	size_t size() const
	{
		return m_Size;
	}

	size_t capacity() const
	{
		return m_Capacity;
	}

	T& at( size_t pos );
	const T& at( size_t pos ) const;

	T& back()
	{
		return m_pData[m_Size-1];
	}

	const T& back() const
	{
		return m_pData[m_Size-1];
	}

	T& front()
	{
		return m_pData[0];
	}

	const T& front() const
	{
		return m_pData[0];
	}

	void pop_back()
	{
		--m_Size;
	}
	void push_back( const T &data );

	iterator& begin() 
	{
		beginIter.pointer = &m_pData[0];
		return beginIter;
	}
	iterator end() 
	{
		endIter.pointer = &m_pData[m_Size];
		return endIter;
	}

	T& operator[]( size_t index )
	{
		return m_pData[index];
	}
	void reserve( size_t count );

private:
	T *m_pData;
	size_t m_Size;
	size_t m_Capacity;

	iterator beginIter;
	iterator endIter;
};

template<typename T>
myVectorClass<T>::myVectorClass()
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
}

template<typename T>
myVectorClass<T>::~myVectorClass()
{
	SAFE_DELARR(m_pData);
}

template<typename T>
myVectorClass<T>::myVectorClass( size_t count )
{
	m_pData = new T[count];
	m_Capacity = count;
	m_Size = count;
}

template<typename T>
myVectorClass<T>::myVectorClass( size_t count, const T &data )
{
	m_pData = new T[count];
	m_Capacity = count;
	m_Size = count;
	for ( size_t i=0; i<count; ++i )
	{
		m_pData[i] = data;
	}
}

template<typename T>
void myVectorClass<T>::assign( size_t count, const T &data )
{
	reserve(count);

	for ( size_t i=0; i<count; ++i )
	{
		m_pData[i] = data;
	}
	m_Size = count;
}

template<typename T>
T& myVectorClass<T>::at( size_t pos )
{
	if ( pos < m_Size )
	{
		return m_pData[pos];
	}
	else
	{
		throw out_of_range;
	}
}

template<typename T>
const T& myVectorClass<T>::at( size_t pos ) const
{
	if ( pos < m_Size )
	{
		return m_pData[pos];
	}
	else
	{
		throw out_of_range;
	}
}

template<typename T>
void myVectorClass<T>::push_back( const T &data )
{
	if ( m_Size >= m_Capacity )
	{
		reserve( m_Capacity + MAX( m_Capacity*2/3, 1 ) );
	}

	m_pData[m_Size] = data;
	++m_Size;
}

template<typename T>
void myVectorClass<T>::reserve( size_t count )
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

#endif	// END MYVECTORCLASS
