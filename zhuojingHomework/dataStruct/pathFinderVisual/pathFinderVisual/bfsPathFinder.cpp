#include "AllDefine.h"

bfsNode::bfsNode()
{
	pos.x = 0;
	pos.y = 0;
	pParent = NULL;
	mapFlag = SPACE;
}

//////////////////////////////////////////////////////////////////////////
bfsPathFinder::bfsPathFinder()
{
	m_Dir = 0;
}

bfsPathFinder::~bfsPathFinder()
{
}

void bfsPathFinder::findPath( char (*mapdata)[COL], 
							 int startX, int startY, 
							 int endX, int endY,
							 StackArray<POINT,ROW*COL> &path )
{
	path.SetEmpty();
	m_NodeList.setEmpty();

	for ( int i=0; i<ROW; ++i )
	{
		for ( int j=0; j<COL; ++j )
		{
			m_Map[i][j].pos.x = j;
			m_Map[i][j].pos.y = i;
			m_Map[i][j].mapFlag = mapdata[i][j];
		}
	}
	node = &m_Map[startY][startX];
	node->mapFlag = WALKED;
	m_NodeList.push( node );

	// 我们还有点可以探索的时候，就继续下去
	while ( !m_NodeList.isEmpty() )
	{
		m_NodeList.pop( node );

		m_Dir = 0;
		while ( m_Dir < DIR_NUM )
		{
			tempPos.x = node->pos.x + dirArray[m_Dir].x;
			tempPos.y = node->pos.y + dirArray[m_Dir].y;
			if( !isPointOutOfRange(tempPos) )
			{
				temp= &m_Map[tempPos.y][tempPos.x];
	
				// 有效地路径点，做好标记，然后继续
				if( _isPosWalked( temp ) )
				{
					temp->pParent = node;
					temp->mapFlag = WALKED;

					if( isPointEqual( temp->pos.x, temp->pos.y, endX, endY ) )
					{
						_readPathFromMap( startX, startY, endX, endY, path );
						// 读取路径
						return;
					}
					m_NodeList.push(temp);
				}
			}
			++m_Dir;
		}
	}
}

bool bfsPathFinder::findPathOneStep( char (*mapdata)[COL], 
								int startX, int startY, 
								int endX, int endY,
								bool isFirst )
{
	if( isFirst )
	{
		m_NodeList.setEmpty();
		for ( int i=0; i<ROW; ++i )
		{
			for ( int j=0; j<COL; ++j )
			{
				m_Map[i][j].pos.x = j;
				m_Map[i][j].pos.y = i;
				m_Map[i][j].mapFlag = mapdata[i][j];
			}
		}
		node = &m_Map[startY][startX];
		mapdata[startY][startX] = WALKED;
		m_NodeList.push( node );
	}

	if( !m_NodeList.isEmpty() )
	{
		m_NodeList.pop( node );

		m_Dir = 0;
		while ( m_Dir < DIR_NUM )
		{
			tempPos.x = node->pos.x + dirArray[m_Dir].x;
			tempPos.y = node->pos.y + dirArray[m_Dir].y;
			if( !isPointOutOfRange(tempPos) )
			{
				temp= &m_Map[tempPos.y][tempPos.x];

				// 有效地路径点，做好标记，然后继续
				if( mapdata[temp->pos.y][temp->pos.x] == SPACE )
				{
					temp->pParent = node;
					mapdata[temp->pos.y][temp->pos.x] = WALKED;

					if( isPointEqual( temp->pos.x, temp->pos.y, endX, endY ) )
					{
						return true;
					}
					m_NodeList.push(temp);
				}
			}
			++m_Dir;
		}

		return false;
	}
	else
	{
		return true;
	}
}

void bfsPathFinder::_readPathFromMap( int startX, int startY, 
									int endX, int endY, 
									StackArray<POINT, ROW*COL> &path )
{
	node = &m_Map[endY][endX];
	path.Push( node->pos );

	while ( !isPointEqual( node->pos.x, node->pos.y, startX, startY ) )
	{
		node = node->pParent;
		path.Push( node->pos );
	}
}

bool bfsPathFinder::_isPosWalked( const bfsNode *node )
{
	if( (node->pos.x < 0) || (node->pos.x > COL-1) ||
		(node->pos.y < 0) || (node->pos.y > ROW-1) )
	{
		return false;
	}
	else
	{
		return node->mapFlag == SPACE;
	}
}


