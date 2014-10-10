#include "AllDefine.h"

template<typename T>
void mySwap( T &a, T &b )
{
	static T temp;
	temp = a;
	a = b;
	b = temp;
}

//////////////////////////////////////////////////////////////////////////
aStarPathFinder::aStarPathFinder()
: m_OpenList( false )
{
	m_Dir = 0;
}

aStarPathFinder::~aStarPathFinder()
{
}

void aStarPathFinder::findPath( char (*mapdata)[COL], 
							 int startX, int startY, 
							 int endX, int endY,
							 StackArray<POINT,ROW*COL> &path )
{
	// ���·����openlist��closelist�������ܵ���һ��·��������Ӱ��
	path.SetEmpty();
	m_OpenList.setEmpty();
	m_CloseList.setEmpty();

	m_Start.x = startX;
	m_Start.y = startY;
	m_End.x = endX;
	m_End.y = endY;

	// ��ʼ����ͼ����
	for ( int i=0; i<ROW; ++i )
	{
		for ( int j=0; j<COL; ++j )
		{
			m_Map[i][j].pos.x = j;
			m_Map[i][j].pos.y = i;
			m_Map[i][j].mapFlag = mapdata[i][j];
			_calcH( m_Map[i][j] );
			m_Map[i][j].G = 0;
		}
	}

	// �����ѹ��openlist�У��������ĵ�·���������Ͽ�ʼ
	node = &m_Map[startY][startX];
	node->H = 0;
	node->mapFlag = AF_INOPENLIST;
	m_OpenList.add( node );

	while ( !m_OpenList.isEmpty() )
	{
		// ��openlist�ĶѶ���ȡһ��Ԫ�أ����Ƴ�����
		// �������ŵ�closeList��
		m_OpenList.remove_Top( &node );
		m_CloseList.push( node );
		node->mapFlag = AF_INCLOSELIST;

		// ̽����Χ�İ˸�����
		m_Dir = 0;
		while ( m_Dir < DIR_NUM )
		{
			tempPos.x = node->pos.x + dirArray[m_Dir].x;
			tempPos.y = node->pos.y + dirArray[m_Dir].y;

			
			if ( _isPointValidAStar( tempPos ) )
			{
				temp= &m_Map[tempPos.y][tempPos.x];

				// ���Ѱ·
				if( isPointEqual( temp->pos, m_End ) )
				{
					temp->pParent = node;
					_readPathFromMap( path );
					return;
				}

				if ( temp->mapFlag == SPACE )
				{
					m_OpenList.add( temp );
					temp->mapFlag = AF_INOPENLIST;
					// ��������ʹ����һ����������飬����б�߷�����±�
					// �պ���һ�������������жϵ�ǰ�ķ����Ƿ�Ϊ��������
					// �ж��Ƿ�Ϊб�߷���
					if( _calcF( *temp, *node, (m_Dir%2 != 0) ) )
					{
						temp->pParent = node;
					}
				}
				else
				{
					if( temp->mapFlag == AF_INOPENLIST &&
						_calcF( *temp, *node, (m_Dir%2 != 0) ) )
					{
						temp->pParent = node;
					}
					else
					if( temp->mapFlag == AF_INCLOSELIST &&
						_calcF( *temp, *node, (m_Dir%2 != 0) ) )
					{
						m_OpenList.add( temp );
						m_CloseList.remove( temp );
						temp->mapFlag = AF_INOPENLIST;
						temp->pParent = node;
					}
				}
			}

			++m_Dir;
		}
	}
}

bool aStarPathFinder::findPathOneStep( char (*mapdata)[COL], 
								int startX, int startY, 
								int endX, int endY,
								bool isFirst )
{
	if( isFirst )
	{
		m_OpenList.setEmpty();
		m_CloseList.setEmpty();

		m_Start.x = startX;
		m_Start.y = startY;
		m_End.x = endX;
		m_End.y = endY;

		// ��ʼ����ͼ����
		for ( int i=0; i<ROW; ++i )
		{
			for ( int j=0; j<COL; ++j )
			{
				m_Map[i][j].pos.x = j;
				m_Map[i][j].pos.y = i;
				m_Map[i][j].mapFlag = mapdata[i][j];
				_calcH( m_Map[i][j] );
				m_Map[i][j].G = 0;
			}
		}
		node = &m_Map[m_Start.y][m_Start.x];
		node->H = INT_MAX;
		mapdata[m_Start.y][m_Start.x]= AF_INOPENLIST;
		m_OpenList.add( node );

		return false;
	}

	if( !m_OpenList.isEmpty() )
	{
		m_OpenList.remove_Top( &node );
		m_CloseList.push( node );
		mapdata[node->pos.y][node->pos.x] = AF_INCLOSELIST;

		// ̽����Χ�İ˸�����
		m_Dir = 0;
		while ( m_Dir < DIR_NUM )
		{
			tempPos.x = node->pos.x + dirArray[m_Dir].x;
			tempPos.y = node->pos.y + dirArray[m_Dir].y;

			if ( isPointValid( mapdata, tempPos ) )
			{
				temp= &m_Map[tempPos.y][tempPos.x];

				// ���Ѱ·
				if( isPointEqual( temp->pos, m_End ) )
				{
					temp->pParent = node;
					return true;
				}

				if ( mapdata[temp->pos.y][temp->pos.x] == SPACE )
				{
					m_OpenList.add( temp );
					mapdata[temp->pos.y][temp->pos.x] = AF_INOPENLIST;
					// ��������ʹ����һ����������飬����б�߷�����±�
					// �պ���һ�������������жϵ�ǰ�ķ����Ƿ�Ϊ��������
					// �ж��Ƿ�Ϊб�߷���
					if( _calcF( *temp, *node, (m_Dir%2 != 0) ) )
					{
						temp->pParent = node;
					}
				}
				else
				{
					if( mapdata[temp->pos.y][temp->pos.x] == AF_INOPENLIST &&
						_calcF( *temp, *node, (m_Dir%2 != 0) ) )
					{
						temp->pParent = node;
					}
					else
					if( mapdata[temp->pos.y][temp->pos.x] == AF_INCLOSELIST &&
						_calcF( *temp, *node, (m_Dir%2 != 0) ) )
					{
						m_OpenList.add( temp );
						m_CloseList.remove( temp );
						mapdata[temp->pos.y][temp->pos.x] = AF_INOPENLIST;
						temp->pParent = node;
					}
				}
			}

			++m_Dir;
		}
	}

	return false;
}

void aStarPathFinder::_readPathFromMap( StackArray<POINT, ROW*COL> &path )
{
	node = &m_Map[m_End.y][m_End.x];
	path.Push( node->pos );

	while ( !isPointEqual( node->pos, m_Start ) )
	{
		node = node->pParent;
		path.Push( node->pos );
	}
}

void aStarPathFinder::_calcH( aStarNode &l )
{
	l.H = ( abs( l.pos.x-m_End.x ) + abs( l.pos.y-m_End.y ) ) * ASTAR_H_TIMES;
}

bool aStarPathFinder::_calcG( aStarNode &child, const aStarNode &parent, bool isDiagonal )
{
	static tempG;
	tempG = isDiagonal ? parent.G + ASTAR_G_DIAGONAL_TIMES :
						 parent.G + ASTAR_G_STRAIGHT_TIMES;

	// ���ı���Gֵ����true�����򷵻�false
	// GֵΪ0�����ǵ�һ�μ���,Ҳ�ı�Gֵ
	if( tempG < child.G || 
		child.G == 0 )
	{
		child.G = tempG;
		return true;
	}
	return false;
}

bool aStarPathFinder::_calcF( aStarNode &child, const aStarNode &parent, bool isDiagonal )
{
	// ֻ�е��ı���Gֵ��ʱ������¼���Fֵ
	// Fֵ�ı���Ҳ����true
	if( _calcG( child, parent, isDiagonal ) )
	{
		child.F = child.G + child.H;
		return true;
	}
	return false;
}

bool aStarPathFinder::_isPointValidAStar( const POINT &pos )
{
	return !isPointOutOfRange( pos ) &&
		(m_Map[pos.y][pos.x].mapFlag != NOWALK);
}
