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

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  findPathOneStep
         *  Description:  执行路径查找的一步，可以用于演示路径搜索的具体过程
         *                  会改变传入地图的值
         * =====================================================================================
         */
	bool findPathOneStep( char (*mapdata)[COL],
					  int startX, int startY,
					  int endX, int endY,
					  bool isFirst = false );

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  findPath
         *  Description:  执行一次路径搜索，将路径返回到path参数中
         *                  会改变传入地图的值
         * =====================================================================================
         */
	void findPath( char (*mapdata)[COL], 
					   int startX, int startY,
					   int endX, int endY,
					   vector<dfsNode> &path );

private:
	int m_Dir;
	dfsNode node,temp;
	vector<dfsNode> m_pNodeList;
	char walkedMap[ROW][COL];
};

#endif // END DFS_PATHFINDER
