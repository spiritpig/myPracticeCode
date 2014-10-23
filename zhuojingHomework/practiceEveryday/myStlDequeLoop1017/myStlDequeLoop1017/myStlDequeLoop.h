#ifndef MYSTLDEQUELOOP
#define MYSTLDEQUELOOP

#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }
#define GET_NEW_CAPACITY(c) ( c + c/2 + 1 )

template<class T>
class myStlDequeLoop
{
public:
	struct iterator
	{
		iterator()
			: pt ( NULL ), 
			  rightSide( NULL ), leftSide( NULL )
		{
		}
		iterator( const iterator &iter ) 
			: pt( iter.pt ), 
			  rightSide( iter.rightSide ),
              leftSide( iter.leftSide )
		{
		}

		iterator& operator++()
		{
			++sit;
			++pt;
			if (pt > rightSide)
			{
				pt = leftSide;
			}
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp = *this;

			++sit;
			++pt;
			if (pt > rightSide)
			{
				pt = leftSide;
			}
			return temp;
		}
		iterator& operator--()
		{
			--sit;
			--pt;
			if (pt < leftSide)
			{
				pt = rightSide;
			}
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp = *this;

			--sit;
			--pt;
			if (pt < leftSide)
			{
				pt = rightSide;
			}
			return temp;
		}

		iterator& operator+( int n )
		{
			if ( n > 0 )
			{
				if ( n > (rightSide-pt) )
				{
					pt = leftSide + n - rightSide + pt;
				} 
				else
				{
					pt += n;
				}
			}
			else
			{
				if ( n < (leftSide-pt) )
				{
					pt = rightSide + n - leftSide + pt;
				} 
				else
				{
					pt += n;
				}
			}
			sit += n;

			return *this;
		}

		bool operator==( const iterator &iter )
		{
			return (this->pt == iter.pt);
		}
		bool operator!=( const iterator &iter )
		{
			return (this->pt != iter.pt);
		}

		T& operator*()
		{
			return *pt;
		}

	public:
		T *pt;
		T *leftSide,*rightSide;
		int sit;
	};
public:
	myStlDequeLoop();
	~myStlDequeLoop();

	iterator& begin()
	{
		first.pt = &m_pData[m_LeftIndex];
		first.leftSide = &m_pData[0];
		first.rightSide = &m_pData[m_Capacity-1];
		first.sit = 0;

		return first;
	}
	iterator& end()
	{
		last.pt = &m_pData[m_RightIndex+1];
		last.leftSide =  &m_pData[0];
		last.rightSide =  &m_pData[m_Capacity-1];
		last.sit = (int)m_Size;

		return last;
	}

	
	void insert( const iterator &pos, const T &val );
	void erase( const iterator &pos );
	void pop_front();
	void push_front( const T &val );
	void pop_back();
	void push_back( const T &val );

private:
	void _realloc( size_t count );

	T *m_pData;
	int m_LeftIndex, m_RightIndex;
	size_t m_Size, m_Capacity;

	iterator first, last;
};

template<class T>
myStlDequeLoop<T>::myStlDequeLoop()
:	m_pData( NULL ), 
	m_LeftIndex( 0 ), m_RightIndex( 0 ),
	m_Size( 0 ), m_Capacity( 0 )
{
}

template<class T>
myStlDequeLoop<T>::~myStlDequeLoop()
{
	SAFE_DELARR( m_pData );
}

template<class T>
void myStlDequeLoop<T>::insert( const iterator &pos, const T &val )
{
	if ( m_Size >= m_Capacity )
	{
		_realloc( GET_NEW_CAPACITY(m_Capacity) );
	}

	++m_Size;
	m_RightIndex = (m_RightIndex+1)%(int)m_Capacity;
	// 后移元素
	int cur = m_RightIndex;
	int prev = m_RightIndex-1 < 0 ? (int)m_Capacity-1 : m_RightIndex-1;
	int endPos = (m_LeftIndex + pos.sit)%(int)m_Capacity;
	while ( cur != endPos )
	{
		m_pData[cur] = m_pData[prev];

		cur = prev;
		prev = prev-1 < 0 ? (int)m_Capacity-1 : prev-1;
	}

	m_pData[endPos] = val;
}

template<class T>
void myStlDequeLoop<T>::erase( const iterator &pos )
{
	--m_Size;
	// 前移元素
	int cur = (m_LeftIndex + pos.sit)%(int)m_Capacity;
	int next = (cur+1)%(int)m_Capacity;
	int endPos = m_RightIndex;
	while ( cur != endPos )
	{
		m_pData[cur] = m_pData[next];

		cur = next;
		next = (next+1)%(int)m_Capacity;
	}

	m_RightIndex = m_RightIndex-1 < 0 ? (int)m_Capacity-1 : m_RightIndex-1;
}

template<class T>
void myStlDequeLoop<T>::pop_front()
{
	if ( m_Size > 0 )
	{
		m_LeftIndex = (m_LeftIndex+1)%(int)m_Capacity;
		--m_Size;
	}
}

template<class T>
void myStlDequeLoop<T>::push_front( const T &val )
{
	if ( m_Size >= m_Capacity )
	{
		_realloc( GET_NEW_CAPACITY(m_Capacity) );
	}

	// 下标保持循环状态
	--m_LeftIndex;
	m_LeftIndex = m_LeftIndex < 0 ? (int)m_Capacity-1 : m_LeftIndex;
	m_pData[m_LeftIndex] = val;
	++m_Size;
}

template<class T>
void myStlDequeLoop<T>::pop_back()
{
	if ( m_Size > 0 )
	{
		--m_RightIndex;
		m_RightIndex = m_RightIndex < 0 ? (int)m_Capacity-1 : m_RightIndex ;
		--m_Size;
	}
}

template<class T>
void myStlDequeLoop<T>::push_back( const T &val )
{
	if ( m_Size >= m_Capacity )
	{
		_realloc( GET_NEW_CAPACITY(m_Capacity) );
	}

	// 下标保持循环状态
	m_RightIndex = (m_RightIndex+1)%(int)m_Capacity;
	m_pData[m_RightIndex] = val;
	++m_Size;
}

template<class T>
void myStlDequeLoop<T>::_realloc( size_t count )
{
	static T *pTemp;
	pTemp = new T[count];
	for ( size_t i=0; i<m_Size; ++i )
	{
		pTemp[i] = m_pData[(m_LeftIndex+i) % m_Capacity];
	}
	SAFE_DELARR(m_pData);
	m_pData = pTemp;

	m_LeftIndex = 0;
	m_RightIndex = (int)m_Size-1;
	m_Capacity = count;
}

#endif	// END MYSTLDEQUELOOP