// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <conio.h>

#define STR_SPACE	"  "
#define STR_CURSOR	"◇"
#define MAP_ROW		20
#define MAP_CEL		20

struct Point
{
	int x, y;
};

struct cursorState
{
	Point pos;
	Point prevPos;
};

void gotoXY( int x, int y );
void hideConsoleCursor();

// TODO: 在此处引用程序要求的附加头文件
#include "cursor.h"