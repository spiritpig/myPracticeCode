#ifndef MYDEQUE2DIR
#define MYDEQUE2DIR

#define SAFE_DELARR(p) { if(p) { delete []p; p = NULL; } }
#define CALC_NEWSIZE(s) ( s+s/2+1 )

template<class T>
class myDeque2Dir
{
public:
	struct iterator
	{
		iterator()
			: pointer( NULL ), 
			  leftData( NULL ), leftSize( 0 ),
			  rightData( NULL ), rightSize( 0 ),
			  sit( -1 ), isLeft( true )
		{
		}
		iterator( const iterator &iter )
			: pointer( iter.pointer ), 
			  leftData( iter.leftData ), leftSize( iter.leftSize ),
			  rightData( iter.rightData), rightSize( iter.rightSize ),
			  sit( iter.sit ), isLeft( true )
		{
		}

		T& operator*()
		{
			return *pointer;
		}
		
		iterator& operator=( const iterator &iter )
		{
			this->pointer = iter.pointer;
			this->leftData = iter.leftData;
			this->leftSize = iter.leftSize;
			this->rightData = iter.rightData;
			this->rightSize = iter.rightSize;
			this->sit = iter.sit;

			return *this;
		}

		iterator& operator++()
		{
			if ( isLeft )
			{
				// 如果，已经处于左边数组的最后一个（下标为0的位置）了，
				// 跳转到右边数组的第一个去
				if( pointer == leftData )
				{
					pointer = rightData;
					isLeft = false;
				}
				else
				{
					--pointer;
				}
			}
			else
			{
				++pointer;
			}
			++sit;

			return *this;
		}

		iterator operator++(int)
		{
			iterator temp = *this;

			if ( isLeft )
			{
				// 如果，已经处于左边数组的最后一个（下标为0的位置）了，
				// 跳转到右边数组的第一个去
				if( pointer == leftData )
				{
					pointer = rightData;
					isLeft = false;
				}
				else
				{
					--pointer;
				}
			}
			else
			{
				++pointer;
			}
			++sit;

			return temp;
		}

		iterator& operator--()
		{
			if ( isLeft )
			{
				++pointer;
			}
			else
			{
				// 如果，已经处于右边数组的最后一个（下标为0的位置）了，
				// 跳转到左边数组的第一个去
				if( pointer == rightData )
				{
					pointer = leftData;
					isLeft = true;
				}
				else
				{
					--pointer;
				}
			}
			--sit;

			return *this;
		}

		iterator operator--(int)
		{
			iterator temp = *this;

			if ( isLeft )
			{
				// 如果，已经处于左边数组的最后一个（下标为0的位置）了，
				// 跳转到右边数组的第一个去
				if( pointer == leftData )
				{
					pointer = rightData;
					isLeft = false;
				}
				else
				{
					--pointer;
				}
			}
			else
			{
				++pointer;
			}
			--sit;

			return temp;
		}

		T* operator+( int n ) const
		{
			static int curPos;
			curPos = (int)(pointer - leftData);

			if ( n-curPos > 0 )
			{
				return (rightData + (n - curPos - 1));
			}
			else
			{
				return (pointer - n);
			}
		}

		size_t operator-( const iterator &iter ) const
		{
			return (size_t)(sit - iter.sit);
		}

		bool operator==( const iterator &iter )
		{
			return (pointer == iter.pointer);
		}
		bool operator!=( const iterator &iter )
		{
			return (pointer != iter.pointer);
		}

	public:
		T *pointer;
		size_t sit;

		T *leftData;
		size_t leftSize;

		T *rightData;
		size_t rightSize;

		bool isLeft;
	};
public:
	myDeque2Dir();
	myDeque2Dir( const myDeque2Dir &md2Dir );
	~myDeque2Dir();

	size_t size() const
	{
		return m_LeftSize+m_RightSize;
	}
	bool empty()
	{
		return (m_LeftSize+m_RightSize) <= 0;
	}
	void pop_front();
	void pop_back();
	void push_front( const T &val );
	void push_back( const T &val );

	T& operator[]( size_t index )
	{
		static size_t dataIndex;

		dataIndex = m_LeftSize - index - 1;
		if ( index < m_LeftSize )
		{
			return m_pLeftData[dataIndex];
		}
		else
		{
			return m_pRightData[m_RightSize+dataIndex];
		}
	}

	T& front()
	{
		if ( m_LeftSize > 0 )
		{
			return m_pLeftData[m_LeftSize-1];
		}
		else
		{
			return m_pRightData[0];
		}
	}
	T& back()
	{
		if ( m_RightSize > 0 )
		{
			return m_pRightData[m_RightSize-1];
		}
		else
		{
			return m_pLeftData[0];
		}
	}

	iterator& begin()
	{
		first.pointer = &m_pLeftData[m_LeftSize-1];
		first.isLeft = true;
		first.leftData = m_pLeftData;
		first.rightData = m_pRightData;
		first.leftSize = m_LeftSize;
		first.rightSize = m_RightSize;
		first.sit = 0;

		return first;
	}
	iterator& end()
	{
		last.pointer = &m_pRightData[m_RightSize];
		last.isLeft = true;
		last.leftData = m_pLeftData;
		last.rightData = m_pRightData;
		last.leftSize = m_LeftSize;
		last.rightSize = m_RightSize;
		last.sit = m_LeftSize+m_RightSize;

		return last;
	}
	void assign( const iterator &left, const iterator &right );

private:
	// 将数据重新平分到左右数组中
	void _reDivideData( bool isLeft );
	void _processRealloc( bool isLeft, size_t count );

	T *m_pLeftData;
	T *m_pRightData;

	size_t m_LeftSize;
	size_t m_LeftCapacity;
	size_t m_RightSize;
	size_t m_RightCapacity;

	iterator first;
	iterator last;
};

template<class T>
myDeque2Dir<T>::myDeque2Dir()
:	m_pLeftData( NULL ), m_LeftSize( 0 ),
	m_LeftCapacity( 0 ),
	m_pRightData( NULL ), m_RightSize( 0 ),
	m_RightCapacity( 0 )
{
}

template<class T>
myDeque2Dir<T>::myDeque2Dir( const myDeque2Dir &md2Dir )
{
	m_LeftSize = md2Dir.m_LeftSize;
	m_LeftCapacity = md2Dir.m_LeftSize;

	m_RightSize = md2Dir.m_RightSize;
	m_RightCapacity = md2Dir.m_RightSize;

	m_pLeftData = new T[m_LeftSize];
	for ( int i=0; i<m_LeftSize; ++i )
	{
		m_pLeftData[i] = md2Dir.m_pLeftData[i];
	}

	m_pRightData = new T[m_RightSize];
	for ( int i=0; i<m_RightSize; ++i )
	{
		m_pRightData[i] = md2Dir.m_pRightData[i];
	}
}

template<class T>
myDeque2Dir<T>::~myDeque2Dir()
{
	SAFE_DELARR( m_pLeftData );
	SAFE_DELARR( m_pRightData );
}

template<class T>
void myDeque2Dir<T>::pop_front()
{
	// 队列为空，直接返回即可
	if ( (m_LeftSize+m_RightSize) <= 0 )
	{
		return;
	}

	// 弹出数据，若右边数组为空，则分一半左边的数据给右边
	if ( m_LeftSize>0 )
	{
		--m_LeftSize;
	}
	else
	{
		_reDivideData( true );
		// 弹出元素
		m_LeftSize > 0 ? --m_LeftSize : 
						 --m_RightSize;
	}
}

template<class T>
void myDeque2Dir<T>::pop_back()
{
	// 队列为空，直接返回即可
	if ( (m_LeftSize+m_RightSize) <= 0 )
	{
		return;
	}

	// 弹出数据，若右边数组为空，则分一半左边的数据给右边
	if ( m_RightSize>0 )
	{
		--m_RightSize;
	}
	else
	{
		_reDivideData( false );
		// 弹出元素
		m_RightSize > 0 ? --m_RightSize : 
						  --m_LeftSize;
	}
}

template<class T>
void myDeque2Dir<T>::push_front( const T &val )
{
	// 数据压入
	if ( m_LeftSize >= m_LeftCapacity )
	{
		_processRealloc( true, CALC_NEWSIZE(m_LeftCapacity) );
	}
	m_pLeftData[m_LeftSize] = val;
	++m_LeftSize;

	// 若右边为空，将左边数组元素的一半分给右边
	if ( m_RightSize <= 0)
	{
		_reDivideData( false );
	}
}

template<class T>
void myDeque2Dir<T>::push_back( const T &val )
{
	// 数据压入
	if ( m_RightSize >= m_RightCapacity )
	{
		_processRealloc( false, CALC_NEWSIZE(m_RightCapacity) );
	}
	m_pRightData[m_RightSize] = val;
	++m_RightSize;

	// 若左边为空，将右边数组元素的一半分给左边
	if ( m_LeftSize <= 0)
	{
		_reDivideData( true );
	}
}

template<class T>
void myDeque2Dir<T>::assign( const iterator &left, const iterator &right )
{
	size_t count = right - left;
	size_t newLeftCapacity = count/2;
	size_t newRightCapacity = count - newLeftCapacity;

	// 处理重新分配
	_processRealloc( true, newLeftCapacity );
	_processRealloc( false, newRightCapacity );

	int curMoveIndex = 0;
	// 移动元素到左边
	for ( int i=(int)newLeftCapacity-1; i>-1; --i )
	{
		m_pLeftData[i] = *(left+curMoveIndex);
		++curMoveIndex;
	}
	m_LeftSize = newLeftCapacity;

	// 移动元素到右边
	for ( size_t i=0; i<newRightCapacity; ++i )
	{
		m_pRightData[i] = *(left+curMoveIndex);
		++curMoveIndex;
	}
	m_RightSize = newRightCapacity;
}

// 在其中一边数组为空的时候，进行再分配
template<class T>
void myDeque2Dir<T>::_reDivideData( bool isLeft )
{
	size_t size = m_LeftSize+m_RightSize;
	size_t newLeftCapacity = size/2;
	size_t newRightCapacity = size - newLeftCapacity;

	// 处理重新分配
	_processRealloc( true, newLeftCapacity );
	_processRealloc( false, newRightCapacity );

	if( isLeft )
	{
		size_t curMoveIndex = 0;
		// 移动元素到左边
		for ( int i=(int)newLeftCapacity-1; i>-1; --i )
		{
			m_pLeftData[i] = m_pRightData[curMoveIndex++];
		}
		m_LeftSize = newLeftCapacity;

		// 移动元素到右边
		for ( size_t i=0; i<newRightCapacity; ++i )
		{
			m_pRightData[i] = m_pRightData[curMoveIndex++];
		}
		m_RightSize = newRightCapacity;
	}
	else
	{
		size_t curMoveIndex = 0;
		// 移动元素到右边
		for ( int i=(int)newRightCapacity-1; i>-1; --i )
		{
			m_pRightData[i] = m_pLeftData[curMoveIndex++];
		}
		m_RightSize = newRightCapacity;

		// 移动元素到左边
		for ( size_t i=0; i<newLeftCapacity; ++i )
		{
			m_pLeftData[i] = m_pLeftData[curMoveIndex++];
		}
		m_LeftSize = newLeftCapacity;

	}
}

template<class T>
void myDeque2Dir<T>::_processRealloc( bool isLeft, size_t count )
{
	static T *tempData;
	if ( isLeft && (count > m_LeftCapacity) )
	{
		tempData = new T[count];
		for ( size_t i=0; i<m_LeftSize; ++i )
		{
			tempData[i] = m_pLeftData[i];
		}

		SAFE_DELARR( m_pLeftData );
		m_pLeftData = tempData;
		m_LeftCapacity = count;
	}
	else
	if( count > m_RightCapacity )
	{
		tempData = new T[count];
		for ( size_t i=0; i<m_RightSize; ++i )
		{
			tempData[i] = m_pRightData[i];
		}

		SAFE_DELARR( m_pRightData );
		m_pRightData = tempData;
		m_RightCapacity = count;
	}
}

#endif	// END MYDEQUE2DIR