/*
	描述： evil，怪物类
		  如名字所见，代表了一只怪物

	日期： 2014.08.14

	作者： pinkbeen
 */
#include "stdafx.h"

#ifndef EVIL_AFX
#define EVIL_AFX

class evil
{
public:
	evil::evil( int bmt );
	void walk( p2DArray mapData, int dir = -1 );

	const vector2 & getPos();
	const vector2 & getBulletPos();

	bool isBulletHitPlayer( const vector2 &pos );

private:
	vector2 pos;
	bullet myBullet;
};

#endif

//
//class ren
//{
//public:
//	void init(); // 初始化
//	void update();
//	void render();
//	void processinput();
//
//private:
//	float weizhix, weizhiy;
//};
//
//void ren::init()
//{
//	weizhix = 0.0f;
//	weizhiy = 0.0f;
//}
//
//void ren::updata()
//{
//}
//
//void ren::processinput()
//{
//}