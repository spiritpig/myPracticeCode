#include "dfsPathFinder.h"

static bool isPointOutOfRange( const POINT &pos )
{
	return (pos.x < 0) || (pos.x > COL-1) ||
		   (pos.y < 0) || (pos.y > ROW-1);
}

static bool isPointValid( char (*mapdata)[COL], const POINT &pos )
{
	return !isPointOutOfRange( pos ) &&
		   (mapdata[pos.y][pos.x] == SPACE);
}

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
}

dfsPathFinder::~dfsPathFinder()
{
}

void dfsPathFinder::findPath( char (*mapdata)[COL], 
								 int startX, int startY, 
								 int endX, int endY,
								 StackDArray<dfsNode> &path)
{
	path.SetEmpty();

	int dir = 0;
	dfsNode node( startX, startY ), temp;
	path.Push( node );

	mapdata[startY][startX] = WALKED;

//	memcpy( walkedMap, mapdata, sizeof(char)*ROW*COL );

	while ( !path.Empty() )
	{
		while ( dir < 4 )
		{
			temp.pos.x = node.pos.x + dirArray[dir].x;
			temp.pos.y = node.pos.y + dirArray[dir].y;

			if( isPointValid( mapdata, temp.pos ) )
			{
				printf( "%d,%d  ", temp.pos.x, temp.pos.y );
				if( (temp.pos.x == endX) &&
					(temp.pos.y == endY) )
				{
					return;
				}

				mapdata[temp.pos.y][temp.pos.x] = WALKED;

				node.dir = dir+1;
				path.Push( node );
				path.Push( temp );
				break;
			}

			++dir;
		}

		// 如果四个方向都无效，该点为无效点，弹出来
		// 并且，下一次移动的起始方向，变为上一次移动到的方向
		path.Pop( node );
		if ( dir == 4 )
		{
			dir = node.dir;
		}
		else
		{
			dir = 0;
		}
	}
}
