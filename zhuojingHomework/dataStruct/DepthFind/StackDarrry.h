#include "AllDefine.h"

#ifndef AFX_STACKDARRAY
#define AFX_STACKDARRAY

#define MYMAX(a,b) ((a>b)?a:b)

template<class T>
class StackDArray
{
public:
	StackDArray();
	bool Empty();
	void Push(T const &data);
	bool Pop();
	bool Pop(T &data);
	T& GetTop();
	bool GetTop(T &data);
	void SetEmpty();
	~StackDArray();
private:
	void _ReSize();
private:
	T *m_pdata;
	int m_top;
	int m_spacenum;
};

template<class T>
void StackDArray<T>::SetEmpty()
{
	//SAFE_DELARR(m_pdata);
	//m_spacenum=0;

	m_top=-1;
}

template<class T>
bool StackDArray<T>::GetTop( T &data )
{
	if(Empty())
	{
		return false;
	}
	else
	{
		data=m_pdata[m_top];
		return true;
	}
}

template<class T>
T& StackDArray<T>::GetTop()
{
	return m_pdata[m_top];
}

template<class T>
bool StackDArray<T>::Pop( T &data )
{
	if(Empty())
	{
		return false;
	}
	else
	{
		data=m_pdata[m_top];
		--m_top;
		return true;
	}
}

template<class T>
bool StackDArray<T>::Pop()
{
	if(Empty())
	{
		return false;
	}
	else
	{
		--m_top;
		return true;
	}
}

template<class T>
void StackDArray<T>::Push( T const &data )
{
	_ReSize();
	++m_top;
	m_pdata[m_top]=data;
	return;
}

template<class T>
bool StackDArray<T>::Empty()
{
	return m_top<=-1;
}

template<class T>
StackDArray<T>::~StackDArray()
{
	SAFE_DELARR(m_pdata);
	m_top=-1;
	m_spacenum=0;
}

template<class T>
StackDArray<T>::StackDArray()
{
	m_pdata=NULL;
	m_top=-1;
	m_spacenum=0;
}

template<class T>
void StackDArray<T>::_ReSize()
{
	if(m_top>=m_spacenum-1)
	{
		m_spacenum+=MYMAX(m_spacenum/2,1);
		static T *pTemp;
		pTemp=new T[m_spacenum];
		static int i;
		for (i=0;i<=m_top;++i)
		{
			pTemp[i]=m_pdata[i];
		}
		SAFE_DELARR(m_pdata);
		m_pdata=pTemp;
		pTemp=NULL;
	}
}

#endif