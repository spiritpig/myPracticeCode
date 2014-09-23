/*
 * 说明： ember 小游戏地图类
 *
 * 日期： 14.7.17
 * 作者:  pinkbin
 *
 */
#include "commonHeader.h"

#ifndef EMBER_MAP
#define EMBER_MAP

class emberMap
{
private:
	char dir;

    char **holeMap;
    int holeMapWidth, holeMapHeight;							// 整个地图的大小
	int mapDisplayOffsetX, mapDisplayOffsetY;					// 相对地图的中点的地图显示偏移量
	int holeMapCenterX, holeMapCenterY;							// 完整地图的中点，因为，每次显示都需要用到
																// 所以，存起来。备用
	void readMapFromFile( const char *filename );
	void saveMapIntoFile( const char *filename );

	bool isXValOutOfMapRange( int x )
	{
		if( x <= 0 || x >= holeMapWidth-1 )
		{
			return true;
		}
		return false;
	}

	bool isYValOutOfMapRange( int y )
	{
		if( y <= 0 || y >= holeMapHeight-1 )
		{
			return true;
		}
		return false;
	}

public:
    emberMap();
    ~emberMap();

    void init();
    void destory();

	// 显示地图，仅显示地图上的一块区域，偏移量由
	// mapDisplayOffsetX, mapDisplayOffsetY控制
	// 这个偏移量是相对地图的中点的
	void showMap();
	void moveMap();

    char** getMap();
    void setPosOnMap( int x, int y, int val );
};

#endif // EMBER_MAP
