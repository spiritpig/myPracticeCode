/*
 * =====================================================================================
 *
 *       Filename:  aStar.h
 *
 *    Description:  a*·����������ʵ����һ��ʹ��a*��ΪѰ·�㷨��·��������
 *
 *        Version:  1.0
 *        Created:  2014/10/9 14:42:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  �ձ�
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
         *  Description:  ִ��·�����ҵ�һ��������������ʾ·�������ľ������
         *                  ��ı䴫���ͼ��ֵ
         * =====================================================================================
         */
	bool findPathOneStep( char (*mapdata)[COL],
					  int startX, int startY,
					  int endX, int endY,
					  bool isFirst = false );

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  findPath
         *  Description:  ִ��һ��·����������·�����ص�path������
         *                  ��ı䴫���ͼ��ֵ
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
         *  Description:  ���Ѿ�������·�������ĵ�ͼ�У���ȡ·��
         * =====================================================================================
         */
	void _readPathFromMap( StackArray<POINT, ROW*COL> &path );

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _isPointValidAStar
         *  Description:  �ж�������Ƿ���Ч��astar�汾
         * =====================================================================================
         */
	bool _isPointValidAStar( const POINT &pos );

        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _calcH
         *  Description:  ���㵱ǰ·�����Hֵ
         * =====================================================================================
         */
	void _calcH( aStarNode &l );
        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _calcG
         *  Description:  ���¼��㵱ǰ·�����Gֵ,���µ�Gֵ�Ƚ�С��ı�child��Gֵ��
         *                  ���ı���������Gֵ���򷵻�true
         * =====================================================================================
         */
	bool _calcG( aStarNode &child, const aStarNode &parent, bool isDiagonal );
        /* 
         * ===  FUNCTION  ======================================================================
         *         Name:  _calcF
         *  Description:  ���¼���������Fֵ�����ı������򷵻�true
         * =====================================================================================
         */
	bool _calcF( aStarNode &child, const aStarNode &parent, bool isDiagonal );


	int m_Dir;
	aStarNode *node,*temp;
	aStarNode m_Map[ROW][COL];
	POINT tempPos, m_Start, m_End;

        // openlistʹ����С����ʵ�֣�����ÿ�δ�openlist��ȡֵ��ʱ��
        // ѡȡFֵ��С�Ľڵ㣬���ԣ���С�Ѻ��ʺ�����ʵ��openlist
	heap m_OpenList;
	myDequeArray<aStarNode*,ROW*COL> m_CloseList;
};

#endif // END ASTAR_PATHFINDER
