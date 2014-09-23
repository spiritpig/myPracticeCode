// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#include <iostream>
#include <tchar.h>

#define BOARD_CEL 15
#define BOARD_ROW 15

enum MAP_STATUS
{
	MS_SPACE,
	MS_BORDER,
	MS_BLACKCHESS,
	MS_WHITECHESS
};

struct Point
{
	int x;
	int y;
};

// TODO: 在此处引用程序要求的附加头文件
#include "chessBoard.h"
