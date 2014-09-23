// bfs.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
/*

class pathFinder
{
private:
	bool getOppositeDir( int dir );
	void findPathFromDirMap( MyQueue &mq, const vector2 &end );

public:
	pathFinder();
	pathFinder( p2DArray maze );

	void findPath( const vector2 &start, const vector2 &end );


private:
	char maze[ROW][CEL];
	char dirMap[ROW][CEL];
};


vector2 dir[4] = {
	{  0, -1 },
	{  1,  0 },
	{  0,  1 },
	{ -1,  0 },
};

void assignPos( vector2 &left, const vector2 &right )
{
	left.x = right.x;
	left.y = right.y;
}

bool isPosEqual( vector2 &v1, const vector2 &v2 )
{
	return (v1.x == v2.x) &&
		   (v1.y == v2.y);
}

bool isPointOutofRange( const vector2 &v )
{
	if( v.x < 0 || v.x > ROW-1 ||
		v.y < 0 || v.y > CEL-1 )
	{
		return true;
	}
	return false;
}

bool isPointCanBeWalked( const vector2 &v, p2DArray maze )
{
	if( maze[v.x][v.y] == MS_SPACE )
	{
		return true;
	}
	return false;
}

bool isPointValid( const vector2 &v, p2DArray maze )
{
	if( !isPointOutofRange(v) &&
		isPointCanBeWalked( v, maze ))
	{
		return true;
	}
	return false;
}

int getOppositeDir( int dir )
{
	return (dir+2) % 4;
}

void findPathFromDirMap( MyQueue &mq, char (*dirMap)[CEL], const vector2 &end )
{
	vector2 curPos;
	assignPos( curPos, end );

	int curDir = 0;
	do 
	{
		mq.push_front( curPos );

		curDir = dirMap[curPos.x][curPos.y];
		curPos.x = curPos.x + dir[curDir].x;
		curPos.y = curPos.y + dir[curDir].y;
	} while (  dirMap[curPos.x][curPos.y] != MS_START  );

	mq.push_front( curPos );
}

void bfs( char (*maze)[CEL], char (*dirMap)[CEL], 
		  const vector2 &start, const vector2 &end )
{
	// 起点或者终点无效，直接返回
	if( !isPointValid( start, maze ) ||
		!isPointValid( end, maze ) )
	{
		return;
	}

	MyQueue expandingNodes;
	expandingNodes.push_back( start );

	// 设置起点和终点的位置
	dirMap[start.x][start.y] = MS_START;
	dirMap[end.x][end.y] = MS_END;

	Node *curNode;
	vector2 temp;

	while ( 1 )
	{
		expandingNodes.pop_front( &curNode );

		// 碰到了终点，可以停止了
		if( curNode == NULL ||
			isPosEqual( curNode->data, end ) )
		{
			return;
		}

		// 当前点有效才需要扩展
		if( isPointValid( curNode->data, maze ) )
		{
			maze[curNode->data.x][curNode->data.y] = MS_WALKED;

			int curDir = 0;
			while ( curDir < 4 )
			{
				temp.x = curNode->data.x + dir[curDir].x;
				temp.y = curNode->data.y + dir[curDir].y;
				if( isPointValid( temp, maze ) )
				{
					expandingNodes.push_back( temp );
					// 标记当前节点的上一节点
					dirMap[temp.x][temp.y] = getOppositeDir( curDir );
				}

				++curDir;
			}
		}

		delete curNode;
		curNode = NULL;
	}
}
*/
int _tmain(int argc, _TCHAR* argv[])
{
	char maze[ROW][CEL] = {
		{ 0, 0, 0, 4, 0, 0, 0, 0, 0, 0 },
		{ 4, 4, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 4, 4, 4, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 4, 4, 0, 0, 0 },
		{ 0, 0, 4, 4, 4, 0, 4, 0, 0, 4 },
		{ 0, 0, 0, 0, 4, 4, 0, 0, 4, 0 },	
		{ 0, 0, 0, 0, 0, 4, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 4, 4, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 4, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	};

	vector2 start, end;

	start.x = 0;
	start.y = 0;

	end.x = 9;
	end.y = 9;

	pathFinder pf;

	pf.findPath( maze, start, end );
	MyQueue *mq;
	mq = pf.getPath();
	//findPathFromDirMap( mq, dirMap, start );

	vector2 v;
	while( !mq->isEmpty() )  
	{
		mq->pop_front( v );
		std::cout << v << " ";
	}
	printf( "\n" );

	return 0;
}

