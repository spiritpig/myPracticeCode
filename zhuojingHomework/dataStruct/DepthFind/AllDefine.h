#ifndef AFX_ALLDEFINE
#define AFX_ALLDEFINE

#include <Engine_Define.h>
#pragma comment(lib,"Sgge.lib")
#include <Windows.h>
#include <tchar.h>

#define ROW 10
#define COL 10

#define SPACE	0
#define NOWALK	1
#define WALKING 2
#define WALKED	3
#define START	4
#define END		5
#define PATH	6

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

#include "StackDarrry.h"
#include "dfsPathFinder.h"
#include "Map.h"
#include "Manage.h"

#endif
