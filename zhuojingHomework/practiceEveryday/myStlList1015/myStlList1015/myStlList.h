#ifndef MYSTLLIST
#define MYSTLLIST

#define SAFE_DELETE(p) { if(p) { delete p; p = NULL; } }

template<class T>
struct Node
{
	T data;
	Node *next;
	Node *prev;

	Node()
	: next( NULL ), prev( NULL )
	{
	}

	Node( T val )
	: data( val ),
	  next( NULL ), prev( NULL )
	{
	}
};

template<class T>
class myStlList1015
{
public:
	struct iterator
	{
		iterator()
		:	nodePt( NULL )
		{
		}
		iterator( const iterator &iter ) 
		:	nodePt( iter.nodePt )
		{ 
		}

		int operator-( const iterator &other )
		{
			return ( this->pos - other.pos );
		}

		iterator& operator++()
		{
			nodePt = nodePt->next;
			++pos;
			return *this;
		}
		iterator operator++(int)
		{
			iterator temp = *this;
			nodePt = nodePt->next;
			++pos;

			return temp;
		}

		iterator& operator--()
		{
			nodePt = nodePt->prev;
			--pos;
			return *this;
		}
		iterator operator--(int)
		{
			iterator temp = *this;
			nodePt = nodePt->prev;
			--pos;

			return temp;
		}

		T& operator*()
		{
			return nodePt->data; 
		}

		bool operator==( const iterator &iter )
		{
			return (nodePt == iter.nodePt);
		}
		bool operator!=( const iterator &iter )
		{
			return (nodePt != iter.nodePt);
		}

	public:
		Node<T> *nodePt;
		size_t pos;
	};

public:
	myStlList1015()
	:	m_Size( 0 ),
		m_pHead( NULL ), m_pEnd( NULL ),
		m_pRear( NULL ), m_pTemp( NULL )
	{
	}
	~myStlList1015();

	void insert( const iterator &pos, const T &val );
	void pop_back();
	void push_back( const T &val );

	iterator& begin()
	{
		first.nodePt =  m_pHead;
		first.pos = 0;

		return first;
	}
	iterator& end()
	{
		last.nodePt = m_pEnd->next;
		last.pos = m_Size;

		return last;
	}

	T& front() const
	{
		return m_pHead->data;
	}
	T& back() const
	{
		return m_pEnd->data;
	}
	size_t size() const
	{
		return m_Size;
	}

private:
	Node<T> *m_pHead;
	Node<T> *m_pEnd;
	Node<T> *m_pTemp;
	Node<T> *m_pRear;

	size_t m_Size;
	
	iterator first;
	iterator last;
};

template<class T>
myStlList1015<T>::~myStlList1015()
{
	m_pRear = m_pHead;
	while ( m_pRear )
	{
		m_pTemp = m_pRear;
		m_pRear = m_pRear->next;

		SAFE_DELETE( m_pTemp );
	}
}

template<class T>
void myStlList1015<T>::insert( const iterator &pos, const T &val )
{
	m_pTemp = new Node<T>( val );

	// 头部插入
	if ( pos.nodePt == m_pHead )
	{
		m_pTemp->next = m_pHead;
	
		// 非空链表
		if ( m_pHead != NULL )
		{
			m_pHead->prev = m_pTemp;
			m_pHead = m_pTemp;
		}
		// 空链表
		else
		{
			m_pEnd = m_pHead = m_pTemp;
		}
	}
	else
	if( pos.nodePt == NULL )
	{
		m_pTemp->prev = m_pEnd;
		m_pEnd->next = m_pTemp;
		m_pEnd = m_pTemp;
	}
	else
	{
		m_pTemp->next = pos.nodePt;
		m_pTemp->prev = pos.nodePt->prev;
		pos.nodePt->prev->next = m_pTemp;
		pos.nodePt->prev = m_pTemp;
	}

	++m_Size;
}

template<class T>
void myStlList1015<T>::pop_back()
{
	if ( m_Size == 0 )
	{
		return;
	}

	if ( m_Size == 1 )
	{
		SAFE_DELETE( m_pHead );
		m_pHead = m_pEnd = NULL;
	}
	else
	{
		m_pTemp = m_pEnd;
		m_pEnd = m_pEnd->prev;

		SAFE_DELETE( m_pTemp );
	}

	--m_Size;
}

template<class T>
void myStlList1015<T>::push_back( const T &val )
{
	if ( m_Size == 0 )
	{
		m_pHead = new Node<T>( val );
		m_pEnd = m_pHead;
	}
	else
	{
		m_pTemp = new Node<T>( val );
		m_pTemp->prev = m_pEnd;
		m_pEnd->next = m_pTemp;
		m_pEnd = m_pTemp;
	}

	++m_Size;
}

#endif	// END MYSTLLIST
