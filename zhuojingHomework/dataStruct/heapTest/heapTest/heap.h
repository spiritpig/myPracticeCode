#ifndef HEAP
#define HEAP

#define MAX( a, b ) ( (a > b) ? (a) : (b) )
#define SAFE_DELARR(p) {if(p) {delete []p;p=0;}}

template<typename T, bool isMax = true>
class heap
{
public:
	heap(void);
	~heap(void);

	void add( const T &data );
	bool remove_Top( T &data );

private:
	// 特殊的比较函数，根据堆为大根堆或小根堆，决定返回值
	// 大根堆时，left > right 返回1
	// 小根堆时，left < right 返回1
	int _compare( const T &left, const T &right );
	void _resize();

	T *m_Data;
	size_t m_Size;
	size_t m_Capacity; 
};

template<typename T, bool isMax>
heap<T, isMax>::heap( void )
{
	m_Capacity = 9;
	m_Size = 0;

	m_Data = new T[m_Capacity];
}

template<typename T, bool isMax>
heap<T, isMax>::~heap( void )
{
	SAFE_DELARR( m_Data );
}

template<typename T, bool isMax>
void heap<T, isMax>::add( const T &data )
{
	// 将第一个元素储存在下标1的位置，下标0放弃不用
	if ( m_Size <= 0 )
	{
		m_Size = 1;
		m_Data[m_Size] = data;
		return;
	}

	// 按需扩容, 此处使用m_Size+1，是因为
	// 我们放弃了第一个节点，m_Size即是最后一个节点的
	// 位置也是元素个数，所以，m_Size必须小于容量才不会越界
	if ( m_Size+1 >= m_Capacity )
	{
		_resize();
	}

	++m_Size;
	size_t insertPos = m_Size;
	while ( insertPos > 1 )
	{
		if( _compare( data, m_Data[insertPos/2] ) == 1 )
		{
			m_Data[insertPos] = m_Data[insertPos/2];
			insertPos /= 2;
		}
		else
		{
			break;
		}
	}

	m_Data[insertPos] = data; 
}

template<typename T, bool isMax>
bool heap<T, isMax>::remove_Top( T &data )
{
	if( m_Size <= 0 )
	{
		return false;
	}

	data = m_Data[1];
	static T tempVal;
	static size_t newPos, tempPos;
	tempVal = m_Data[m_Size];
	tempPos = 1;
	newPos = 1;

	// 对堆进行调整
	--m_Size;
	while ( newPos <= m_Size )
	{
		m_Data[newPos] = m_Data[tempPos];
		newPos = tempPos;
		// 有两个子节点的情况
		if ( (2*newPos + 1) <= m_Size ) 
		{
			if ( _compare( tempVal, m_Data[2*newPos] ) == -1 )
			{
				tempPos = 2*newPos;
			}
			if ( _compare( m_Data[2*newPos], m_Data[2*newPos + 1] ) == -1 )
			{
				tempPos = 2*newPos + 1;
			}
		}
		// 有一个子节点的情况
		else
		if ( (2*newPos) <= m_Size ) 
		{
			if ( _compare( tempVal, m_Data[2*newPos] ) == -1 )
			{
				tempPos = 2*newPos;
			}
		}

		if( newPos == tempPos )
		{
			break;
		}
	}

	// 将原来在末尾的元素，移动到调整后的位置上
	m_Data[newPos] = tempVal;
	return true;
}

template<typename T, bool isMax>
int heap<T, isMax>::_compare( const T &left, const T &right )
{
	if ( left == right )
	{
		return 0;
	}

	if ( isMax )
	{
		return (left > right ? 1 : -1);
	} 
	else
	{
		return (left < right ? 1 : -1);
	}
}


template<typename T, bool isMax>
void heap<T, isMax>::_resize()
{
	m_Capacity += MAX( m_Capacity/2, 1 );

	static T* pTemp = NULL;
	pTemp = new T[m_Capacity];
	for ( size_t i=0; i<=m_Size; ++i )
	{
		pTemp[i] = m_Data[i];
	}

	SAFE_DELARR( m_Data );
	m_Data = pTemp;
}

#endif	// END HEAP
