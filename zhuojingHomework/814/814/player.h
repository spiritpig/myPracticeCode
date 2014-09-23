/*
	描述： player，玩家类
		  储存玩家的全部信息和操作

	日期： 2014.08.14

	作者： pinkbeen
 */
#include "stdafx.h"

#ifndef PLAYER_AFX
#define PLAYER_AFX

class player
{
public:
	player();
	~player();

	void walk( p2DArray mapData, char dir );

	vector2 const & getPos();

private:
	vector2 pos;
};

#endif