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
	bool IsEmpty()const;	bool Insert(size_t index, const T &data);	bool Delete(size_t index, T &data);	int  Search(const T &data, int time) const; 	// �������У���ѯ��time��ֵΪdata��Ԫ���Ƿ����	bool Find(T &data, int time);
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
	// ͷ������
	else
	if ( index == 0 )
	{
		m_pTemp = new listNode<T>;
		m_pTemp->data = data;

		// û��Ԫ��ʱ��ͷβ���ǵ�һ���ڵ�
		if ( m_pHead == NULL )
		{
			m_pTemp->next = NULL;
			m_pHead = m_pEnd = m_pTemp;
		}
		// ��Ԫ��ʱ��ֻ�ƶ�ͷ�ڵ�
		else
		{
			m_pTemp->next = m_pHead;
			m_pHead = m_pTemp;
		}
	}
	//  β����������
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
		// ���û�����5���indexʱ����Ҫ���ǲ��뵽5���λ��
		// Ϊ���ƶ�Ԫ�ط��㣬��λ��4���λ�ã�������һЩ
		// ������ǰ��index��һ
		--index;

		m_pRear = m_pHead;
		while ( index > 0 )
		{
			m_pRear = m_pRear->next;
			--index;
		}

		// �����µ�����
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
		// ���û�����5���indexʱ����Ҫ���ǲ��뵽5���λ��
		// Ϊ���ƶ�Ԫ�ط��㣬��λ��4���λ�ã�������һЩ
		// ������ǰ��index��һ
		--index;

		m_pRear = m_pHead;
		while ( index > 0 )
		{
			m_pRear = m_pRear->next;
			--index;
		}

		// ����������
		m_pTemp = m_pRear->next;
		m_pRear->next = m_pRear->next->next;
		// β�����룬�ƶ�β�ڵ�
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
