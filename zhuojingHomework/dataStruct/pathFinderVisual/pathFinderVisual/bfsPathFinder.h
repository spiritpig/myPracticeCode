#ifndef BFS_PATHFINDER
#define BFS_PATHFINDER

struct bfsNode
{
	char mapFlag;
	POINT pos;
	bfsNode *pParent;

	bfsNode();
};

class bfsPathFinder
{
public:
	bfsPathFinder();
	~bfsPathFinder();


	bool findPathOneStep( char (*mapdata)[COL],
					  int startX, int startY,
					  int endX, int endY,
					  bool isFirst = false );

	void findPath( char (*mapdata)[COL], 
					   int startX, int startY,
					   int endX, int endY,
					   StackArray<POINT, ROW*COL> &path );

private:

	void _readPathFromMap(  int startX, int startY,
							int endX, int endY,
							StackArray<POINT, ROW*COL> &path );

	bool _isPosWalked( const bfsNode *node );

	int m_Dir;
	bfsNode *node,*temp;
	POINT tempPos;
	myDequeArray<bfsNode*,ROW*COL> m_NodeList;
	bfsNode m_Map[ROW][COL];
};

#endif // END BFS_PATHFINDER