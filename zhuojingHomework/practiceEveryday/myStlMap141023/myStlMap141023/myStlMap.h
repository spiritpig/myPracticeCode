#ifndef MYSTLMAP
#define MYSTLMAP

#define SAFE_DELETE(p) { if(p) { delete p; p=NULL; } }
#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }
#define GET_BIGGER_CAPACITY(c) ( c + c/2 + 1 )

template<class k, class v>
struct mypair
{
	k first;
	v second;
};

template<class k, class v, class comp>
class myStlMap
{
public:
	struct value_type
	{
		value_type()
		{
		}

		value_type( const k &ik, const v &iv )
			: key(ik), val(iv)
		{
		}

		k key;
		v val;
	};

public:
	struct iterator
	{
		iterator()
			: pt( NULL )
		{
		}
		iterator( const iterator &iter )
			: pt( iter.pt )
		{
		}

		iterator& operator=( const iterator &iter )
		{
			pt = iter.pt;
			return *this;
		}

		iterator& operator+( int n )
		{
			pt += n;
			return *this;
		}
		iterator& operator-( int n )
		{
			pt -= n;
			return *this;
		}
		int operator-( const iterator &iter )
		{
			return (this->pt - iter.pt);
		}

		iterator& operator++()
		{
			++pt;
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp = *this;
			++pt;
			return temp;
		}
		iterator& operator--()
		{
			--pt;
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp = *this;
			--pt;
			return temp;
		}

		value_type& operator*()
		{
			return **pt;
		}
		value_type* operator->()
		{
			return *pt;
		}

		bool operator==( const iterator &iter )
		{
			return (pt == iter.pt);
		}
		bool operator!=( const iterator &iter )
		{
			return (pt != iter.pt);
		}

	public:
		value_type **pt;
	};

public:
	myStlMap();
	~myStlMap();

	bool empty()
	{
		return m_Size == 0;
	}

	iterator& begin() 
	{
		first.pt = &m_pData[0];

		return first;
	}
	iterator& end()
	{
		last.pt = &m_pData[m_Size];

		return last;
	}

	iterator find( const k &key )
	{
		iterator retIter;
		retIter.pt = NULL;

		if ( _binarySearch( 0, m_Size, key ) )
		{
			retIter.pt = &m_pData[m_bsMid];
		}

		return retIter;
	}

	iterator lower_bound( const k &key )
	{
		iterator retIter;
		retIter.pt = NULL;

		// map中，每个键值只能存在一个，所以，找到的话
		// 它的下一个一定比它大, 对于不存在更大键值的情况，
		// 返回空迭代器
		if ( _binarySearch( 0, (int)m_Size, key ) )
		{
			retIter.pt = &m_pData[m_bsMid];
		}
		else
		{
			if ( m_bsRight < (int)m_Size ) 
			{
				retIter.pt = &m_pData[m_bsRight];
			}
		}

		return retIter;
	}
	iterator upper_bound( const k &key )
	{
		iterator retIter;
		retIter.pt = NULL;

		// map中，每个键值只能存在一个，所以，找到的话
		// 它的下一个一定比它大, 对于不存在更大键值的情况，
		// 返回空迭代器
		if ( _binarySearch( 0, (int)m_Size, key ) )
		{
			if ( m_bsMid < (int)m_Size-1 )
			{
				retIter.pt = &m_pData[m_bsMid+1];
			}
		}
		else
		if( m_bsMid <= 0 )
		{
			retIter.pt = &m_pData[0];
		}

		return retIter;
	}
	
	iterator erase( iterator iter )
	{
		iterator retIter;

		// 空迭代器，返回
		if ( iter.pt == NULL )
		{
			return retIter;
		}

		--m_Size;
		retIter.pt = iter.pt;
		for ( iter; iter!= end(); ++iter )
		{
			*iter.pt = *(iter.pt + 1);
		}

		return retIter;
	}

	// 单个元素的插入操作，具体的插入位置，由元素的key值与
	// 数据表中元素key值的相对大小决定。
	mypair<iterator,bool> insert( const value_type &v )
	{
		mypair<iterator,bool> retPair;
		retPair.first.pt = &m_pData[m_Size];
		retPair.second = false;

		if ( _binarySearch( 0, (int)m_Size, v.key ) )
		{
			retPair.first.pt = &m_pData[m_bsMid];
		}
		else
		{
			retPair.second = true;
			if ( m_Size >= m_Capacity )
			{
				_realloc( GET_BIGGER_CAPACITY( m_Capacity ) );
			}
			
			int iIndex=_getInsertPos( v.key );
			for ( int i=(int)m_Size; i>iIndex; --i )
			{
				m_pData[i] = m_pData[i-1];
			}
			m_pData[iIndex] = new value_type;
			m_pData[iIndex]->key = v.key;
			m_pData[iIndex]->val = v.val;

			retPair.first.pt = &m_pData[iIndex];
			++m_Size;
		}

		return retPair;
	}

	void swap( myStlMap &right);
	 
private:
	bool _binarySearch( int left, int right, const k &key );
	int _getInsertPos( const k &key );
	void _realloc( size_t count );

	value_type **m_pData;
	size_t m_Size;
	size_t m_Capacity;

	int m_bsLeft, m_bsRight, m_bsMid;
	comp compare;

	iterator first, last;
};

template<class k, class v, class comp>
myStlMap<k, v, comp>::myStlMap()
:	m_pData( NULL ),
m_Size( 0 ), m_Capacity( 0 )
{
}

template<class k, class v, class comp>
myStlMap<k, v, comp>::~myStlMap()
{
	for ( size_t i=0; i<m_Size; ++i )
	{
		SAFE_DELETE( m_pData[i] );
	}
	SAFE_DELARR( m_pData );
}

template<class k, class v, class comp>
void myStlMap<k, v, comp>::swap( myStlMap &right )
{
	static value_type **temp;
	temp = this->m_pData;
	this->m_pData = right.m_pData;
	right.m_pData = temp;

	static size_t tempNum;
	tempNum = this->m_Size;
	this->m_Size = right.m_Size;
	right.m_Size = tempNum;

	tempNum = this->m_Capacity;
	this->m_Capacity = right.m_Capacity;
	right.m_Capacity = tempNum;
}

template<class k, class v, class comp>
int myStlMap<k, v, comp>::_getInsertPos( const k &key )
{
	int insertPos = m_bsRight-1;

	if ( (insertPos+1 >= (int)m_Size) ||
		m_pData[insertPos+1]->key > key )
	{
		insertPos += 1;
	}
	else
	if ( (insertPos+2 >= (int)m_Size) || 
		m_pData[insertPos+2]->key > key )
	{
		insertPos += 2;
	}
	else
	if ( insertPos < 0 )
	{
		insertPos = 0;
	}

	return insertPos;
}

template<class k, class v, class comp>
bool myStlMap<k, v, comp>::_binarySearch(  int left, int right, const k &key )
{
	m_bsLeft = left;
	m_bsRight = right;
	m_bsMid = left;
	
	while ( m_bsLeft < m_bsRight )
	{
		m_bsMid = (m_bsLeft + m_bsRight)/2;
		if ( key == m_pData[m_bsMid]->key )
		{
			return true;
		}
		else
		if( compare( key, m_pData[m_bsMid]->key ) )
		{
			m_bsRight = m_bsMid;
		}
		else
		{
			m_bsLeft = m_bsMid+1;
		}
	}

	return false;
}

template<class k, class v, class comp>
void myStlMap<k, v, comp>::_realloc( size_t count )
{
	static value_type** pTemp;
	pTemp = new value_type*[count];
	for ( size_t i=0; i<m_Size; ++i )
	{
		pTemp[i] = m_pData[i];
	}
	SAFE_DELARR( m_pData );

	m_pData = pTemp;
	m_Capacity = count;
}

#endif	// END MYSTLMAP