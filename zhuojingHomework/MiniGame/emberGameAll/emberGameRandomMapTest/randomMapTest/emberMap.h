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
	char holeMap[MAP_HEIGHT][MAP_WIDTH];						// 大地图，我们只会显示其中的一部分
	int holeMapWidth, holeMapHeight;							// 整个地图的大小
	Point curMapCenter;										 // 显示地图区域中点在大地图中的位置，因为，每次显示都需要用到
																// 所以，存起来。备用
	Point curCharacterPos;									  // 这个坐标需要从外部传递进来， 主角的坐标

	// void readMapFromFile( const char *filename );
	// void saveMapIntoFile( const char *filename );
    
	/**
	 *	 生成随机的地图  
	 *
	 */
	void genRandomMap();

	/**
	 *	  判断x坐标是否越界
     *
     *	  参数
     *	        x   需要检测的横坐标值
	 */
	bool isXValOutOfMapRange( int x )
	{
		if( x <= 0 || x >= holeMapWidth-1 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 *	  判断传入的位置是否在接近地图中心的位置
	 *	  以地图中心为中心7x7的范围为接近的位置
     *
     *	  参数
     *	        x   需要检测的横坐标值
	 *	        y   需要检测的纵坐标值
	 */
	bool isPosApproachToCenter( const int &x, const int &y )
	{
		if( x >= holeMapWidth/2 - 3 && 
			x <= holeMapWidth/2 + 3 && 
			y >= holeMapHeight/2 - 3 &&
			y <= holeMapHeight/2 + 3 )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/**
	 *	  判断y坐标是否越界
     *
     *	  参数
     *	        y   需要检测的纵坐标值
	 */
	bool isYValOutOfMapRange( int y )
	{
		if( y <= 0 || y >= holeMapHeight-1 )
		{
			return true;
		}
		return false;
	}

	/**
	 *	  随机的放置物体到地图中，生成的物体会以块状呈现
     *
     *	  参数
     *	        time    需要放置的物体数量
     *	        flag    需要放置的物体的符号
	 */
	void randomPutObjIntoMap( const int times, const char flag );

public:

	/**
	 *	  构造函数和析构函数
	 */
	emberMap();
	~emberMap();

	/**
	 *	  初始化地图类，负责地图的填充和变量的赋值
     *
	 */
	void init();

	/**
     *	  显示地图，仅显示地图上的一块区域，偏移量由
     *	  mapDisplayOffsetX, mapDisplayOffsetY控制 
     *	  这个偏移量是相对地图的中点的
     *
     *	  参数
     *	        time    需要放置的物体数量
     *	        flag    需要放置的物体的符号
	 */
	void draw();

	/**
     *	  移动实际显示的地图区域
     *
     *	  参数
     *	        dir     移动的方向
	 */
	void moveMap( char dir );



	//////////////////////////////////////////////////////////////////////////
	//
	//		getter 和 setter
	//
	//////////////////////////////////////////////////////////////////////////
	int getMapHeight()
	{
		return holeMapHeight;
	}

	int getMapWidth()
	{
		return holeMapWidth;
	}

	const char * const emberMap::getMap()
	{
		return &holeMap[0][0];
	}

	void setHeroPos( const Point &pos )
	{
		curCharacterPos.x = pos.x;
		curCharacterPos.y = pos.y;
	}

	const Point& getCurMapCenter()
	{
		return curMapCenter;
	}
};

#endif // EMBER_MAP
