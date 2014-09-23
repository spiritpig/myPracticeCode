// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

const int CLOCK_WIDTH_TIMES = 5;

struct pos
{
	int x;
	int y;
};

int random( int min, int max );
void gotoxy( int x, int y );

// TODO: 在此处引用程序要求的附加头文件
