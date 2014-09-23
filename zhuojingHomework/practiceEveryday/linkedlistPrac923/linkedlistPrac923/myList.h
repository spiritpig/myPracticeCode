#include "stdafx.h"

#ifndef MYLIST
#define MYLIST

#define SAFE_DELETE(p) { if(p) { delete p; p = NULL;} }

template<typename T>
struct listNode
{
	T data;
	listNode<T> *next;

	listNode() {}
};

template<typename T>
class linkedList
{
public:
	linkedList(void);
	~linkedList(void);

	size_t Length()const;  
	bool IsEmpty()const;	bool Insert(size_t index, const T &data);	bool Delete(size_t index, T &data);	int  Search(const T &data, int time) const;	/**/	bool Find(const T &data, size_t time);
private:
	listNode<T> *m_pHead, *m_pEnd,
		*m_pRear, *m_pTemp;

	size_t m_Size;
};

template<typename T>
linkedList<T>::linkedList( void )
: m_pHead( NULL ), m_pRear( NULL ),
  m_pTemp( NULL ), m_pEnd( NULL ),
  m_Size( 0 )
{
}

template<typename T>
linkedList<T>::~linkedList( void )
{
	m_pRear = m_pHead;
	while ( m_pRear != NULL )
	{
		m_pRear = m_pHead->next;

		SAFE_DELETE( m_pHead );
		m_pHead = m_pHead->next;
	}
}

template<typename T>
size_t linkedList<T>::Length() const
{
	return m_Size;
}

template<typename T>
bool linkedList<T>::IsEmpty() const
{
	return (m_Size <= 0);
}

template<typename T>
bool linkedList<T>::Insert( size_t index, const T &data )
{
	if ( index < 0 || index > m_Size )
	{
		return false;
	}

	m_pTemp = new listNode<T>;
	m_pTemp->data = data;
	m_pTemp->next = NULL;
	// 头部插入
	if ( index <= 0 )
	{
		m_pTemp->next = m_pHead;
		m_pHead = m_pTemp;

		if ( m_pEnd == NULL )
		{
			m_pEnd = m_pHead;
		}
	}
	// 尾部插入
	else
	if ( index >= m_Size )
	{
		m_pEnd->next = m_pTemp;
		m_pEnd = m_pTemp;
	}
	else
	{
		--index;

		m_pRear = m_pHead;
		while ( index >0 )
		{
			m_pRear = m_pRear->next;
			--index;
		}

		m_pTemp->next = m_pRear->next;
		m_pRear->next = m_pTemp;
	}

	++m_Size;
	return true;
}

template<typename T>
bool linkedList<T>::Delete( size_t index, T &data )
{
	if ( IsEmpty() ||
		 index < 0 || 
		 index >= m_Size )
	{
		return false;
	}

	// 头部删除
	if ( index <= 0 )
	{
		m_pTemp = m_pHead;
		m_pHead = m_pHead->next;

		data = m_pTemp->data;
		// 当只有一个元素时，头和尾要共进退
		if ( m_pEnd == m_pTemp )
		{
			m_pEnd = NULL;
		}
		SAFE_DELETE( m_pTemp );
	}
	// 尾部删除
	else
	{
		--index;

		m_pRear = m_pHead;
		while ( index >0 )
		{
			m_pRear = m_pRear->next;
			--index;
		}

		m_pTemp = m_pRear->next;
		m_pRear->next = NULL;

		data = m_pTemp->data;
		// 若是删除尾节点，需要移动尾指针
		if ( m_pEnd == m_pTemp )
		{
			m_pEnd = m_pRear;
		}
		SAFE_DELETE( m_pTemp );
	}

	--m_Size;
	return true;
}

template<typename T>
bool linkedList<T>::Find(const T &data, size_t time)
{
	if ( IsEmpty()	||
		 time == 0	||
		 time > m_Size )
	{
		return false;
	}

	m_pRear = m_pHead;
	while ( (m_pRear != NULL ) && (time > 0) )
	{
		// 找到合适的就闪人了
		if ( m_pRear->data == data )
		{
			--time;
			if ( time <= 0 )
			{
				return true;
			}
		}
		m_pRear = m_pRear->next;
	}

	return false;
}

#endif	// END MYLIST
