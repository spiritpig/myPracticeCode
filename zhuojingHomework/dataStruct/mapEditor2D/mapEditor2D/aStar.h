/*
 * =====================================================================================
 *
 *       Filename:  aStar.h
 *
 *    Description:  a*路径查找器，实现了一个使用a*作为寻路算法的路径查找器
 *
 *        Version:  1.0
 *        Created:  2014/10/9 14:42:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  烧饼
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef ASTAR_PATHFINDER
#define ASTAR_PATHFINDER

class aStarPathFinder
{
public:
	aStarPathFinder();
	~aStarPathFinder();

        
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
	void _readPathFromMap( StackArray<POINT, ROW*COL> &path );

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _isPointValidAStar
         *  Description:  判断输入点是否有效，astar版本
         * =====================================================================================
         */
	bool _isPointValidAStar( const POINT &pos );

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _calcH
         *  Description:  计算当前路径点的H值
         * =====================================================================================
         */
	void _calcH( aStarNode &l );
        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _calcG
         *  Description:  重新计算当前路径点的G值,若新的G值比较小则改变child的G值，
         *                  若改变了输入点的G值，则返回true
         * =====================================================================================
         */
	bool _calcG( aStarNode &child, const aStarNode &parent, bool isDiagonal );
        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _calcF
         *  Description:  重新计算输入点的F值，若改变了它则返回true
         * =====================================================================================
         */
	bool _calcF( aStarNode &child, const aStarNode &parent, bool isDiagonal );


	int m_Dir;
	aStarNode *node,*temp;
	aStarNode m_Map[ROW][COL];
	POINT tempPos, m_Start, m_End;

        // openlist使用最小堆来实现，由于每次从openlist中取值的时候，
        // 选取F值最小的节点，所以，最小堆很适合用来实现openlist
	heap m_OpenList;
	myDequeArray<aStarNode*,ROW*COL> m_CloseList;
};

#endif // END ASTAR_PATHFINDER
