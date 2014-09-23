/*
 *  说明： player类， 代表一个玩家
 *
 *  日期： 2014.7.31
 *  作者： pinkbeen
 */
#ifndef PLAYER
#define PLAYER

#include "life.h"

class player : public life
{
public:
	/**
	 *	  构造函数
     *
     *	  参数
     *	        li              生命体的信息
     *	        name            生命体的名字
     *	        modelFileName   模型文件的名字
	 */
	player( const lifeInfo &li, const char *name, 
			const char *modelFileName )
		: life( li, name, modelFileName )
	{}

	/**
	 *	  构造函数
     *
     *	  参数
     *	        name            生命体的名字
     *	        modelFileName   模型文件的名字
	 */
	player( const char *name, const char *modelFileName )
		: life( name, modelFileName )
	{}

	
	/**
	 *	  析构函数
	 *
	 */
	~player()
	{
	}

	/**
	 *	  主角可以在适当的时候，逃离战场
     *
	 */
	void runAway(){}

	/**
	 *	  碰撞检测部分
     *
     *	  参数
     *          pos         需要检测的点的位置
     *          mapData     地图数据
	 */
	bool isHitBuilding( const Point &pos, 
						const char * const mapData );
	bool isHitBuildingRoom( const Point &pos, 
							const char * const mapData );
	bool isHitGrass( const Point &pos, 
					 const char * const mapData );
	bool isHitRock( const Point &pos, 
					const char * const mapData );
	bool isHitMonster( const Point &pos, 
					   const char * const mapData );
	bool isHitBorder( const Point &pos, 
					  const char * const mapData );

	/**
	 *	  控制移动
     *
     *	  参数
     *          mapData     地图数据 
     *          dir         需要移动的方向
     *
     *	  返回值
     *          碰到的目标代号
     *          CANNOT_MOVEABLE  不可移动的情况
     *          MOVEABLE         可移动的情况
     *          HIT_ROOM         碰到了门
     *          HIT_MONSTER	     碰到了怪物
     *
	 */
	int move( const char * const mapData, char dir );


    //////////////////////////////////////////////////////////////////////
    //
    //  getter 和 setter
    //
    //////////////////////////////////////////////////////////////////////
	void setPos( const int &x, const int &y )
	{
		state.pos.x = x;
		state.pos.y = y;
	}

	const Point & getPos()
	{
		return state.pos;
	}
};

#endif // PLAYER
