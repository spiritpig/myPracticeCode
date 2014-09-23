/*
	描述： bullet，子弹类。
		  存储了怪物的子弹信息和操作

	日期： 2014.08.14

	作者： pinkbeen
 */
#include "stdafx.h"

#ifndef BULLET_AFX
#define BULLET_AFX

struct state 
{
	bool isExist;
	vector2 pos;
	vector2 velocity;
	int time;
	const int maxTime;

	state( int mt );
	state( int x, int y, int mt, int vx, int vy );
};


class bullet
{
private:
	//bool isOutOfRange( p2DArray mapData, int x, int y );
	bool isHitObstacle( p2DArray mapData, int x, int y );

public:
	bullet( int mt );
	bullet( int x, int y, int maxTime, int vx, int vy );
	~bullet();

	bool isExist();
	bool isHitPlayer( int x, int y );

	void move( p2DArray mapData );
	void resetBullet( int newPosX, int newPosY,
					  int newVelX, int newVelY );

	const vector2 & getPos();

private: 
	state bulletState;
};

#endif