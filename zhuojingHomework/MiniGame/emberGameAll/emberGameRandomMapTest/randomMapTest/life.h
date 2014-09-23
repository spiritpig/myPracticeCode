/*
 *  说明： life类， 代表一个可攻击移动的生物
 *          作为怪物和主角的公共基类
 *
 *  日期： 2014.7.25
 *  作者： pinkbeen
 */
#include "commonHeader.h"

#ifndef LIFE
#define LIFE

struct lifeInfo
{
public:
	int atk, def;
	int hp, mp;
	int isDefense;

	float defPercent; // 防御率，在防御姿态下所能抵挡的伤害百分比。
	Point pos;

	char name[20];

public:

	/**
	 *	 构造函数  
	 *
	 */
	lifeInfo( int iatk, 
			  int idef, 
			  int ihp, 
			  int imp, 
			  const char *iname );
	lifeInfo( const char *iname );
};

// 怪物和主角的基本信息
class life
{
protected:
	lifeInfo state;
	char model[5][6];									// 从文件中读取字符画模型
	Point modelSize;

	void initModel();

public:

	/**
	 *	 构造函数  
	 *
	 */
	life( const lifeInfo &li,
		  const char *iname, 
		  const char *modelFileName );
	life( const char *iname, const char *modelFileName );

	/**
	 *	  对某个生命体进行攻击
     *
     *	  参数
     *          l   我们要攻击的对象 
	 */
	virtual void attack( life &l );

	/**
	 *	  防御，会提高自身的抗打击能力
     *
	 */
	virtual void defense();

	/**
	 *	  声明体最本能的反应，逃跑
     *	  但是，不同的生命体逃跑的方式是不同的
     *
	 */
	virtual void runAway() = 0;


	// void releaseSkill(); 考虑加入
    
	/**
	 *	  从文件中读取模型信息
     *
     *	  参数
     *          filename   模型文件名 
	 *
	 *	  模型文件统一为5行5列
	 */
	void readModelFromFile( const char *filename );

	/**
	 *	  绘制模型
     *
	 *	  模型文件统一为5行5列
	 */
	void drawModel( const int startX, const int startY );

	const Point& getModelSize()
	{
		return modelSize;
	}
};

#endif	// LIFE
