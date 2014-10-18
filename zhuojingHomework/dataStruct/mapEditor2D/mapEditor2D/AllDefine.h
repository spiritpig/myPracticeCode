/*
 *  描述：  公共头文件，放置全部的头文件包含命令、一些公共的
 *          常量和枚举值的定义。
 *
 *  日期： 14.10.9
 *
 *  作者： 烧饼
 *
 */

#ifndef AFX_ALLDEFINE
#define AFX_ALLDEFINE


#include <Engine_Define.h>
#pragma comment(lib,"Sgge.lib")
#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <limits.h>
#include <stdio.h>
#include <vector>
using std::vector;

#define ROW 15
#define COL 20
#define CELL_SIZE 40.0f
#define SPACE	0
#define NOWALK	1
#define WALKING 2
#define WALKED	3
#define START	4
#define END		5
#define PATH	6
#define MAP_FILENAME "map.txt"


/*-----------------------------------------------------------------------------
 *  a star 算法F值公式的控制系数
 *-----------------------------------------------------------------------------*/
#define ASTAR_H_TIMES 10
#define ASTAR_G_STRAIGHT_TIMES 10
#define ASTAR_G_DIAGONAL_TIMES 14

enum ASTAR_FLAG 
{
	AF_SPACE,
	AF_NOWALK,
	AF_INOPENLIST,
	AF_INCLOSELIST
};

enum EDIT_STATE 
{
	ES_SPACE,
	ES_WALL,
	ES_START,
	ES_END
};

#define DIR_NUM 8
const POINT dirArray[8] = {
	{  0, -1 },
	{  1, -1 },
	{  1,  0 },
	{  1,  1 },
	{  0,  1 },
	{ -1,  1 },
	{ -1,  0 },
	{ -1, -1 }
};

const POINT STARTPOS = { 0, 7 };
const POINT ENDPOS = { 19, 7 };

enum PATH_FINDING_METHOD
{
	DEPTH_FIRST_SEARCH = 1,
	BREADTH_FIRST_SEARCH = 2,
	ASTAR = 3
};


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isPointOutOfRange
 *  Description:  判断输入点，是否超出了地图范围，地图范围由ROW和COL来界定。
 * =====================================================================================
 */
bool isPointOutOfRange( const POINT &pos );

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isPointValid
 *  Description:  判断输入点，在mapdata中是否为有效点( 空地 )
 * =====================================================================================
 */
bool isPointValid( char (*mapdata)[COL], const POINT &pos );

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isPointEqual
 *  Description:  判断输入的两个点是否相等
 * =====================================================================================
 */
bool isPointEqual( int paX, int paY, int pbX, int pbY );

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  isPointEqual
 *  Description:  判断输入的两个点是否相等
 * =====================================================================================
 */
bool isPointEqual( POINT pa, POINT pb );

#include "heap.h"
#include "StackArray.h"
#include "myDequeArray.h"
#include "dfsPathFinder.h"
#include "bfsPathFinder.h"
#include "aStar.h"
#include "Map.h"
#include "Manage.h"

#endif
