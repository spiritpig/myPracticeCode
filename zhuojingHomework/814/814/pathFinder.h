/*
	描述： pathFinder，路径查找器。
		  内部使用BFS作为寻路算法。

	日期： 2014.08.17

	作者： pinkbeen
 */
#include "stdafx.h"

#ifndef PATHFINDER_AFX
#define PATHFINDER_AFX

class pathFinder
{
private:
	bool isPointOutofRange( const vector2 &v );
	bool isPointCanBeWalked( const vector2 &v, p2DArray maze );
	bool isPointValid( const vector2 &v, p2DArray maze );
	int getOppositeDir( int dir );

	// 清空路径，以便下一次查找出来的路径
	// 不会被上一次的路径影响
	void clearPath();

public:
	pathFinder();

	// findpath函数会填充dirMap，需要获取路径时，
	// 可以使用readPathFromDirMap函数来填充路径
	void findPath( p2DArray maze, const vector2 &start, const vector2 &end );

	// 从DirMap中读取出实际的路径
	void readPathFromDirMap( const vector2 &end );

	// 输出接口，让用户获取路径查找的结果
	p2DArray getDirMap();
	MyQueue* getPath();

private:
	char dirMap[ROW][CEL];
	MyQueue path;
};

#endif // PATHFIDNER_AFX END