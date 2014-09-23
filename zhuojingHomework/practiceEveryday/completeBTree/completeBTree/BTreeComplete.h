#ifndef BTREE_COMPLETE
#define BTREE_COMPLETE

#define SAFE_DELARR( p )	\
{							\
	if( p != NULL )			\
	{						\
		delete [] p;		\
		p = NULL;			\
	}						\
}
#define MAX( a, b ) ( (a > b) ? (a) : (b) )

// 9）TRAVERSE(T) 遍历操作。按某个次序依此访问树中各个节点，并使每个节点只被访问一次。

template<typename T>
class BTreeComplete
{
public:
	BTreeComplete(void);
	~BTreeComplete(void);

	void clear();
	void add( const T &data );
	bool remove();
	bool remove( T &data );

	bool root( T &data );
	bool parent( T &data, int index );
	bool child( T &data, int index, bool isLeft = true );
	bool left_sinling( T &data, int index );
	bool right_sinling( T &data, int index );

	T& operator[]( int index )
	{
		return m_Data[index];
	}

	int size() const
	{
		return m_Size;
	}

private:
	void _resize();

	T *m_Data;
	int m_Size;
	int m_Capacity;
};

template<typename T>
BTreeComplete<T>::BTreeComplete()
{
	m_Size = 0;
	m_Capacity = 9;

	m_Data = new T[m_Capacity];
}


template<typename T>
BTreeComplete<T>::~BTreeComplete()
{
	SAFE_DELARR( m_Data );
}

template<typename T>
void BTreeComplete<T>::clear()
{
	m_Size = 0;
}

template<typename T>
void BTreeComplete<T>::add( const T &data )
{
	_resize();

	m_Data[m_Size] = data;
	++m_Size;
}


template<typename T>
bool BTreeComplete<T>::remove()
{
	if ( m_Size == 0 )
	{
		return false;
	}
	
	--m_Size;
	return true;
}

template<typename T>
bool BTreeComplete<T>::remove( T &data )
{
	if ( m_Size == 0 )
	{
		return false;
	}

	--m_Size;
	data = m_Data[m_Size];
	return true;
}


template<typename T>
bool BTreeComplete<T>::root( T &data )
{
	if ( m_Size == 0 )
	{
		return false;
	}

	data = m_Data[0];
	return true;
}


template<typename T>
bool BTreeComplete<T>::parent( T &data, int index )
{
	if ( (index <= 0) || (index>=m_Size) )
	{
		return false;
	}

	data = m_Data[(index-1)/2];
	return true;
}


template<typename T>
bool BTreeComplete<T>::child( T &data, int index, bool isLeft /* true */ )
{
	if ( (index < 0) || (index>=m_Size) )
	{
		return false;
	}

	int tempIndex = isLeft ?
		index*2+1 : index*2+2;
	
	// 确保存在符合条件的孩子
	if ( tempIndex>=m_Size )
	{
		return false;
	}
	data = m_Data[tempIndex];
	return true;
}

template<typename T>
bool BTreeComplete<T>::left_sinling( T &data, int index )
{
	if ( (index <= 0)			|| 
		 (index >= m_Size)		||
		 (index%2 != 0) )
	{
		return false;
	}

	int tempIndex = index-1;
	data = m_Data[tempIndex];
	return true;
}

template<typename T>
bool BTreeComplete<T>::right_sinling( T &data, int index )
{
	if ( (index <= 0)			|| 
		 (index >= m_Size-1)	||
		 (index%2 != 1) )
	{
		return false;
	}

	int tempIndex = index+1;
	data = m_Data[tempIndex];
	return true;
}

template<typename T>
void BTreeComplete<T>::_resize()
{
	if ( m_Size >= m_Capacity )
	{
		m_Capacity += MAX( m_Capacity, 1 );
		static T *tempBuffer = new T[m_Capacity];
		for ( int i=0; i<m_Size; ++i )
		{
			tempBuffer[i] = m_Data[i];
		}

		// 以新换旧
		SAFE_DELARR( m_Data );
		m_Data = tempBuffer;
	}
}

#endif	// END BTREE_COMPLETE