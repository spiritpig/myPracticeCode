/*
	������ evil��������
		  ������������������һֻ����

	���ڣ� 2014.08.14

	���ߣ� pinkbeen
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
//	void init(); // ��ʼ��
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