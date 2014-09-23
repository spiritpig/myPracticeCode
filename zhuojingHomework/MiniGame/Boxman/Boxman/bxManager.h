#include "stdafx.h"

#ifndef BXMANAGER_AFX
#define BXMANAGER_AFX

class bxManager
{
public:
	bxManager();
	~bxManager();

	void init( const char *filename = "map.dat" );
	void update();
	void draw();
	void drawMap();
	void gameLoop();

private:
	void _redrawPos( const point &p );

	// 从文件中读取，数据
	// 这些数据包括： 地图布局，盒子位置，玩家位置
	// 目标地点并不需要记录。
	void _fillDataFromFile( const char *filename );
	bool _isWin();

	bool isRun;

	char **m_MapData;
	int m_MapCel, m_MapRow;
	int m_BoxNum, m_FinishedBoxNum;

	bxBox *m_Boxes;
	bxPlayer m_Hero;
};

#endif // END BXMANAGER_AFX