#include "stdafx.h"

#ifndef LINKEDLIST_AFX
#define LINKEDLIST_AFX

#define INVALID_INDEX 0xffffffff;
// 安全删除动态变量
#define SAFE_DELETE(p)	\
{						\
	if( p != NULL )		\
	{					\
		delete p;		\
		p = NULL;		\
	}					\
}						\

// 安全删除动态数组
#define SAFE_DELARR(p)	\
{						\
	if( p != NULL )		\
	{					\
		delete [] p;	\
		p = NULL;		\
	}					\
}						\

template<typename T>
struct Node
{
	T data;
	Node<T> *next;
};

template<typename T>
class linkedList
{
public:
	linkedList(void);
	~linkedList(void);
	bool	find( size_t k, T &x );
	size_t	search( T const &data, size_t time = 1 );

	bool	insert( const T &newData, size_t sit );
	// 尾部插入
	void	append( const T &newData );
	bool	remove( size_t sit );
	bool	remove( const T &data, size_t time );

	bool	isEmpty() const;
	size_t	getSize() const;

private:
	Node<T> *m_pHead;	// 头节点
	Node<T> *m_pRear;
	Node<T> *m_pTemp;
	Node<T> *m_pEnd;	// 尾节点
	size_t len;
};

template<typename T>
linkedList<T>::linkedList( void )
: m_pHead(NULL), m_pRear(NULL),
  m_pTemp(NULL), m_pEnd(NULL),
  len(0)
{
}

template<typename T>
linkedList<T>::~linkedList( void )
{
	m_pEnd = NULL;
	
	while ( m_pHead != NULL )
	{
		m_pTemp = m_pHead;
		m_pHead = m_pHead->next;

		SAFE_DELETE(m_pTemp);
	}
	m_pTemp = NULL;
	m_pEnd = NULL;
	len = 0;
}

template<typename T>
bool linkedList<T>::find( size_t k, T &x )
{
	if ( isEmpty() )
	{
		return false;
	}
	--k;

	// 让遍历君就这么遍历下去吧
	m_pRear = m_pHead;
	while ( m_pRear != NULL && (k>0) )
	{
		m_pRear = m_pRear->next;
		--k;
	}

	// 遍历完成后，若rear非空 则证明是有效值
	if ( m_pRear != NULL )
	{
		x = m_pRear->data;

		m_pRear = NULL;
		return true;
	}
	else
	{
		return false;
	}
}


template<typename T>
size_t linkedList<T>::search( T const &data, size_t time /*= 1 */ )
{
	if( isEmpty() )
	{
		return INVALID_INDEX;
	}
	else
	{
		// 代表元素位于第几个
		size_t sit = 0;

		m_pRear = m_pHead;
		//while ( m_pRear != NULL )
		//{
		//	++sit;

		//	if( m_pRear->data == data )
		//	{
		//		--time;

		//		// 一旦找到了大小合适，且次数满足的元素
		//		// 就返回，果断结束战斗
		//		if( time <= 0 )
		//		{
		//			m_pRear = NULL;
		//			return sit;
		//		}
		//	}

		//	m_pRear = m_pRear->next;
		//}

		while ( (m_pRear != NULL) && (time > 0))
		{
			++sit;
			if( m_pRear->data == data )
			{
				--time;
			}

			m_pRear = m_pRear->next;
		}


		// 找到了大小合适，且次数满足的元素
		// 果断结束战斗
		if( time <= 0 )
		{
			m_pRear = NULL;
			return sit;
		}

		return INVALID_INDEX;
	}
}


template<typename T>
bool linkedList<T>::insert( const T &newData, size_t sit )
{
	if( isEmpty() || sit <= 0 )
	{
		return false;
	}
	else
	{
		--sit;
		// 在尾部插入
		if( sit == len )
		{
			m_pTemp = new Node<T>;
			m_pTemp->data = newData;
			m_pTemp->next = NULL;

			m_pEnd->next = m_pTemp;
			m_pEnd = m_pTemp;

			++len;
			m_pTemp = NULL;
			return true;
		}

		// 头部插入的情况
		if( sit == 0 )
		{
			m_pTemp = new Node<T>;
			m_pTemp->data = newData;
			m_pTemp->next = m_pHead;
			
			m_pHead = m_pTemp;
			m_pTemp = NULL;

			if( len == 0 )
			{
				m_pEnd = m_pHead;
			}
			++len;
			return true;
		}
		else
		{
			// 非头部,非尾部的情况
			--sit;
			m_pRear = m_pHead;
			while ( (m_pRear != NULL) && (sit > 0) )
			{
				--sit;
				m_pRear = m_pRear->next;
			}

			if( sit == 0 )
			{
				m_pTemp = new Node<T>;
				m_pTemp->next = m_pRear->next;
				m_pTemp->data = newData;
				m_pRear->next = m_pTemp;

				m_pRear = NULL;
				m_pTemp = NULL;
				++len;
				return true;
			}
		}

		return false;
	}
}


template<typename T>
void linkedList<T>::append( const T &newData )
{
	if( len != 0 )
	{
		m_pTemp = new Node<T>;
		m_pTemp->data = newData;
		m_pTemp->next = NULL;

		m_pEnd->next = m_pTemp;
		m_pEnd = m_pTemp;

		m_pTemp = NULL;
	}
	else
	{
		m_pHead = new Node<T>;
		m_pHead->data = newData;
		m_pHead->next = NULL;

		m_pEnd = m_pHead;
	}

	++len;
}


template<typename T>
bool linkedList<T>::remove( size_t sit )
{
	if( isEmpty() )
	{
		return false;
	}
	else
	{
		--sit;

		// 头部的情况单独处理
		if( sit == 0 )
		{
			m_pTemp = m_pHead;
			m_pHead = m_pHead->next;
			SAFE_DELETE( m_pTemp ); 

			--len;
			if( len == 0 )
			{
				m_pEnd = NULL;
			}
			return true;
		}

		// 非头部的情况
		m_pTemp = m_pHead;
		m_pRear = m_pTemp->next;
		while ( m_pRear != NULL )
		{
			--sit;
			if( sit == 0 )
			{
				// 若删除了尾节点，则将它向前移动一个节点
				if( m_pEnd == m_pRear )
				{
					m_pEnd = m_pTemp;
				}
				m_pTemp->next = m_pRear->next;
				SAFE_DELETE( m_pRear );
				m_pTemp = NULL;

				--len;
				if( len == 0 )
				{
					m_pEnd = NULL;
				}
				return true;
			}

			m_pTemp = m_pTemp->next;
			m_pRear = m_pTemp->next;
		}
	}

	return false;
}

template<typename T>
bool linkedList<T>::remove( const T &data, size_t time )
{
	if( isEmpty() )
	{
		return false;
	}
	else
	{
		// 头部的情况单独处理
		if( m_pHead->data == data )
		{
			--time;

			if( time <= 0  )
			{
				m_pTemp = m_pHead;
				m_pHead = m_pHead->next;
				SAFE_DELETE( m_pTemp ); 

				--len;
				if( len == 0 )
				{
					m_pEnd = NULL;
				}
				return true;
			}
		}

		// 非头部的情况
		m_pTemp = m_pHead;
		m_pRear = m_pTemp->next;
		while ( m_pRear != NULL )
		{
			if( m_pRear->data == data )
			{
				--time;

				// 一旦找到了大小合适，且次数满足的元素
				// 就返回，果断结束战斗
				if( time <= 0 )
				{
					// 若删除了尾节点，则将它向前移动一个节点
					if( m_pEnd == m_pRear )
					{
						m_pEnd = m_pTemp;
					}
					m_pTemp->next = m_pRear->next;
					SAFE_DELETE( m_pRear );
					m_pTemp = NULL;

					--len;
					if( len == 0 )
					{
						m_pEnd = NULL;
					}
					return true;
				}
			}

			m_pTemp = m_pTemp->next;
			m_pRear = m_pTemp->next;
		}
	}

	return false;
}

template<typename T>
bool linkedList<T>::isEmpty() const
{
	return (len <= 0);
}

template<typename T>
size_t linkedList<T>::getSize() const
{
	return len;
}

#endif // END LINKEDLIST_AFX