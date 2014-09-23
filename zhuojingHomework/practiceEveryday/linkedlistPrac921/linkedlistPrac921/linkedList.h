#include "stdafx.h"

#ifndef LINKEDLIST
#define LINKEDLIST

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
	bool IsEmpty()const;	bool Insert(size_t index, const T &data);	bool Delete(size_t index, T &data);	int  Search(const T &data, int time) const; 	// 在链表中，查询第time个值为data的元素是否存在	bool Find(T &data, int time);
private:
	listNode<T> *m_pHead, *m_pEnd,
				*m_pRear, *m_pTemp;

	size_t size;
};

template<typename T>
linkedList<T>::linkedList( void )
: m_pHead(NULL), m_pEnd(NULL),
  m_pRear(NULL), m_pTemp(NULL),
  size(0)
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
		m_pHead = m_pRear;
	}
}

template<typename T>
size_t linkedList<T>::Length() const
{
	return size;
}

template<typename T>
bool linkedList<T>::IsEmpty() const
{
	return (m_pHead == NULL);
}

template<typename T>
bool linkedList<T>::Insert( size_t index, const T &data )
{
	if ( index > size )
	{
		return false;
	}
	// 头部插入
	else
	if ( index == 0 )
	{
		m_pTemp = new listNode<T>;
		m_pTemp->data = data;

		// 没有元素时，头尾都是第一个节点
		if ( m_pHead == NULL )
		{
			m_pTemp->next = NULL;
			m_pHead = m_pEnd = m_pTemp;
		}
		// 有元素时，只移动头节点
		else
		{
			m_pTemp->next = m_pHead;
			m_pHead = m_pTemp;
		}
	}
	//  尾部插入的情况
	else
	if ( index == size )
	{
		m_pTemp = new listNode<T>;
		m_pTemp->data = data;
		m_pTemp->next = NULL;

		m_pEnd->next = m_pTemp;
		m_pEnd = m_pTemp;
	}
	else
	{
		// 当用户输入5这个index时，需要的是插入到5这个位置
		// 为了移动元素方便，定位到4这个位置，更合适一些
		// 所以提前将index减一
		--index;

		m_pRear = m_pHead;
		while ( index > 0 )
		{
			m_pRear = m_pRear->next;
			--index;
		}

		// 建立新的链接
		m_pTemp = new listNode<T>;
		m_pTemp->data = data;
		m_pTemp->next = m_pRear->next;
		m_pRear->next = m_pTemp;
	}

	++size;
	return true;
}


template<typename T>
bool linkedList<T>::Delete( size_t index, T &data )
{
	if ( IsEmpty() || 
		 index < 0 || 
		 index >= size )
	{
		return false;
	}
	else
	if ( m_pHead == m_pEnd )
	{
		SAFE_DELETE( m_pHead );
		m_pEnd = NULL;
	}
	else
	{
		// 当用户输入5这个index时，需要的是插入到5这个位置
		// 为了移动元素方便，定位到4这个位置，更合适一些
		// 所以提前将index减一
		--index;

		m_pRear = m_pHead;
		while ( index > 0 )
		{
			m_pRear = m_pRear->next;
			--index;
		}

		// 建立新链接
		m_pTemp = m_pRear->next;
		m_pRear->next = m_pRear->next->next;
		// 尾部插入，移动尾节点
		if ( m_pTemp == m_pEnd )
		{
			m_pEnd = m_pRear;
		}
		SAFE_DELETE( m_pTemp );
		--size;
	}

	return true;
}


#endif	// END LINKEDLIST
