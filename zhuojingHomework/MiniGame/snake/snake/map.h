/*
 *  说明： map类， 该类是贪吃蛇的地图
 *
 *  日期： 2014.7.31
 *  作者： pinkbeen
 */
#ifndef SNAKE_MAP
#define SNAKE_MAP

#include "stdafx.h"

class snakeMap
{
	char mapData[MAP_HEIGHT][MAP_WIDTH];

public:
	snakeMap()
	{
		initMap();
	}
	~snakeMap()
	{
	}

	void initMap();
	void draw();
};

#endif // SNAKE_MAP end