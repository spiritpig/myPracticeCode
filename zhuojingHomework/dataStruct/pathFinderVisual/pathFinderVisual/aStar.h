#ifndef ASTAR_PATHFINDER
#define ASTAR_PATHFINDER

class aStarPathFinder
{
public:
	aStarPathFinder();
	~aStarPathFinder();


	bool findPathOneStep( char (*mapdata)[COL],
					  int startX, int startY,
					  int endX, int endY,
					  bool isFirst = false );

	void findPath( char (*mapdata)[COL], 
					   int startX, int startY,
					   int endX, int endY,
					   StackArray<POINT, ROW*COL> &path );

private:

	void _readPathFromMap( StackArray<POINT, ROW*COL> &path );
	bool _isPointValidAStar( const POINT &pos );

	void _calcH( aStarNode &l );
	// 若本次计算改变了G值返回true，否则返回false
	bool _calcG( aStarNode &child, const aStarNode &parent, bool isDiagonal );
	bool _calcF( aStarNode &child, const aStarNode &parent, bool isDiagonal );


	int m_Dir;
	aStarNode *node,*temp;
	aStarNode m_Map[ROW][COL];
	POINT tempPos, m_Start, m_End;

	heap m_OpenList;
	myDequeArray<aStarNode*,ROW*COL> m_CloseList;
};

#endif // END ASTAR_PATHFINDER