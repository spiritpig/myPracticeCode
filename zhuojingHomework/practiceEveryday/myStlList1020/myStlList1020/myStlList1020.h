#ifndef MYSTLLIST1020
#define MYSTLLIST1020

#define SAFE_DELETE(p) { if(p) { delete p; p=NULL; } }

template<class T>
struct Node
{
	Node()
		: next( NULL ), prev( NULL )
	{
	}

	T val;
	Node *next;
	Node *prev;
};

template<class T>
class myStlList1020
{
public:
	struct iterator
	{
		iterator()
			: nodePt( NULL )
		{}

		iterator( const iterator &iter )
			: nodePt( iter.nodePt ), sit( iter.sit )
		{}

		iterator& operator=( const iterator &iter )
		{
			nodePt = iter.nodePt;
			sit = iter.sit;

			return *this;
		}

		iterator& operator++()
		{
			nodePt = nodePt->next;
			++sit;

			return *this;
		}
		iterator operator++(int)
		{
			iterator temp = *this;

			nodePt = nodePt->next;
			++sit;

			return temp;
		}
		iterator& operator--()
		{
			nodePt = nodePt->prev;
			--sit;

			return *this;
		}
		iterator operator--(int)
		{
			iterator temp = *this;

			nodePt = nodePt->prev;
			--sit;

			return temp;
		}

		T& operator*()
		{
			return nodePt->val;
		}

		bool operator==( const iterator &iter )
		{
			return nodePt == iter.nodePt;
		}
		bool operator!=( const iterator &iter )
		{
			return nodePt != iter.nodePt;
		}

	public:
		Node<T> *nodePt;
		size_t sit;
	};

public:
	myStlList1020();
	myStlList1020( const myStlList1020<T> &otherList );
	~myStlList1020();

	size_t size() const
	{
		return m_Size;
	}

	iterator& begin()
	{
		first.nodePt = m_pHead;
		first.sit = 0;

		return first;
	}
	iterator& end()
	{
		last.nodePt = NULL;
		last.sit = m_Size;

		return last;
	}

	T& front() const
	{
		return m_pHead->val;
	}
	T& back() const
	{
		return m_pEnd->val;
	}

	iterator erase( iterator pos )
	{
		// 异常返回
		if ( pos.nodePt == NULL )
		{
			return pos;
		}

		if ( pos.nodePt == m_pHead )
		{
			m_pTemp = m_pHead;

			m_pHead = m_pHead->next;
			if ( m_pHead != NULL )
			{
				m_pHead->prev = NULL;
			}
		}
		else
		if( pos.nodePt == m_pEnd )
		{
			m_pTemp = m_pEnd;

			m_pEnd = m_pEnd->prev;
			m_pEnd->next = NULL;
		}
		else
		{
			m_pTemp = pos.nodePt;

			pos.nodePt->prev->next = pos.nodePt->next;
			pos.nodePt->next->prev = pos.nodePt->prev;
		}

		pos.nodePt = m_pTemp->next;
		SAFE_DELETE( m_pTemp );
		--m_Size;
		return pos;
	}

	//////////////////////////////////////////////////////////////////////////
	// 未测试的函数
	//////////////////////////////////////////////////////////////////////////
	iterator insert( iterator pos, iterator first, iterator last )
	{
		// 异常终止
		if ( first.nodePt == NULL )
		{
			return pos;
		}

		Node<T> *m_pTempHead = new Node<T>, *m_pTempEnd;
		m_pTempHead->val = first.nodePt->val;
		first.nodePt = first.nodePt->next;
		++m_Size;

		// 复制区间元素
		m_pRear = m_pTempHead;
		while ( first.nodePt != last.nodePt )
		{
			m_pRear->next = new Node<T>;
			m_pRear->next->val = first.nodePt->val;
			m_pRear->next->next = NULL;
			m_pRear->next->prev = m_pRear;

			m_pRear = m_pRear->next;
			first.nodePt = first.nodePt->next;
			++m_Size;
		}
		m_pTempEnd = m_pRear;

		// 找到插入位置
		if ( pos.nodePt == m_pHead )
		{
			if ( m_pHead == NULL )
			{
				m_pHead = m_pTempHead;
				m_pEnd = m_pTempEnd;
			}
			else
			{
				m_pTempEnd->next = m_pHead;
				m_pHead->prev = m_pTempEnd;

				m_pHead = m_pTempHead;
			}
		}
		else
		if( pos.nodePt == NULL )
		{
			m_pEnd->next = m_pTempHead;
			m_pTempHead->prev = m_pEnd;

			m_pEnd = m_pTempEnd;
		}
		else
		{
			m_pTempEnd->next = pos.nodePt;
			m_pTempHead->prev = pos.nodePt->prev;
			pos.nodePt->prev->next = m_pTempHead;
			pos.nodePt->prev = m_pTempEnd;
		}

		return pos;
	}

	iterator insert( iterator pos, const T &val )
	{
		m_pTemp = new Node<T>;
		m_pTemp->val = val;

		if ( pos.nodePt == m_pHead )
		{
			if ( m_Size == 0 )
			{
				m_pHead = m_pEnd = m_pTemp;
			}
			else
			{
				m_pTemp->next = m_pHead;
				m_pHead->prev = m_pTemp;

				m_pHead = m_pTemp;
			}
		}
		else
		if( pos.nodePt == NULL )
		{
			m_pEnd->next = m_pTemp;
			m_pTemp->prev = m_pEnd;

			m_pEnd = m_pTemp;
		}
		else
		{
			m_pTemp->next = pos.nodePt;
			m_pTemp->prev = pos.nodePt->prev;
			pos.nodePt->prev->next = m_pTemp;
			pos.nodePt->prev = m_pTemp;
		}

		pos.nodePt = m_pTemp;
		++m_Size;
		return pos;
	}

	void pop_back();
	void pop_back( T &val );
	void push_back( const T &val );

private:
	Node<T> *m_pHead;
	Node<T> *m_pEnd;
	Node<T> *m_pTemp;
	Node<T> *m_pRear;

	size_t m_Size;
	iterator first, last;
};

template<class T>
myStlList1020<T>::myStlList1020()
:	m_pHead( NULL ), m_pEnd( NULL ),
	m_pRear( NULL ), m_pTemp( NULL ),
	m_Size( 0 )
{
}

template<class T>
myStlList1020<T>::myStlList1020( const myStlList1020<T> &otherList )
:	m_pHead( NULL ), m_pEnd( NULL ),
	m_pRear( NULL ), m_pTemp( NULL ),
	m_Size( 0 )
{
	if ( otherList.m_Size > 0 )
	{
		m_pHead = new Node<T>;
		m_pHead->val = otherList.m_pHead->val;

		m_pRear = m_pHead;
		m_pTemp = otherList.m_pHead->next;
		while ( m_pTemp != NULL )
		{
			m_pRear->next = new Node<T>;
			m_pRear->next->val = m_pTemp->val;
			m_pRear->next->next = NULL;
			m_pRear->next->prev = m_pRear;

			m_pRear = m_pRear->next;
			m_pTemp = m_pTemp->next;
		}
		m_pEnd = m_pRear;

		m_Size = otherList.m_Size;
	}
}

template<class T>
myStlList1020<T>::~myStlList1020()
{
	m_pRear = m_pHead;
	while ( m_pRear != NULL )
	{
		m_pTemp = m_pRear;
		m_pRear = m_pRear->next;

		SAFE_DELETE( m_pTemp );
	}
}

template<class T>
void myStlList1020<T>::pop_back()
{
	if ( m_Size == 1 )
	{
		m_pTemp = m_pEnd;
		m_pHead = m_pEnd = NULL;
	}
	else
	if( m_Size > 1 )
	{
		m_pTemp = m_pEnd;
		m_pEnd = m_pEnd->prev;
	}

	SAFE_DELETE( m_pTemp );
	--m_Size;
}

template<class T>
void myStlList1020<T>::pop_back( T &val )
{
	if ( m_Size == 1 )
	{
		m_pTemp = m_pEnd;
		m_pHead = m_pEnd = NULL;
	}
	else
	if( m_Size > 1 )
	{
		m_pTemp = m_pEnd;
		m_pEnd = m_pEnd->prev;
		m_pEnd->next = NULL;
	}

	val = m_pTemp->val;
	SAFE_DELETE( m_pTemp );
	--m_Size;
}

template<class T>
void myStlList1020<T>::push_back( const T &val )
{
	m_pTemp = new Node<T>;
	m_pTemp->val = val;

	if ( m_Size == 0 )
	{
		m_pHead = m_pEnd = m_pTemp;
	}
	else
	{
		m_pEnd->next = m_pTemp;
		m_pTemp->prev = m_pEnd;

		m_pEnd = m_pTemp;
	}

	++m_Size;
}

#endif	// END MYSTLLIST1020