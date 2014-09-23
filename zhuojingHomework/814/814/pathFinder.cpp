#include "stdafx.h"

struct pos
{
	int x,y;
};
pos dirArray[4] = {
	{  -1, 0 },
	{   1, 0 },
	{   0,-1 },
	{   0, 1 },
};

//////////////////////////////////////////////////////////////////////////
bool pathFinder::isPointOutofRange( const vector2 &v )
{
	if( v.x < 0 || v.x > ROW-1 ||
		v.y < 0 || v.y > CEL-1 )
	{
		return true;
	}
	return false;
}

bool pathFinder::isPointCanBeWalked( const vector2 &v, p2DArray maze )
{
	if( maze[v.x][v.y] == MS_SPACE )
	{
		return true;
	}
	return false;
}

bool pathFinder::isPointValid( const vector2 &v, p2DArray maze )
{
	if( !isPointOutofRange(v) &&
		isPointCanBeWalked( v, maze ))
	{
		return true;
	}
	return false;
}

int pathFinder::getOppositeDir( int dir )
{
	switch( dir )
	{
	case ED_UP:
		{
			return ED_DOWN;
		}
		break;

	case ED_DOWN:
		{
			return ED_UP;
		}
		break;

	case ED_LEFT:
		{
			return ED_RIGHT;
		}
		break;

	case ED_RIGHT:
		{
			return ED_LEFT;
		}
		break;
	}

	return -1;
}


void pathFinder::readPathFromDirMap( const vector2 &end )
{
	// ���ɵ�·����Ϣ���
	clearPath();

	vector2 curPos = end;

	// �����ȡ·�����������·�������ݣ����õ��ľ��������·����
	int curDir = 0;
	do 
	{
		path.push_front( curPos );

		curDir = dirMap[curPos.x][curPos.y];
		curPos.x = curPos.x + dirArray[curDir].x;
		curPos.y = curPos.y + dirArray[curDir].y;
	} while ( dirMap[curPos.x][curPos.y] != MS_START );

	path.push_front( curPos );
}

void pathFinder::clearPath()
{
	path.clearQueue();
}


pathFinder::pathFinder(void)
{
	memset( dirMap, 0, sizeof(char)*ROW*CEL );
}

void pathFinder::findPath( p2DArray maze, const vector2 &start, const vector2 &end )
{
	// �������յ���Ч��ֱ�ӷ���
	if( !isPointValid( start, maze ) ||
		!isPointValid( end, maze ) )
	{
		return;
	}
	else
	{
		clearPath();

		char mazeCopy[ROW][CEL];
		memcpy( dirMap, maze, sizeof(char)*ROW*CEL );
		memcpy( mazeCopy, maze, sizeof(char)*ROW*CEL );

		MyQueue openList;
		openList.push_back( start );

		vector2 curPos;
		vector2 temp;

		while ( 1 )
		{
			openList.pop_front( curPos );

			// �������յ㣬����ֹͣ��
			if( curPos == end )
			{
				dirMap[start.x][start.y] = MS_START;
//				readPathFromDirMap( end );
				return;
			}

			// ��ǰ����Ч����Ҫ��չ
			if( isPointValid( curPos, mazeCopy ) )
			{
				mazeCopy[curPos.x][curPos.y] = MS_WALKED;

				int curDir = 0;
				while ( curDir < 4 )
				{
					temp.x = curPos.x + dirArray[curDir].x;
					temp.y = curPos.y + dirArray[curDir].y;
					if( isPointValid( temp, mazeCopy ) )
					{
						openList.push_back( temp );
						// ��ǵ�ǰ�ڵ����һ�ڵ�
						dirMap[temp.x][temp.y] = getOppositeDir( curDir );
					}

					++curDir;
				}
			}

			// ��չ�б�Ϊ�գ�ֻ���˳���
			if( openList.isEmpty() )
			{
				return;
			}
		}
	}
}

p2DArray pathFinder::getDirMap()
{
	return dirMap;
}

MyQueue* pathFinder::getPath()
{
	return &path;
}
