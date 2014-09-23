// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <cmath>
#include <conio.h>
#include <time.h>

#define ROW 10
#define CEL 10
#define MONSTER_FINDPATH_BASE 10

// 代表了怪物在三个阶段中的寻路几率
const int MAX_STAGE = 3;
// 不同阶段的持续时间，以毫秒计
const int STAGE_DURATION[MAX_STAGE] = { 9000, 7000, 5000 };
const float MONSTER_FINDPATH_PERCENT[MAX_STAGE] = { 0.1f, 0.3f, 0.6f };

enum MAP_STATE
{
	MS_SPACE,
	MS_STONE = 4,
	MS_TREE,

	MS_WALKED, 
	MS_START, 
	MS_END,

	MS_PLAYER,
	MS_EVIL,
	MS_BULLET
};

enum EVIL_DIR
{
	ED_UP,
	ED_DOWN,
	ED_LEFT,
	ED_RIGHT
};

typedef const char ( * const p2DArray ) [CEL];

// TODO: 在此处引用程序要求的附加头文件
#include "Vector2.h"
#include "Queue.h"
#include "pathFinder.h"
#include "miniMap.h"
#include "bullet.h"
#include "player.h"
#include "evil.h"
#include "miniManage.h"