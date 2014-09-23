/*
 *  说明： emberManager类， 该类是ember小游戏的管理人员
 *
 *  日期： 2014.7.31
 *  作者： pinkbeen
 */
#ifndef EMBER_MANAGER
#define EMBER_MANAGER

#include "commonHeader.h"

class emberManager
{
	emberMap	myMap;
	monster		evil;
	player		ember;
	bool		isFight;
	Tab			fightTab;

	/**
	 *	  绘制怪物和主角的战斗场景
     *
     *	  参数
     *	        plName				玩家的名字
     *	        plModelFileName		玩家模型文件的名字
	 *	        monName				怪物的名字
	 *	        monModelFileName	怪物模型文件的名字
	 */
	void drawFightScene( const player &pl,
						 const monster &mon );
public:

	/**
	 *	  构造函数
     *
     *	  参数
	 *			plLi				玩家的信息
     *	        plName				玩家的名字
     *	        plModelFileName		玩家模型文件的名字
	 *			monLi				怪物的信息
	 *	        monName				怪物的名字
	 *	        monModelFileName	怪物模型文件的名字
	 */
	emberManager( const lifeInfo &plLi, const char *plName, 
				  const char *plModelFileName, 
				  const lifeInfo &monLi, const char *monName, 
				  const char *monModelFileName );

	/**
	 *	  构造函数
     *
     *	  参数
     *	        plName				玩家的名字
     *	        plModelFileName		玩家模型文件的名字
	 *	        monName				怪物的名字
	 *	        monModelFileName	怪物模型文件的名字
	 */
	emberManager( const char *plName, 
				  const char *plModelFileName, 
				  const char *monName, 
				  const char *monModelFileName );

	/**
	 *	  析构函数
	 *
	 */
	~emberManager()
	{
	}

	void update();
	void processInput();
	void draw_scene();
};

#endif // EMBER_MANAGER end