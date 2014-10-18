//////////////////////////////////////////////////////////////////////////
//
//	通用定义文件，将所有的包含关系集中到这个文件中方便管理
//
//////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <Sgge.h>
#include <cmath>
#include <iostream>
#include "vector2.h"
#pragma comment( lib, "sgge.lib" )

#ifndef	COMMONHEADER
#define COMMONHEADER 

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

enum DAMAGE_TYPE
{
	DT_PHYSICAL_DAMAGE,
	DT_FIRE_DAMAGE,
	DT_ICE_DAMAGE,
	DT_LIGHTING_DAMAGE,
	DT_SHARP_DAMAGE,
	DT_BLUDGEONING_DAMAGE,
};

struct towerState
{
	int def;
	int cost;
	int atkRange;
	vector2 pos;
	bool isFire;
};

struct towerBulletState
{
	int min_atk;
	int max_atk;
	vector2 pos;
	vector2 dir;
	float speed;
	DAMAGE_TYPE at;
};
// struct COMMONTEXTURE
// {
// 	PSTEXTURE texture;
// 	size_t count;
// };

//////////////////////////////////////////////////////////////////////////
#include "baseTower.h"
#include "tower_Slipper.h"
#include "myMap.h"
#include "GameManager.h"

#endif	// END COMMONHEADER
