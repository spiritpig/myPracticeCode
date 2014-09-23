// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#include <iostream>
#include <tchar.h>
#include <cmath>

// TODO: 在此处引用程序要求的附加头文件
#define ROW 10
#define CEL 10
typedef const char ( * const p2DArray )[CEL];

struct point
{
	int x;
	int y;
};

enum MAP_STATE{ MS_SPACE, MS_STONE=4, MS_WALKED, MS_START, MS_END };

#include "Vector2.h"
#include "Queue.h"
#include "pathFinder.h"