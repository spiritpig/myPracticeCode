/*
 *  ˵���� map�࣬ ������̰���ߵĵ�ͼ
 *
 *  ���ڣ� 2014.7.31
 *  ���ߣ� pinkbeen
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