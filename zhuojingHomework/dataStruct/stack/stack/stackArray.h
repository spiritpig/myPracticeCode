#include "stdafx.h"

#ifndef STACKARRAY_AFX
#define STACKARRAY_AFX
#endif // END STACKARRAY_AFX

template<typename T, int maxsize>
class stackArray
{
public:
	stackArray();
	~stackArray(void);

	bool isFull();
	bool isEmpty();

	T& getTop();
	bool getTop( T &data );
	bool push( const T &data );
	bool pop();
	bool pop( T &data );

	void setEmpty();

private:
	T m_data[maxsize];
	int m_Top;
};

template<typename T, int maxsize>
stackArray<T, maxsize>::stackArray()
{
	m_Top = -1;
}

template<typename T, int maxsize>
stackArray<T, maxsize>::~stackArray( void )
{
	m_Top = -1;
}

template<typename T, int maxsize>
bool stackArray<T, maxsize>::isFull()
{
	return (m_Top >= maxsize-1);	
}


template<typename T, int maxsize>
bool stackArray<T, maxsize>::isEmpty()
{
	return (m_Top <= -1);
}


template<typename T, int maxsize>
T& stackArray<T, maxsize>::getTop()
{
	return m_data[m_Top];
}

template<typename T, int maxsize>
bool stackArray<T, maxsize>::getTop( T &data )
{
	if( m_Top <= -1 )
	{
		return false;
	}
	else
	{
		data = m_data[m_Top];
		return true;
	}
}

template<typename T, int maxsize>
bool stackArray<T, maxsize>::push( const T &data )
{
	if( isFull() )
	{
		return false;
	}
	else
	{
		m_data[++m_Top] = data;
		return true;
	}
}


template<typename T, int maxsize>
bool stackArray<T, maxsize>::pop()
{
	if( isEmpty() )
	{
		return false;
	}
	else
	{
		--m_Top;
		return true;
	}
}


template<typename T, int maxsize>
bool stackArray<T, maxsize>::pop( T &data )
{
	if( isEmpty() )
	{
		return false;
	}
	else
	{
		data = m_data[m_Top--];
		return true;
	}
}


template<typename T, int maxsize>
void stackArray<T, maxsize>::setEmpty()
{
	m_Top = -1;
}
