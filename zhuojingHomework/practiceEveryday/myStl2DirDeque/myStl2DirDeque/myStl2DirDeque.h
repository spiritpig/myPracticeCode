#ifndef MYSTL2DIRDEQUE
#define MYSTL2DIRDEQUE

#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }
#define GET_NEW_CAPACITY(s) ( s + s/2 + 1 ) 

template<class T>
class myStl2DirDeque
{
public:
	struct iterator
	{
		iterator()
			: pt( NULL ), 
			  leftPT( NULL ), rightPT( NULL ),
			  sit( -1 ), isLeft( true )
		{
		}

		iterator& operator++()
		{
			if ( isLeft )
			{
				// ����������һ������Ҫ��ת���ұ�ȥ
				// �������������λ��ֱ��--
				if ( pt == leftPT )
				{
					pt = rightPT;
					isLeft = false;
				}
				else
				{
					// ++���������˵��--���±��С�ķ����ƶ�
					--pt;
				}
			}
			else
			{
				++pt;
			}
			++sit;

			return *this;
		}

		iterator& operator--()
		{
			if ( isLeft )
			{
				// --���������˵��++�����±�����ķ����ƶ�
				++pt;
			}
			else
			{
				// �����ұߵ�һ��λ�ã���Ҫ��ת�����ȥ
				// �������ұ�����λ��ֱ��++
				if ( pt == rightPT )
				{
					pt = leftPT;
					isLeft = true;
				}
				else
				{
					--pt;
				}
			}
			--sit;

			return *this;
		}

		bool operator==( const iterator &other )
		{
			return (pt == other.pt);
		}

		bool operator!=( const iterator &other )
		{
			return (pt != other.pt);
		}

		T& operator*()
		{
			return *pt;
		}

	public:
		T *pt;
		T *leftPT, *rightPT;
		// �˴����������޷������Σ�����һ�㿼��
		// ��sit����ȷ��ʱ�򣬱���С��0���������Ԫ�ظ���
		// ��ʱ��sit��ʹ��ʾ��ȷ��pt��λ��ʵ�����Ѿ�����
		// ���ԣ�ѡ���޷������Σ���ʹ��ӦС��0������Ϊ�ܴ�
		// ����������Ӱ����������ʵ��
		size_t sit;
		bool isLeft;
	};

public:
	myStl2DirDeque();
	myStl2DirDeque( const myStl2DirDeque &other );
	~myStl2DirDeque();

	void pop_front();
	void pop_back();
	void push_front( const T &val );
	void push_back( const T &val );

	size_t size() const
	{
		return (m_LeftSize + m_RightSize);
	}

	T& at( size_t index )
	{
		if ( index < m_LeftSize )
		{
			return m_pLeftData[m_LeftSize-index-1];
		}
		else
		if ( (index-m_LeftSize) < m_RightSize )
		{
			return m_pRightData[index-m_LeftSize];
		}
		else
		{
			throw std::out_of_range( "�����" );
		}
	}

	T& operator[]( size_t index )
	{
		if ( index < m_LeftSize )
		{
			return m_pLeftData[m_LeftSize-index-1];
		}
		else
		{
			return m_pRightData[index-m_LeftSize];
		}
	}

	iterator& begin()
	{
		first.leftPT = m_pLeftData;
		first.rightPT = m_pRightData;
		first.pt = m_pLeftData + m_LeftSize - 1;
		first.sit = 0;
		
		return first;
	}

	iterator& end()
	{
		last.leftPT = m_pLeftData;
		last.rightPT = m_pRightData;
		last.pt = m_pRightData + m_RightSize;
		last.sit = m_RightSize + m_LeftSize;

		return last;
	}

private:
	void _redivideData( bool isLeft );
	void _realloc( size_t count, bool isLeft );

	T *m_pLeftData;
	T *m_pRightData;

	size_t m_LeftSize;
	size_t m_LeftCapacity;
	size_t m_RightSize;
	size_t m_RightCapacity;
	
	iterator first, last;
};

template<class T>
myStl2DirDeque<T>::myStl2DirDeque()
:	m_pLeftData( NULL ),
	m_LeftSize( 0 ), m_LeftCapacity( 0 ),
	m_pRightData( NULL ),
	m_RightSize( 0 ), m_RightCapacity( 0 )
{
}

template<class T>
myStl2DirDeque<T>::~myStl2DirDeque()
{
	SAFE_DELARR( m_pLeftData );
	SAFE_DELARR( m_pRightData );
}

template<class T>
void myStl2DirDeque<T>::pop_front()
{
	if ( m_LeftSize <= 0 )
	{
		_redivideData( true );

		// ���������һ��Ԫ�ض�����--
		// �����û��Ԫ�أ�֤���ұ�ֻ��һ��
		// ��Ϊ���ұߵ�Ԫ���������ڵ���2ʱ��
		// ������ֵܷ�һ��,���ԣ����û��Ԫ��ʱ��
		// ���Զ��ұ�--
		if ( m_LeftSize > 0 )
		{
			--m_LeftSize;
		}
		else
		if ( m_RightSize == 1 )
		{
			--m_RightSize;
		}
	}
	else
	{
		--m_LeftSize;
	}
}

template<class T>
void myStl2DirDeque<T>::pop_back()
{
	if ( m_RightSize <= 0 )
	{
		_redivideData( false );

		// �����ұ���һ��Ԫ�ض�����--
		// ���ұ�û��Ԫ�أ�֤�����ֻ��һ��
		// ��Ϊ����ߵ�Ԫ���������ڵ���2ʱ��
		// �ұ����ֵܷ�һ��,���ԣ��ұ�û��Ԫ��ʱ
		// ���Զ���߽���--������
		if ( m_RightSize > 0 )
		{
			--m_RightSize;
		}
		else
		if ( m_LeftSize == 1 )
		{
			--m_LeftSize;
		}
	}
	else
	{
		--m_RightSize;
	}
}

template<class T>
void myStl2DirDeque<T>::push_front( const T &val )
{
	if ( m_LeftSize>= m_LeftCapacity)
	{
		_realloc( GET_NEW_CAPACITY( m_LeftCapacity ), true );
	}

	m_pLeftData[m_LeftSize] = val;
	++m_LeftSize;

	// �����������ˣ���һ��Ԫ�ظ���
	if ( m_RightSize <= 0 )
	{
		_redivideData( false );
	}
}

template<class T>
void myStl2DirDeque<T>::push_back( const T &val )
{
	if ( m_RightSize >= m_RightCapacity )
	{
		_realloc( GET_NEW_CAPACITY( m_RightCapacity ), false );
	}

	m_pRightData[m_RightSize] = val;
	++m_RightSize;

	// �����������ˣ���һ��Ԫ�ظ���
	if ( m_LeftSize <= 0 )
	{
		_redivideData( true );
	}
}

template<class T>
void myStl2DirDeque<T>::_redivideData( bool isLeft )
{
	size_t preSize = m_LeftSize+m_RightSize;
	size_t preLeftSize = preSize/2;
	size_t preRightSize = preSize-preLeftSize;

	if ( isLeft )
	{
		_realloc( preLeftSize, true );

		size_t curMoveIndex = 0;
		for ( int i=(int)preLeftSize-1; i>-1; --i )
		{
			m_pLeftData[i] = m_pRightData[curMoveIndex++];
		}

		for ( size_t i=0; i<(int)preRightSize; ++i )
		{
			m_pRightData[i] = m_pRightData[curMoveIndex++];
		}
	}
	else
	{
		_realloc( preRightSize, false );

		size_t curMoveIndex = 0;
		for ( int i=(int)preRightSize-1; i>-1; --i )
		{
			m_pRightData[i] = m_pLeftData[curMoveIndex++];
		}

		for ( size_t i=0; i<(int)preLeftSize; ++i )
		{
			m_pLeftData[i] = m_pLeftData[curMoveIndex++];
		}
	}

	m_RightSize = preRightSize;
	m_LeftSize = preLeftSize;
}

template<class T>
void myStl2DirDeque<T>::_realloc( size_t count, bool isLeft )
{
	static T *pTemp;
	if ( isLeft )
	{
		if ( count > m_LeftCapacity )
		{
			pTemp = new T[count];
			for ( size_t i=0; i<m_LeftSize; ++i )
			{
				pTemp[i] = m_pLeftData[i];
			}
			SAFE_DELARR(m_pLeftData);

			m_pLeftData = pTemp;
			m_LeftCapacity = count;
		}
	}
	else
	{
		if ( count > m_RightCapacity)
		{
			pTemp = new T[count];
			for ( size_t i=0; i<m_RightSize; ++i )
			{
				pTemp[i] = m_pRightData[i];
			}
			SAFE_DELARR(m_pRightData);

			m_pRightData = pTemp;
			m_RightCapacity = count;
		}
	}
}

#endif	// END MYSTL2DIRDEQUE