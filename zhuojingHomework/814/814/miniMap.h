/*
	������ miniMap�� ��Ϸ��ͼ��
		  ����ά����Ϸ�ĵ�ͼ

	���ڣ� 2014.08.14

	���ߣ� pinkbeen
 */
#include "stdafx.h"

#ifndef MINIMAP_AFX
#define MINIMAP_AFX

class miniMap
{
public:
	miniMap();
	~miniMap();

	void draw();

	p2DArray getMapData();

	void setPlayerData( const vector2 &pos );
	void clearPlayerData( const vector2 &pos );

	void setEvilData( const vector2 &pos );
	void clearEvilData( const vector2 &pos );

	void setBulletData( const vector2 &pos );
	void clearBulletData( const vector2 &pos );

private:
	char mapData[ROW][CEL];
};

#endif