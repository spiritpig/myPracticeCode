/*
	描述： miniManage， 游戏管理器类
		  负责管理游戏的一切，游戏的核心

	日期： 2014.08.14

	作者： pinkbeen
 */
#include "stdafx.h"

#ifndef MINIMANAGE_AFX
#define MINIMANAGE_AFX

class miniManage
{
private:
	bool isEvilHitPlayer();

public:
	miniManage();
	~miniManage();

	void update();
	void render();
	void processInput();
	void gameLoop();

private:
	// 游戏开始的时间和逝去的时间，以毫秒为单位
	int startTime;
	int elpasedTime;

	pathFinder pfGuy;

	miniMap myMap;
	player fireMan;
	evil monster;

	int curStage;
	bool isRun;
};

#endif