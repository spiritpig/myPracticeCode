#include "AllDefine.h"

aStarNode::aStarNode()
{
	pos.x = 0;
	pos.y = 0;
	pParent = NULL;
	mapFlag = SPACE;

	F = 0;
	G = 0;
	H = 0;
}

//////////////////////////////////////////////////////////////////////////
heap::heap( bool isMax )
: m_IsMax( isMax ), m_Size( 0 ),
  m_Capacity( 9 )
{
	m_Data = new aStarNode*[m_Capacity];
}

heap::~heap( void )
{
	SAFE_DELARR( m_Data );
}

void heap::add( const aStarNode *data )
{
	// ����һ��Ԫ�ش������±�1��λ�ã��±�0��������
	if ( m_Size <= 0 )
	{
		m_Size = 1;
		m_Data[m_Size] = (aStarNode *)data;
		return;
	}

	// ��������, �˴�ʹ��m_Size+1������Ϊ
	// ���Ƿ����˵�һ���ڵ㣬m_Size�������һ���ڵ��
	// λ��Ҳ��Ԫ�ظ��������ԣ�m_Size����С�������Ų���Խ��
	if ( m_Size+1 >= m_Capacity )
	{
		_resize();
	}

	++m_Size;
	size_t insertPos = m_Size;
	while ( insertPos > 1 )
	{
		if( _compare( data, m_Data[insertPos/2] ) == 1 )
		{
			m_Data[insertPos] = m_Data[insertPos/2];
			insertPos /= 2;
		}
		else
		{
			break;
		}
	}

	m_Data[insertPos] = (aStarNode *)data;
}

bool heap::remove_Top( aStarNode **data )
{
	if( m_Size <= 0 )
	{
		return false;
	}

	*data = m_Data[1];
	static aStarNode *tempVal;
	static size_t newPos, tempPos;
	tempVal = m_Data[m_Size];
	tempPos = 1;
	newPos = 1;

	// �Զѽ��е���
	--m_Size;
	while ( newPos <= m_Size )
	{
		m_Data[newPos] = m_Data[tempPos];
		newPos = tempPos;
		// �������ӽڵ�����
		if ( (2*newPos + 1) <= m_Size ) 
		{
			if ( _compare( tempVal, m_Data[2*newPos] ) == -1 )
			{
				tempPos = 2*newPos;
			}
			if ( _compare( m_Data[2*newPos], m_Data[2*newPos + 1] ) == -1 )
			{
				tempPos = 2*newPos + 1;
			}
		}
		// ��һ���ӽڵ�����
		else
		if ( (2*newPos) <= m_Size ) 
		{
			if ( _compare( tempVal, m_Data[2*newPos] ) == -1 )
			{
				tempPos = 2*newPos;
			}
		}

		if( newPos == tempPos )
		{
			break;
		}
	}

	// ��ԭ����ĩβ��Ԫ�أ��ƶ����������λ����
	m_Data[newPos] = tempVal;
	return true;
}

bool heap::isEmpty()
{
	return m_Size <= 0;
}

void heap::setEmpty()
{
	m_Size = 0;
}

int heap::_compare( const aStarNode * const left, const aStarNode * const right )
{
	if ( left == right )
	{
		return 0;
	}

	if ( m_IsMax )
	{
		return (left->F > right->F ? 1 : -1);
	} 
	else
	{
		return (left->F < right->F ? 1 : -1);
	}
}


void heap::_resize()
{
	m_Capacity += MAX( m_Capacity/2, 1 );

	static aStarNode **pTemp = NULL;
	pTemp = new aStarNode*[m_Capacity];
	for ( size_t i=0; i<=m_Size; ++i )
	{
		pTemp[i] = m_Data[i];
	}

	SAFE_DELARR( m_Data );
	m_Data = pTemp;
}
