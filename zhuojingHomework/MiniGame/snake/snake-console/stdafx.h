// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <tchar.h>
#include <cstdio>
#include <ctime>

const int MAP_WIDTH  = 20;
const int MAP_HEIGHT = 20;
const int MAX_SNAKE_NODE = (MAP_WIDTH-2)*(MAP_HEIGHT-2);

const char MAP_SPACE_CHAR = ' ';
const char MAP_SNAKE_CHAR = '#';
const char MAP_WALL_CHAR  = '*';
const char MAP_FOOD_CHAR  = 'F';

const char SPACE_CHAR[3] = "  ";
const char SNAKE_CHAR[3] = "  ";
const char SNAKE_HEAD_CHAR[3] = "  ";
//const char SNAKE_CHAR[3] = "⊙";
const char WALL_CHAR[3]  = "  ";
const char FOOD_CHAR[3]  = "  ";

const int LEFT	= -1;
const int RIGHT = 1;
const int UP	= -2;
const int DOWN	= 2;
const int NONE	= -3;

const int DEFAULT_TEXT_COLOR= 0x07;
const int SNAKE_TAIL_TEXT_COLOR	= 0xa0;
const int SNAKE_HEAD_TEXT_COLOR	= 0xe0;
const int WALL_TEXT_COLOR	= 0x90;
const int FOOD_TEXT_COLOR	= 0xc0;

struct point
{
	int x;
	int y;

	point& operator=( const point &b )
	{
		x = b.x;
		y = b.y;

		return *this;
	}
};

struct Node
{
	point data;
	Node *next;
};


int random( int min, int max );
void gotoXY( const int x, const int y );
void changeTextColor( int color );
void clearInputCache();

// TODO: 在此处引用程序要求的附加头文件
#include "queue.h"
#include "map.h"
#include "snake.h"
#include "food.h"