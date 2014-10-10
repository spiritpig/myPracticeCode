#ifndef MYSTLLIST
#define MYSTLLIST

#define SAFE_DELETE(p) { if(p) { delete p; p=NULL; } }

template<class T>
struct Node
{
	T data;
	Node *pre;
	Node *next;
};

template<class T>
class myStlList
{
public:
	myStlList();
	~myStlList();

	void pop_back();
	void push_back( const T &val );


private:
	Node<T> *m_pHead;
	Node<T> *m_pEnd;
	Node<T> *m_pRear;
	Node<T> *m_pTemp;

	size_t m_Size;
};

template<class T>
myStlList<T>::myStlList()
:	m_Size( 0 ), 
	m_pHead( NULL ), m_pEnd( NULL )
{
}

template<class T>
myStlList<T>::~myStlList()
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
void myStlList<T>::pop_back()
{
	if ( m_Size == 1 )
	{
		SAFE_DELETE( m_pHead );
		m_pEnd = NULL;
	}
	else
	{
		m_pTemp = m_pEnd;
		m_pEnd = m_pEnd->pre;
		m_pEnd->next = NULL;

		SAFE_DELETE( m_pTemp );
	}
	--m_Size;
}

template<class T>
void myStlList<T>::push_back( const T &val )
{
	if ( m_Size == 0 )
	{
		m_pHead = new Node<T>;
		m_pHead->data = val;
		m_pHead->next = NULL;
		m_pHead->pre = NULL;

		m_pEnd = m_pHead;
	}
	else
	{
		m_pTemp = new Node<T>;
		m_pTemp->data = val;
		m_pTemp->next = NULL;
		m_pTemp->pre = m_pEnd;

		m_pEnd->next = m_pTemp;
		m_pEnd = m_pTemp;
	}
	++m_Size;
}

#endif	// END MYSTLLIST