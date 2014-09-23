#include "stdafx.h"

#ifndef MY_DEQUE_DARRAY_AFX
#define MY_DEQUE_DARRAY_AFX

#define SAFE_DELARR(p) if(p) {delete []p;p=NULL;}
#define MYMAX(a,b) ((a>b)?a:b)

template<typename T>
class myDequeDArray
{
public:
	myDequeDArray();
	~myDequeDArray();

	bool isEmpty();
	void push( const T &data );
	bool pop( T &data );
	bool pop();

	T &First();
	void setEmpty();

private:
	void _resize();

	T *m_pData;
	int m_Back;
	size_t m_Capacity;
};

template<typename T>
myDequeDArray<T>::myDequeDArray()
: m_pData(NULL), m_Back(-1),
  m_Capacity(0)
{
}

template<typename T>
myDequeDArray<T>::~myDequeDArray()
{
	SAFE_DELARR(m_pData);
}

template<typename T>
bool myDequeDArray<T>::isEmpty()
{
	return (m_Back <= -1);
}

template<typename T>
void myDequeDArray<T>::push( const T &data )
{
	_resize();

	m_pData[++m_Back] = data;
}

template<typename T>
bool myDequeDArray<T>::pop( T &data )
{
	if( isEmpty() )
	{
		return false;
	}
	else
	{
		data = m_pData[m_Back--];
		return true;
	}
}

template<typename T>
bool myDequeDArray<T>::pop()
{
	if( isEmpty() )
	{
		return false;
	}
	else
	{
		--m_Back;
		return true;
	}
}

template<typename T>
T & myDequeDArray<T>::First()
{
	return m_pData[m_Back];
}

template<typename T>
void myDequeDArray<T>::setEmpty()
{
	m_Back = -1;
}

template<typename T>
void myDequeDArray<T>::_resize()
{
	if( m_Back >= (int)m_Capacity-1 )
	{
		static T *pTemp;
		static int i;

		m_Capacity+=MYMAX(m_Capacity/2,1);
		pTemp = new T[m_Capacity];
		for (i=0;i<=m_Back;++i)
		{
			pTemp[i]=m_pData[i];
		}

		SAFE_DELARR(m_pData);
		m_pData=pTemp;
		pTemp=NULL;
	}
}

#endif	// END MY_DEQUE_DARRAY_AFX
