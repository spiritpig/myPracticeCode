// linkedListPrac-912.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>

#define SAFE_DELETE(p) { if( p != NULL ) { delete p; p = NULL; } }

template<typename T>
struct node
{
	T data;
	node<T> *next;

	node()
	{
		next = NULL;
	}
};

template<typename T>
class linkedList
{
public:
	linkedList();
	~linkedList();
	void add( const T &data );
	bool remove( T &data );

	const node<T>* getHead()
	{
		return m_pHead;
	}

private:
	node<T> *m_pHead;
	node<T> *m_pRear;
	node<T> *m_pTemp;
	node<T> *m_pEnd;

	int size;
};

template<typename T>
linkedList<T>::linkedList()
{
	m_pHead = NULL;
	m_pRear = NULL;
	m_pTemp = NULL;
	m_pEnd = NULL;

	size = 0;
}

template<typename T>
linkedList<T>::~linkedList()
{
	m_pRear = m_pHead;
	while ( m_pHead != NULL )
	{
		m_pRear = m_pHead->next;

		SAFE_DELETE(m_pHead);
		m_pHead = m_pRear;
	}
}

template<typename T>
void linkedList<T>::add( const T &data )
{
	// 链表为空
	if ( m_pHead == NULL )
	{
		m_pHead = new node<T>;
		m_pHead->data = data;

		m_pEnd = m_pHead;
	}
	else
	{
		m_pTemp = new node<T>;
		m_pTemp->data =data;

		m_pEnd->next = m_pTemp;
		m_pEnd = m_pTemp;
	}
}

template<typename T>
bool linkedList<T>::remove( T &data )
{
	// 链表为空
	if ( m_pHead == NULL )
	{
		return false;
	}
	else
	{
		data = m_pEnd->data;
		// 只有一个元素的情况
		if( m_pHead == m_pEnd )
		{
			SAFE_DELETE(m_pHead);
			m_pEnd = NULL;
		}
		else
		{
			m_pRear = m_pHead;
			while( m_pRear->next != m_pEnd )
			{
				m_pRear = m_pRear->next;
			}

			m_pRear->next = NULL;
			SAFE_DELETE(m_pEnd);
			m_pEnd = m_pRear;
		}

		return true;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	linkedList<int> ll;

	for ( int i=0; i<20; ++i )
	{
		ll.add(i);
	}

	const node<int> *head = ll.getHead();
	while ( head != NULL )
	{
		printf( "add: %d ", head->data );
		head = head->next;
	}
	printf( "\n" );

	int t = -100;
	while(ll.remove( t ))
	{
		printf( "remove: %d ", t );
	}
	printf( "\n" );

	return 0;
}

