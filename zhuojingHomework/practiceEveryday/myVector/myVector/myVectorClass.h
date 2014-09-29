#ifndef MYVECTORCLASS
#define MYVECTORCLASS

#define SAFE_DELARR(p) {if(p != NULL){ delete []p; p=NULL; }}
#define MAX( a, b ) ( a > b ? a : b )

template<class T>
class myVectorClass
{
public:
	myVectorClass();
	myVectorClass( size_t count );
	myVectorClass( const T &data, size_t count );
	~myVectorClass();

	void assgin( size_t count, const T &data );
	void pop_back();
	void push_back( const T &data );

	T& at( size_t pos );
	const T& at( size_t pos ) const;
	T& back();
	const T& back() const;
	T& front();
	const T& front() const;
	size_t size() const;
	size_t capacity() const;
	bool empty() const;
	size_t max_size() const;

	void resize( size_t count );
	void resize( size_t count, const T &data );
	void reverse( size_t count );

	void swap( myVectorClass &right );

	template<class T1>
	friend void myswap( myVectorClass<T1> &left, myVectorClass<T1> &right );

private:
	T *m_pData;
	size_t m_Size;
	size_t m_Capacity;
};

//////////////////////////////////////////////////////////////////////////
//
//	成员函数定义
//
//////////////////////////////////////////////////////////////////////////
template<class T>
myVectorClass<T>::myVectorClass()
: m_pData( NULL ), m_Size( 0 ),
  m_Capacity( 0 )
{
}

template<class T>
myVectorClass<T>::myVectorClass( size_t count )
{
	m_pData = new T[count];
	memset( m_pData, 0, sizeof(T)*count );
	m_Capacity = count;
	m_Size = count;
}

template<class T>
myVectorClass<T>::myVectorClass( const T &data, size_t count )
{
	m_pData = new T[count];
	for ( int i=0; i<count; ++i )
	{
		m_pData[i] = data;
	}

	m_Capacity = count;
	m_Size = count;
}

template<class T>
myVectorClass<T>::~myVectorClass()
{
	SAFE_DELARR( m_pData );
	m_Capacity = 0;
	m_Size = 0;
}

template<class T>
void myVectorClass<T>::assgin( size_t count, const T &data )
{
	if ( count > m_Capacity )
	{
		SAFE_DELARR( m_pData );
		m_pData = new T[count];
		m_Capacity = count;
	}

	for ( int i=0; i<count; ++i )
	{
		m_pData[i] = data;
	}
	m_Size = count;
}

template<class T>
void myVectorClass<T>::pop_back()
{
	if ( m_Size > 0 )
	{
		--m_Size;
	}
}

template<class T>
void myVectorClass<T>::push_back( const T &data )
{
	reverse( m_Capacity + MAX( m_Capacity/2, 1 ) );

	m_pData[m_Size] = data;
	++m_Size;
}

template<class T>
T& myVectorClass<T>::at( size_t pos )
{
	return m_pData[pos];
}

template<class T>
const T& myVectorClass<T>::at( size_t pos ) const
{
	return m_pData[pos];
}

template<class T>
T& myVectorClass<T>::back()
{
	return m_pData[m_Size-1];
}

template<class T>
const T& myVectorClass<T>::back() const
{
	return m_pData[m_Size-1];
}

template<class T>
T& myVectorClass<T>::front()
{
	return m_pData[0];
}

template<class T>
const T& myVectorClass<T>::front() const
{
	return m_pData[0];
}

template<class T>
bool myVectorClass<T>::empty() const
{
	return m_Size;
}

template<class T>
inline size_t myVectorClass<T>::size() const
{
	return m_Size;
}

template<class T>
inline size_t myVectorClass<T>::capacity() const
{
	return m_Capacity;
}

template<class T>
size_t myVectorClass<T>::max_size() const
{
	return 0xffffffff / sizeof(T);
}

template<class T>
void myVectorClass<T>::resize( size_t count )
{
	if ( count > m_Size )
	{
		// 扩容规则
		if ( count < ( m_Capacity + MAX( m_Capacity/2, 1 ) ) )
		{
			reverse( m_Capacity + MAX( m_Capacity/2, 1 ) );
		}
		else
		{
			reverse( count );
		}

		static T nullObj;
		// 填充新元素
		for ( size_t i=m_Size; i<count; ++i )
		{
			m_pData[i]= nullObj;
		}
	}

	m_Size = count;
}

template<class T>
void myVectorClass<T>::resize( size_t count, const T &data )
{
	if ( count > m_Size )
	{
		// 扩容规则
		if ( count <= ( m_Capacity + MAX( m_Capacity/2, 1 ) ) )
		{
			reverse( m_Capacity + MAX( m_Capacity/2, 1 ) );
		}
		else
		{
			reverse( count );
		}

		// 填充新元素
		for ( size_t i=m_Size; i<count; ++i )
		{
			m_pData[i]= data;
		}
	}

	m_Size = count;
}

template<class T>
void myVectorClass<T>::reverse( size_t count )
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

template<class T>
void myVectorClass<T>::swap( myVectorClass &right )
{
	// 交换数据指针
	static T *pTemp;
	pTemp = right.m_pData;
	right.m_pData = m_pData;
	m_pData = pTemp;

	// 交换元素个数
	static size_t tempNum;
	tempNum = right.m_Size;
	right.m_Size = m_Size;
	m_Size = tempNum;

	// 交换容量
	tempNum = right.m_Capacity;
	right.m_Capacity = m_Capacity;
	m_Capacity = tempNum;
}

template<class T>
void myswap( myVectorClass<T> &left, myVectorClass<T> &right )
{
	// 交换数据指针
	static T *pTemp;
	pTemp = right.m_pData;
	right.m_pData = left.m_pData;
	left.m_pData = pTemp;

	// 交换元素个数
	static size_t tempNum;
	tempNum = right.m_Size;
	right.m_Size = left.m_Size;
	left.m_Size = tempNum;

	// 交换容量
	tempNum = right.m_Capacity;
	right.m_Capacity = left.m_Capacity;
	left.m_Capacity = tempNum;
}

#endif	// END MYVECTORCLASS
