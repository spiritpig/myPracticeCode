#ifndef MYSTLMAP
#define MYSTLMAP

#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }
#define SAFE_DELETE(p) { if(p) { delete p; p=NULL; } }
#define GET_NEW_CAPACITY(c) ( c + c/2 + 1 )

namespace mystd
{
	template<class T>
	class baseCompare
	{
	public:
		virtual bool operator()( const T &left, const T &right ) = 0;
	};

	template<class T>
	class less : public baseCompare<T>
	{
	public:
		virtual bool operator()( const T &left, const T &right )
		{
			return (left < right);
		}
	};

	template<class keyType, class valType>
	struct pair
	{
		pair()
		{
		}

		pair( const keyType &kt, const valType &val )
			: first( kt ), second( val )
		{
		}

		keyType first;
		valType second;
	};

	template<class keyType, class valType, class comp>
	class myStlMap
	{
	public:
		struct value_type
		{
			value_type()
			{
			}

			value_type( const keyType key, const valType val )
				:	first( key ), second( val )
			{
			}

			keyType first;
			valType second;
		};

	public:
		struct iterator
		{
			iterator()
				: pointer( NULL ) {}
			iterator( const iterator &iter )
				: pointer( iter.pointer ) {}

			value_type& operator*()
			{
				return (**pointer);
			}
			value_type* operator->()
			{
				return (*pointer);
			}

			iterator& operator=( const iterator &iter )
			{
				this->pointer = iter.pointer;
				return *this;
			}

			iterator& operator++()
			{
				++pointer;
				return *this;
			}
			iterator operator++(int)
			{
				iterator temp = *this;
				++pointer;
				return temp;
			}
			iterator& operator--()
			{
				--pointer;
				return *this;
			}
			iterator operator--(int)
			{
				iterator temp = *this;
				--pointer;
				return temp;
			}

			value_type** operator+( size_t pos )
			{
				return (pointer + pos);
			}
			value_type** operator-( size_t pos )
			{
				return (pointer - pos);
			}

			bool operator==(const iterator &other)
			{
				return pointer == other.pointer;
			}
			bool operator!=(const iterator &other)
			{
				return pointer != other.pointer;
			}
			bool operator!()
			{
				return !pointer;
			}

			value_type **pointer;
		};

	public:
		myStlMap();
		myStlMap( const myStlMap &msm );
		~myStlMap();

		void clear();

		size_t count( const keyType &key );
		bool empty();
		iterator find( const keyType &key )
		{
			iterator ret;
			ret.pointer = &m_pKeyTable[m_Size];

			if ( _binarySearch( key, 0, m_Size ) )
			{
				ret.pointer = &m_pKeyTable[m_Middle];
			}

			return ret;
		}

		pair<iterator, bool> insert( const value_type &val )
		{
			pair<iterator, bool> retPair;
			retPair.first.pointer = &m_pKeyTable[m_Size];
			retPair.second = false;

			if ( _binarySearch( val.first, 0, (int)m_Size ) )
			{
				retPair.first.pointer = &m_pKeyTable[m_Middle];
				retPair.second = true;
			}
			else
			{
				if ( m_Size >= m_Capacity )
				{
					_realloc( GET_NEW_CAPACITY( m_Capacity ) );
				}
				
				int insertPos = _getInsertPos( val );
				retPair.first.pointer = &m_pKeyTable[insertPos];
				retPair.second = true;

				for ( int i=(int)m_Size; i>insertPos; --i )
				{
					m_pKeyTable[i] = m_pKeyTable[i-1];
				}
				m_pKeyTable[insertPos] = new value_type;
				m_pKeyTable[insertPos]->first = val.first;
				m_pKeyTable[insertPos]->second = val.second;
				++m_Size;	
			}


			return retPair;
		}

		iterator begin()
		{
			first.pointer = &m_pKeyTable[0];
			return first;
		}
		iterator end()
		{
			last.pointer = &m_pKeyTable[m_Size];
			return last;
		}

	private:

		void _realloc( size_t count );
		// 二分搜索，区间为左闭右开 [left , right)
		bool _binarySearch( const keyType &key, int left, int right )
		{
			m_Left = left;
			m_Right = right;
			m_Middle  = left;

			while( m_Left < m_Right )
			{
				m_Middle = (m_Left + m_Right) / 2;

				if ( key == m_pKeyTable[m_Middle]->first )
				{
					return true;
				}
				else
					if ( compare( key, m_pKeyTable[m_Middle]->first ) )
					{
						m_Right = m_Middle;
					}
					else
					{
						m_Left = m_Middle + 1;
					}
			}

			return false;
		}

		//////////////////////////////////////////////////////////////////////////
		//
		//	获取插入位置
		//	在完成了一次失败的二分搜索之后，m_Right的附近一定存在适合插入当前元素的位置
		//	[ m_Right-1, m_Right+1 ],这个位置符合其前一个的key值小于val的key值，同时，
		//  该位置的key值大于val的key值

		//  注意： 仅在一次二分查找失败以后调用，才能正确工作
		//
		//////////////////////////////////////////////////////////////////////////
		int _getInsertPos( const value_type &val )
		{
			int insertPos = m_Right-1;

			if ( (insertPos+1 >= (int)m_Size) ||
				m_pKeyTable[insertPos+1]->first > val.first )
			{
				insertPos += 1;
			}
			else
			if ( (insertPos+2 >= (int)m_Size) || 
				m_pKeyTable[insertPos+2]->first > val.first )
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

		value_type **m_pKeyTable;
		size_t m_Size;
		size_t m_Capacity;

		// 比较类
		comp compare;

		// 用于二分查找的三个变量
		int m_Left,m_Middle,m_Right;

		iterator first, last;
	};

	template<class keyType, class valType, class comp>
	myStlMap<keyType, valType, comp>::myStlMap()
	:	m_pKeyTable( NULL ),
		m_Size( 0 ), m_Capacity( 0 )
	{
	}

	template<class keyType, class valType, class comp>
	myStlMap<keyType, valType, comp>::myStlMap( const myStlMap &msm )
	:	m_pKeyTable( NULL ),
		m_Size( 0 ), m_Capacity( 0 )
	{
		if ( msm.m_Size > 0 )
		{
			m_pKeyTable = new value_type *[msm.m_Size];
			for ( size_t i=0; i<msm.m_Size; ++i )
			{
				m_pKeyTable[i] = new value_type;
				m_pKeyTable[i]->first = msm.m_pKeyTable[i]->first;
				m_pKeyTable[i]->second = msm.m_pKeyTable[i]->second;
			}

			m_Size = msm.m_Size;
			m_Capacity = msm.m_Size;
		}
	}

	template<class keyType, class valType, class comp>
	myStlMap<keyType, valType, comp>::~myStlMap()
	{
		clear();
	}

	template<class keyType, class valType, class comp>
	void myStlMap<keyType, valType, comp>::clear()
	{
		for ( size_t i=0; i<m_Size; ++i )
		{
			SAFE_DELETE( m_pKeyTable[i] );
		}
		SAFE_DELARR( m_pKeyTable );
	}

	template<class keyType, class valType, class comp>
	size_t myStlMap<keyType, valType, comp>::count( const keyType &key )
	{
		if ( _binarySearch( key, 0, m_Size ) )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	template<class keyType, class valType, class comp>
	bool myStlMap<keyType, valType, comp>::empty()
	{
		return (m_Size == 0);
	}

	template<class keyType, class valType, class comp>
		void mystd::myStlMap<keyType, valType, comp>::_realloc( size_t count )
	{
		static value_type **pTemp;
		pTemp = new value_type *[count];
		for ( size_t i=0; i<m_Size; ++i )
		{
			pTemp[i] = m_pKeyTable[i];
		}
		SAFE_DELARR( m_pKeyTable );
		m_pKeyTable = pTemp;

		m_Capacity = count;
	}

}

#endif	// END MYSTLMAP
