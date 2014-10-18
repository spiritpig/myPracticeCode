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
				// 处于左边最后一个，需要跳转到右边去
				// 否则，在左边其他位置直接--
				if ( pt == leftPT )
				{
					pt = rightPT;
					isLeft = false;
				}
				else
				{
					// ++对于左边来说是--，下标减小的方向移动
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
				// --对于左边来说是++，向下标增大的方向移动
				++pt;
			}
			else
			{
				// 处于右边第一个位置，需要跳转到左边去
				// 否则，在右边其他位置直接++
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
		// 此处决定采用无符号整形，基于一点考虑
		// 当sit不正确的时候，比如小于0，大于最大元素个数
		// 此时，sit即使表示正确，pt的位置实际上已经错了
		// 所以，选用无符号整形，即使本应小于0的数变为很大
		// 的数，并不影响错了这个事实。
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
			throw std::out_of_range( "溢出了" );
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

		// 哪怕左边有一个元素都可以--
		// 若左边没有元素，证明右边只有一个
		// 因为，右边的元素数量大于等于2时，
		// 左边总能分到一个,所以，左边没有元素时，
		// 可以对右边--
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

		// 哪怕右边有一个元素都可以--
		// 若右边没有元素，证明左边只有一个
		// 因为，左边的元素数量大于等于2时，
		// 右边总能分到一个,所以，右边没有元素时
		// 可以对左边进行--操作。
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

	// 若左边数组空了，分一半元素给它
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

	// 若左边数组空了，分一半元素给它
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