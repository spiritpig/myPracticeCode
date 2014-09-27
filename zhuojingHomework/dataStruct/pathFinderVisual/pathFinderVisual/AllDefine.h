#ifndef AFX_ALLDEFINE
#define AFX_ALLDEFINE

#include <Engine_Define.h>
#pragma comment(lib,"Sgge.lib")
#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <limits.h>

#define ROW 15
#define COL 20

#define SPACE	0
#define NOWALK	1
#define WALKING 2
#define WALKED	3
#define START	4
#define END		5
#define PATH	6

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

bool isPointOutOfRange( const POINT &pos );
bool isPointValid( char (*mapdata)[COL], const POINT &pos );
bool isPointEqual( int paX, int paY, int pbX, int pbY );
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
