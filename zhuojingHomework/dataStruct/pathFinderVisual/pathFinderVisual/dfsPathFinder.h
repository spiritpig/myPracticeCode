#ifndef DFS_PATHFINDER
#define DFS_PATHFINDER

struct dfsNode
{
	POINT pos;
	int dir;

	dfsNode();
	dfsNode( int x, int y );
};

class dfsPathFinder
{
public:
	dfsPathFinder();
	~dfsPathFinder();


	bool findPathOneStep( char (*mapdata)[COL],
					  int startX, int startY,
					  int endX, int endY,
					  bool isFirst = false );

	void findPath( char (*mapdata)[COL], 
					   int startX, int startY,
					   int endX, int endY,
					   StackArray<dfsNode,ROW*COL> &path );

private:
	int m_Dir;
	dfsNode node,temp;
	StackArray<dfsNode,ROW*COL> m_pNodeList;
	char walkedMap[ROW][COL];
};

#endif // END DFS_PATHFINDER