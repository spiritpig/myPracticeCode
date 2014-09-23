#include "stdafx.h"

#ifndef STACKLIST_AFX
#define STACKLIST_AFX

#define SAFE_DELETE(p) if(p) {delete p;p=NULL;}

template<typename T>
class stackList
{
public:
	struct node
	{
		T data;
		node *pNext;
		node *pPrev;
	};

public:
	stackList();
	~stackList();

	bool isEmpty();

	T& getTop();
	bool getTop( T &data );
	void push( const T &data );
	bool pop();
	bool pop( T &data );

	void setEmpty();

private:
	node *m_pTop;
	node *m_pTemp;
};

template<typename T>
stackList<T>::stackList()
: m_pTop(NULL), m_pTemp(NULL)
{
}

template<typename T>
stackList<T>::~stackList()
{
	m_pTemp = m_pTop;
	while ( m_pTop != NULL )
	{
		m_pTemp = m_pTop->pPrev;
		SAFE_DELETE( m_pTop );

		m_pTop = m_pTemp;
	}
	m_pTemp = NULL;
}

template<typename T>
bool stackList<T>::isEmpty()
{
	return m_pTop == NULL;
}

template<typename T>
T& stackList<T>::getTop()
{
	return m_pTop->data;
}

template<typename T>
bool stackList<T>::getTop( T &data )
{
	if( isEmpty() )
	{
		return false;
	}
	else
	{
		data = m_pTop->data;
		return true;
	}
}


template<typename T>
void stackList<T>::push( const T &data )
{
	if ( isEmpty() )
	{
		m_pTop = new node;
		m_pTop->data = data;
		m_pTop->pPrev = NULL;
		m_pTop->pNext = NULL;
	}
	else
	{
		m_pTemp = new node;
		m_pTemp->data = data;
		m_pTemp->pPrev = m_pTop;
		m_pTemp->pNext = NULL;

		m_pTop->pNext = m_pTemp;
		m_pTop = m_pTemp;
	}
}

template<typename T>
bool stackList<T>::pop()
{
	if ( isEmpty() )
	{
		return false;
	}
	else
	{
		m_pTemp = m_pTop;
		m_pTop = m_pTop->pPrev;
		if( m_pTop != NULL )
		{
			m_pTop->pNext = NULL;
		}

		SAFE_DELETE( m_pTemp );
		return true;
	}
}

template<typename T>
bool stackList<T>::pop( T &data )
{
	if ( isEmpty() )
	{
		return false;
	}
	else
	{
		data = m_pTop->data;

		m_pTemp = m_pTop;
		m_pTop = m_pTop->pPrev;
		if( m_pTop != NULL )
		{
			m_pTop->pNext = NULL;
		}

		SAFE_DELETE( m_pTemp );
		return true;
	}
}

template<typename T>
void stackList<T>::setEmpty()
{
	m_pTemp = m_pTop;
	while ( m_pTop != NULL )
	{
		m_pTemp = m_pTop->pPrev;

		SAFE_DELETE( m_pTop );
		m_pTop = m_pTemp;
	}
	m_pTemp = NULL;
}

#endif	// END STACKLIST_AFX
