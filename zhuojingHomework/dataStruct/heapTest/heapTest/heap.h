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
	// ����ıȽϺ��������ݶ�Ϊ����ѻ�С���ѣ���������ֵ
	// �����ʱ��left > right ����1
	// С����ʱ��left < right ����1
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
	// ����һ��Ԫ�ش������±�1��λ�ã��±�0��������
	if ( m_Size <= 0 )
	{
		m_Size = 1;
		m_Data[m_Size] = data;
		return;
	}

	// ��������, �˴�ʹ��m_Size+1������Ϊ
	// ���Ƿ����˵�һ���ڵ㣬m_Size�������һ���ڵ��
	// λ��Ҳ��Ԫ�ظ��������ԣ�m_Size����С�������Ų���Խ��
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

	// �Զѽ��е���
	--m_Size;
	while ( newPos <= m_Size )
	{
		m_Data[newPos] = m_Data[tempPos];
		newPos = tempPos;
		// �������ӽڵ�����
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
		// ��һ���ӽڵ�����
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

	// ��ԭ����ĩβ��Ԫ�أ��ƶ����������λ����
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
