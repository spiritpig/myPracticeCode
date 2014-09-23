#include <Windows.h>
#include <stdio.h>
#include "StackDarrry.h"

#define ROW 10
#define COL 10

#define SPACE	0
#define NOWALK	1
#define WALKING 2
#define WALKED	3
#define START	4
#define END		5

#ifndef DFS_PATHFINDER
#define DFS_PATHFINDER

const POINT dirArray[4] = {
	{  0, -1 },
	{  1,  0 },
	{  0,  1 },
	{ -1,  0 },
};


struct dfsNode
{
	POINT pos;
	int dir;

	dfsNode();
	dfsNode( int x, int y );
};

typedef StackDArray<dfsNode> &pathType;

class dfsPathFinder
{
public:
	dfsPathFinder();
	~dfsPathFinder();

	void findPath( char (*mapdata)[COL], 
					   int startX, int startY,
					   int endX, int endY,
					   StackDArray<dfsNode> &path );

private:
	StackDArray<dfsNode> m_pNodeList;
	char walkedMap[ROW][COL];
};

#endif // END DFS_PATHFINDER