// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <cstdio>
#include <conio.h>

struct point 
{
	int x,y;
};

const char SPACE_CHAR[3]	= "  ";
const char WALL_CHAR[3]		= "▇";
const char BOX_CHAR[3]		= "〓";
const char GOAL_CHAR[3]		= "※";
const char PLAYER_CHAR[3]	= "☆";

typedef char ** MAPDATA;

enum MAP_STATE
{ 
	MS_SPACE,
	MS_WALL,
	MS_BOX,
	MS_PLAYER,
	MS_GOAL
};

void gotoXY( int x, int y );
bool isPointEqual( const point &p1, const point &p2 );
bool isPointEqual( int p1X, int p1Y, int p2X, int p2Y );

// TODO: 在此处引用程序要求的附加头文件
#include "bxBox.h"
#include "bxPlayer.h"
#include "bxManager.h"