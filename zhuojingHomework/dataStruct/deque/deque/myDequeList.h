#include "stdafx.h"

#ifndef MY_DEQUE_LIST_AFX
#define MY_DEQUE_LIST_AFX

#define SAFE_DELETE(p) if(p) {delete p;p=NULL;}

template<typename T>
class myDequeList
{
public:
	struct node
	{
		T data;
		node *pNext;
		node *pPrev;
	};

public:
	myDequeList();
	~myDequeList();

	bool isEmpty();
	void push( const T &data );
	bool pop( T &data );
	bool pop();

	T &First();
	void setEmpty();


private:
	node *m_pFront;
	node *m_pBack;
	node *m_pTemp;
};

template<typename T>
myDequeList<T>::myDequeList()
: m_pFront(NULL), m_pBack(NULL),
  m_pTemp(NULL)
{
}

template<typename T>
myDequeList<T>::~myDequeList()
{
	m_pTemp = m_pBack;
	while ( m_pBack != NULL )
	{
		m_pTemp = m_pBack->pNext;

		SAFE_DELETE( m_pBack );
		m_pBack = m_pTemp;
	}
	m_pTemp = NULL;
}

template<typename T>
bool myDequeList<T>::isEmpty()
{
	return (m_pBack == NULL);
}

template<typename T>
void myDequeList<T>::push( const T &data )
{
	if ( isEmpty() )
	{
		m_pFront = new node;
		m_pFront->data = data;
		m_pFront->pPrev = NULL;
		m_pFront->pNext = NULL;

		m_pBack = m_pFront;
	}
	else
	{
		m_pTemp = new node;
		m_pTemp->data = data;
		m_pTemp->pPrev = NULL;
		m_pTemp->pNext = m_pFront;

		m_pFront->pPrev = m_pTemp;
		m_pFront = m_pTemp;
	}
}

template<typename T>
bool myDequeList<T>::pop( T &data )
{
	if ( isEmpty() )
	{
		return false;
	}
	else
	{
		m_pTemp = m_pBack;

		data = m_pBack->data;
		m_pBack = m_pBack->pPrev;
		if( m_pBack != NULL )
		{
			m_pBack->pNext = NULL;
		}

		SAFE_DELETE( m_pTemp );
		return true;
	}
}

template<typename T>
bool myDequeList<T>::pop()
{
	if ( isEmpty() )
	{
		return false;
	}
	else
	{
		m_pTemp = m_pBack;

		m_pBack = m_pBack->pPrev;
		if( m_pBack != NULL )
		{
			m_pBack->pNext = NULL;
		}

		SAFE_DELETE( m_pTemp );
		return true;
	}
}

template<typename T>
T & myDequeList<T>::First()
{
	return m_pBack->data;
}

template<typename T>
void myDequeList<T>::setEmpty()
{
	m_pTemp = m_pBack;
	while ( m_pBack != NULL )
	{
		m_pTemp = m_pBack->pNext;

		SAFE_DELETE( m_pBack );
		m_pBack = m_pTemp;
	}
	m_pTemp = NULL;
}

#endif	// END MY_DEQUE_LIST_AFX
