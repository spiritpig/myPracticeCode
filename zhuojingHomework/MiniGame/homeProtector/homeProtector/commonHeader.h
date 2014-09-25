//////////////////////////////////////////////////////////////////////////
//
//	通用定义文件，将所有的包含关系集中到这个文件中方便管理
//
//////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <Sgge.h>
#pragma comment( lib, "sgge.lib" )

#ifndef	COMMONHEADER
#define COMMONHEADER 

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
	int min_atk;
	int max_atk;
	int def;
	int cost;
	int atkRange;
	float atkSpeed;
	DAMAGE_TYPE at;
};

//////////////////////////////////////////////////////////////////////////
#include "autoTextureManager.h"
#include "baseTower.h"
#include "tower_Slipper.h"
#include "myMap.h"
#include "GameManager.h"

#endif	// END COMMONHEADER
