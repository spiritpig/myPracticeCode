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
	bool IsEmpty()const;	bool Insert(size_t index, const T &data);	bool Delete(size_t index, T &data);	int  Search(const T &data, int time) const; 	// �������У���ѯ��time��ֵΪdata��Ԫ���Ƿ����	bool Find(T &data, int time);
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
	// ͷ������
	if ( index <= 0 )
	{
		m_pTemp->next = m_pHead;
		m_pHead = m_pTemp;

		// û��Ԫ��ʱ��ͷ����β��ָ��ͬһ���ڵ�
		if ( m_pEnd == NULL )
		{
			m_pEnd = m_pHead;
		}
	}
	// β����������
	else
	if ( index >= m_Size )
	{
		m_pTemp->next = NULL;
		m_pEnd->next = m_pTemp;
		m_pEnd = m_pTemp;
	}
	else
	{
		// �ƶ���Ŀ��λ�õ�ǰһ���ڵ���
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

	// ͷ��ɾ��
	if ( index <= 0 )
	{
		m_pTemp = m_pHead;
		m_pHead = m_pHead->next;

		// ��ֻ��һ��Ԫ�أ���Ҫ��β�ڵ���Ϊ��
		if ( m_pEnd == m_pTemp )
		{
			m_pEnd = NULL;
		}
		data = m_pTemp->data;
		SAFE_DELETE( m_pTemp );
	}
	else
	{
		// �ƶ���Ŀ��λ�õ�ǰһ���ڵ���
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
