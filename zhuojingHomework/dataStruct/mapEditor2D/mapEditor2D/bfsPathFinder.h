/*
 * =====================================================================================
 *
 *       Filename:  bfsPathFinder.h
 *
 *    Description:  广度优先搜索路径搜索器，实现一个使用BFS作为寻路算法的路径搜索器
 *
 *        Version:  1.0
 *        Created:  2014/10/9 15:01:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  烧饼
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BFS_PATHFINDER
#define BFS_PATHFINDER

// bfs节点，用于存储地图上的点之间的父子关系和地图的状态
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
					   StackArray<POINT, ROW*COL> &path );

private:

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _readPathFromMap
         *  Description:  从已经进行了路径搜索的地图中，读取路径
         * =====================================================================================
         */
	void _readPathFromMap(  int startX, int startY,
							int endX, int endY,
							StackArray<POINT, ROW*COL> &path );

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _isPosWalked
         *  Description:  判断路径点是否走过
         * =====================================================================================
         */
	bool _isPosWalked( const bfsNode *node );

	int m_Dir;
	bfsNode *node,*temp;
	POINT tempPos;
	myDequeArray<bfsNode*,ROW*COL> m_NodeList;
	bfsNode m_Map[ROW][COL];
};

#endif // END BFS_PATHFINDER
