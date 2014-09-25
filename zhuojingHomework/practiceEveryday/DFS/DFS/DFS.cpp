// DFS.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stack>
using std::stack;

#define  ROW 10
#define  COL 10

#define SPACE	0
#define NOWALK	1
#define WALKING 2
#define WALKED	3
#define START	4
#define END		5
#define PATH	6

struct POINT
{
	int x;
	int y;
};

#define DIR_NUM 8
const POINT dirArray[DIR_NUM] = {
	{  0, -1 },
	{  1, -1 },
	{  1,  0 },
	{  1,  1 },
	{  0,  1 },
	{ -1,  1 },
	{ -1,  0 },
	{ -1, -1 }
};

struct dfsNode
{
	POINT pos;
	int dir;

	dfsNode()
	{
		pos.x = -1;
		pos.y = -1;

		dir = 0;
	}

	dfsNode( const POINT &pos )
	{
		this->pos.x = pos.x;
		this->pos.y = pos.y;

		dir = 0;
	}
};

bool isPointOutOfRange( const POINT &pos )
{
	return pos.x < 0 || pos.x >= COL ||
		   pos.y < 0 || pos.y >= ROW;
}

bool isPointValid( char (*mapData)[COL], const POINT &pos )
{
	return !isPointOutOfRange( pos ) &&
		   mapData[pos.y][pos.x] == SPACE;
}

stack<dfsNode> nodeList;

void dfs( char (*mapData)[COL], const POINT &start, const POINT &end )
{
	if ( !isPointValid( mapData, start ) ||
		 !isPointValid( mapData, end ) )
	{
		return;
	}

	dfsNode cur( start ),temp;

	int dir = 0;
	nodeList.push( cur );
	while ( !nodeList.empty() )
	{
		cur = nodeList.top();
		nodeList.pop();
		mapData[cur.pos.y][cur.pos.x] = WALKED;

		dir = cur.dir < DIR_NUM ? cur.dir : 0;
		while ( dir < DIR_NUM )
		{
			temp.pos.x = cur.pos.x + dirArray[dir].x;
			temp.pos.y = cur.pos.y + dirArray[dir].y;

			if ( isPointValid( mapData, temp.pos ) )
			{
				mapData[temp.pos.y][temp.pos.x] = WALKED;
				cur.dir = dir+1;

				nodeList.push( cur );
				nodeList.push( temp );

				if ( temp.pos.x == end.x &&
					 temp.pos.y == end.y )
				{
					return;
				}
				break;
			}

			++dir;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	char tempmapdata[ROW][COL]={
		{ 0,1,0,0,0,0,0,0,0,0 },
		{ 0,1,1,0,1,1,1,0,0,0 },
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 1,1,1,0,1,0,0,0,1,0 },
		{ 0,1,0,0,1,0,1,1,1,0 },
		{ 0,1,0,0,1,1,1,1,1,0 },
		{ 0,0,0,1,1,0,0,0,1,0 },
		{ 0,1,0,0,0,0,1,0,1,0 },
		{ 0,1,1,1,0,1,1,0,1,1 },
		{ 0,0,0,0,0,0,1,0,0,0 }
	};

	POINT start = { 0, 0 };
	POINT end = { 9, 9 };
	dfs( tempmapdata, start, end );

	dfsNode pathNode;
	while ( !nodeList.empty() )
	{
		pathNode = nodeList.top();
		nodeList.pop();
		printf( "%d, %d\n", pathNode.pos.x, pathNode.pos.y );
	}
	return 0;
}

