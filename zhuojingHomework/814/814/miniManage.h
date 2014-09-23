/*
	������ miniManage�� ��Ϸ��������
		  ���������Ϸ��һ�У���Ϸ�ĺ���

	���ڣ� 2014.08.14

	���ߣ� pinkbeen
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
	// ��Ϸ��ʼ��ʱ�����ȥ��ʱ�䣬�Ժ���Ϊ��λ
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