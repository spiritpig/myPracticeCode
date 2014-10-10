#include "AllDefine.h"

dfsNode::dfsNode()
{
	pos.x = -1;
	pos.y = -1;
	dir = 0;
}

dfsNode::dfsNode( int x, int y )
{
	pos.x = x;
	pos.y = y;
	dir = 0;
}

//////////////////////////////////////////////////////////////////////////
dfsPathFinder::dfsPathFinder()
{
	m_pNodeList.reserve(ROW*COL);
	m_Dir = 0;
}

dfsPathFinder::~dfsPathFinder()
{
}

void dfsPathFinder::findPath( char (*mapdata)[COL], 
							 int startX, int startY, 
							 int endX, int endY,
							 vector<dfsNode> &path )
{
	m_pNodeList.resize(0);
	path.resize(0);

	int dir = 0;
	node.pos.x = startX;
	node.pos.y = startY;
	path.push_back( node );

	mapdata[startY][startX] = WALKED;
	memcpy( walkedMap, mapdata, sizeof(char)*ROW*COL );

	while ( !path.empty() )
	{
		while ( dir < DIR_NUM )
		{
			temp.pos.x = node.pos.x + dirArray[dir].x;
			temp.pos.y = node.pos.y + dirArray[dir].y;

			if( isPointValid( walkedMap, temp.pos ) )
			{
				walkedMap[temp.pos.y][temp.pos.x] = WALKED;
				node.dir = dir+1;
				path.push_back( node );
				path.push_back( temp );

				if( (temp.pos.x == endX) &&
					(temp.pos.y == endY) )
				{
					return;
				}
				break;
			}

			++dir;
		}

		// ����ĸ�������Ч���õ�Ϊ��Ч�㣬������
		// ���ң���һ���ƶ�����ʼ���򣬱�Ϊ��һ���ƶ����ķ���
		node = path.back();
		path.pop_back();
		if ( dir >= DIR_NUM )
		{
			dir = node.dir;
		}
		else
		{
			dir = 0;
		}
	}
}

bool dfsPathFinder::findPathOneStep( char (*mapdata)[COL], 
								int startX, int startY, 
								int endX, int endY,
								bool isFirst )
{
	// ��һ�ε�ʱ�򣬽����ѹ��
	if( isFirst )
	{
		m_pNodeList.resize(0);
		temp.pos.x = startX;
		temp.pos.y = startY;

		m_pNodeList.push_back( temp );
		mapdata[startY][startX] = WALKED;
	}

	node = m_pNodeList.back();
	// �����յ��˳�
	if( node.pos.x == endX &&
		node.pos.y == endY )
	{
		return true;
	}
	else
	{
		// ��ȡ�µ���Ч�㣬�ͷ���
		if ( m_Dir >= DIR_NUM )
		{
			m_Dir = node.dir;
		}
		else
		{
			m_Dir = 0;
		}

		if ( !m_pNodeList.empty() )
		{
			m_pNodeList.pop_back();
			while ( m_Dir < DIR_NUM )
			{
				temp.pos.x = node.pos.x + dirArray[m_Dir].x;
				temp.pos.y = node.pos.y + dirArray[m_Dir].y;

				if( isPointValid( mapdata, temp.pos ) )
				{
					mapdata[temp.pos.y][temp.pos.x] = WALKING;
					node.dir = m_Dir+1;
					m_pNodeList.push_back( node );
					m_pNodeList.push_back( temp );

					if( temp.pos.x == endX &&
						temp.pos.y == endY )
					{
						return true;
					}
					else
					{
						return false;
					}
				}

				++m_Dir;
			}

			if ( m_Dir >= DIR_NUM )
			{
				mapdata[node.pos.y][node.pos.x] = WALKED;
			}
		}
		else
		{
			return true;
		}
	}

	return false;
}


