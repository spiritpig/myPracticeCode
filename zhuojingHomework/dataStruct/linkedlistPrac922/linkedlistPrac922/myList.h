#include "stdafx.h"

#ifndef MYLIST
#define MYLIST

#define SAFE_DELETE(p) {if(p) {delete p;p=0;}}
#define SAFE_DELARR(p) {if(p) {delete []p;p=0;}}

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

	size_t m_Size;
};

template<typename T>
linkedList<T>::linkedList( void )
: m_pHead( NULL ), m_pEnd( NULL ),
  m_pRear( NULL ), m_pTemp( NULL ),
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
		m_pHead = m_pRear;
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
	if ( index<0 || index>m_Size )
	{
		return false;
	}

	m_pTemp = new listNode<T>;
	m_pTemp->data = data;
	// 头部插入
	if ( index <= 0 )
	{
		m_pTemp->next = m_pHead;
		m_pHead = m_pTemp;

		// 没有元素时，头部和尾部指向同一个节点
		if ( m_pEnd == NULL )
		{
			m_pEnd = m_pHead;
		}
	}
	// 尾部插入的情况
	else
	if ( index >= m_Size )
	{
		m_pTemp->next = NULL;
		m_pEnd->next = m_pTemp;
		m_pEnd = m_pTemp;
	}
	else
	{
		// 移动到目标位置的前一个节点上
		--index;

		m_pRear = m_pHead;
		while ( index > 0 )
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
		 index<0 || 
		 index>=m_Size )
	{
		return false;
	}

	// 头部删除
	if ( index <= 0 )
	{
		m_pTemp = m_pHead;
		m_pHead = m_pHead->next;

		// 若只有一个元素，需要将尾节点置为空
		if ( m_pEnd == m_pTemp )
		{
			m_pEnd = NULL;
		}
		data = m_pTemp->data;
		SAFE_DELETE( m_pTemp );
	}
	else
	{
		// 移动到目标位置的前一个节点上
		--index;

		m_pRear = m_pHead;
		while ( index > 0 )
		{
			m_pRear = m_pRear->next;
			--index;
		}

		m_pTemp = m_pRear->next;
		m_pRear->next = m_pTemp->next;

		if ( m_pTemp == m_pEnd )
		{
			m_pEnd = m_pRear;
		}
		data = m_pTemp->data;
		SAFE_DELETE( m_pTemp );
	}

	--m_Size;
	return true;
}

#endif	// END MYLIST
