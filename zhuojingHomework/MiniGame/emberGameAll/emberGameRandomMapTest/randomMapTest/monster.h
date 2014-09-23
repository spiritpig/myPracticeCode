/*
 *  说明： monster类， 代表一个怪物
 *
 *  日期： 2014.7.31
 *  作者： pinkbeen
 */

#ifndef MONSTER_M
#define MONSTER_M

#include "commonHeader.h"

class monster : public life
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
	monster( const lifeInfo &li, const char *name, 
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
	monster( const char *name, const char *modelFileName )
		: life( name, modelFileName )
	{}

	/**
	 *	  析构函数
     *
	 */
	~monster()
	{
	}


	/**
	 *	  嘲讽函数，用于嘲讽玩家角色
     *
	 */
	void taunt()
	{
	}

	/**
	 *	  逃跑函数，怪物的逃跑
     *
	 */
	void runAway()
	{
	}
};

#endif	// MONSTER_M end