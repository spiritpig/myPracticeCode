#ifndef DEQUELOOP
#define DEQUELOOP

#define SAFE_DELARR(p) { if(p) { delete []p; p = NULL; } }
#define GET_NEW_CAPACITY(s) ( s+s/2+1 )

template<class T>
class myDequeLoop
{
public:
	struct iterator 
	{
		iterator()
			:	pointer( NULL ), sit( 0 )
		{
		}

		int operator-( const iterator &iter )
		{
			return (int)(sit - iter.sit);
		}
		T* operator+( int n )
		{
			if ( n >= 0 )
			{
				int space = (int)(endPos - pointer);
				if ( n <= space  )
				{
					return (pointer + n);
				}
				else
				{
					return (startPos + n - space - 1);
				}
			}
			else
			{
				int space = (int)(pointer - startPos);
				if ( n <= space  )
				{
					return (pointer + n);
				}
				else
				{
					return (endPos + n - space - 1);
				}
			}
		}

		iterator& operator++()
		{
			++sit;
			++pointer;
			if ( pointer > endPos )
			{
				pointer = startPos;
			}

			return *this;
		}
		iterator operator++(int)
		{
			iterator temp = *this;

			++sit;
			++pointer;
			if ( pointer > endPos )
			{
				pointer = startPos;
			}

			return temp;
		}

		iterator& operator--()
		{
			--sit;
			--pointer;
			if ( pointer < startPos )
			{
				pointer = endPos;
			}

			return *this;
		}
		iterator operator--(int)
		{
			iterator temp = *this;

			--sit;
			--pointer;
			if ( pointer < startPos )
			{
				pointer = endPos;
			}

			return temp;
		}

		T& operator*()
		{
			return *pointer;
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
		T *startPos, *endPos;
		size_t sit;
	};

public:
	myDequeLoop()
		:	m_pData( NULL ),
			m_FirstIndex( 0 ), m_LastIndex( 0 ),
			m_Size( 0 ), m_Capacity( 0 )
	{
	}

	bool empty()
	{
		return (m_Size <= 0);
	}
	size_t size() const
	{ 
		return m_Size;
	}
	size_t capacity() const
	{
		return m_Capacity;
	}

	T& front()
	{
		return m_pData[m_FirstIndex];
	}
	T& back()
	{
		return m_pData[m_LastIndex];
	}

	iterator& begin()
	{
		first.pointer = &m_pData[m_FirstIndex];
		first.startPos = &m_pData[0];
		first.endPos = &m_pData[m_Capacity-1];
		first.sit = 0;

		return first;
	}
	iterator& end()
	{
		last.pointer = &m_pData[m_LastIndex+1];
		last.startPos = &m_pData[0];
		last.endPos = &m_pData[m_Capacity-1];
		last.sit = m_Size+1;

		return last;
	}

	void pop_front();
	void push_front( const T &val );
	void pop_back();
	void push_back( const T &val );

private:
	void _adjustIndex( int &index );
	void _processReAlloc( size_t count );

	T *m_pData;
	int m_FirstIndex;
	int m_LastIndex;
	size_t m_Size;
	size_t m_Capacity;

	iterator first;
	iterator last;
};

template<class T>
void myDequeLoop<T>::pop_front()
{
	if ( m_Size > 0 )
	{
		--m_Size;
		_adjustIndex( ++m_FirstIndex );
	}
}

template<class T>
void myDequeLoop<T>::push_front( const T &val )
{
	if( m_Size >= m_Capacity )
	{
		_processReAlloc( GET_NEW_CAPACITY(m_Capacity) );
	}

	++m_Size;
	_adjustIndex( --m_FirstIndex );
	m_pData[m_FirstIndex] = val;
}

template<class T>
void myDequeLoop<T>::pop_back()
{
	if ( m_Size > 0 )
	{
		--m_Size;
		_adjustIndex( --m_LastIndex );
	}
}

template<class T>
void myDequeLoop<T>::push_back( const T &val )
{
	if( m_Size >= m_Capacity )
	{
		_processReAlloc( GET_NEW_CAPACITY(m_Capacity) );
	}

	++m_Size;
	_adjustIndex( ++m_LastIndex );
	m_pData[m_LastIndex] = val;
}

template<class T>
void myDequeLoop<T>::_adjustIndex( int &index )
{
	index = index<0 ? ((int)m_Capacity-1): (index%(int)m_Capacity);
}

template<class T>
void myDequeLoop<T>::_processReAlloc( size_t count )
{
	// 重新分配数据空间
	// 为了接下来对数据的操作方便，将有效数据
	// 移动到 [0 , size-1) 的区间内
	if ( count > m_Capacity )
	{
		static T *temp;
		temp = new T[count];
		for ( size_t i=0; i<m_Size; ++i )
		{
			temp[i] = m_pData[m_FirstIndex];
			_adjustIndex( ++m_FirstIndex );
		}
		SAFE_DELARR( m_pData );
		m_pData = temp;

		m_FirstIndex = 0;
		m_LastIndex = (int)m_Size-1;
		m_Capacity = count;
	}
}

#endif	// END DEQUELOOP