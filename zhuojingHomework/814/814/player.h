/*
	������ player�������
		  ������ҵ�ȫ����Ϣ�Ͳ���

	���ڣ� 2014.08.14

	���ߣ� pinkbeen
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