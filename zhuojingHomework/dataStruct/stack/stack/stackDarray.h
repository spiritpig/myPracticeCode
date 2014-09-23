#include "stdafx.h"

#ifndef STACKDARRAY_AFX
#define STACKDARRAY_AFX

#define SAFE_DELARR( p )	\
{							\
	if( p != NULL )			\
	{						\
		delete [] p;		\
		p = NULL;			\
	}						\
}							\

#define MAX(a,b) ( a>b ? a : b )

template<typename T>
class stackDarray
{
public:
	stackDarray();
	~stackDarray();

	bool isEmpty();
	bool needRealloc();

	T& getTop();
	bool getTop( T &data );
	void push( const T &data );
	bool pop();
	bool pop( T &data );

	void setEmpty();

private:
	void _resize();

	T *m_pData;
	int m_Top;
	int m_Capacity;
};

template<typename T>
stackDarray<T>::stackDarray()
: m_Top( -1 ), m_pData( NULL ),
	m_Capacity( 0 )
{
}

template<typename T>
stackDarray<T>::~stackDarray()
{
	SAFE_DELARR( m_pData );
}

template<typename T>
bool stackDarray<T>::isEmpty()
{
	return (m_Top <= -1);
}


template<typename T>
bool stackDarray<T>::needRealloc()
{
	return (m_Top >= m_Capacity-1);
}


template<typename T>
T& stackDarray<T>::getTop()
{
	return m_pData[m_Top];
}


template<typename T>
bool stackDarray<T>::getTop( T &data )
{
	if( isEmpty() )
	{
		return false;
	}
	else
	{
		data = m_pData[m_Top];
		return true;
	}
}


template<typename T>
void stackDarray<T>::push( const T &data )
{
	_resize();
	m_pData[++m_Top] = data;
}


template<typename T>
bool stackDarray<T>::pop()
{
	if ( isEmpty() )
	{
		return false;
	}
	else
	{
		--m_Top;
		return true;
	}
}

template<typename T>
bool stackDarray<T>::pop( T &data )
{
	if ( isEmpty() )
	{
		return false;
	}
	else
	{
		data = m_pData[m_Top--];
		return true;
	}
}

template<typename T>
void stackDarray<T>::_resize()
{
	if( needRealloc() )
	{
		m_Capacity += MAX( m_Capacity/2, 1 );
		static T *pTemp;
		pTemp = new T[m_Capacity];

		static int i;
		for ( i=0; i<=m_Top; ++i )
		{
			pTemp[i] = m_pData[i];
		}

		SAFE_DELARR( m_pData );
		m_pData = pTemp;
	}
}


template<typename T>
void stackDarray<T>::setEmpty()
{
	m_Top = -1;
}


#endif	// END STACKDARRAY_AFX
