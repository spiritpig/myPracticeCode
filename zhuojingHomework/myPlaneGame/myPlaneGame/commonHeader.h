#ifndef COMMONHEADER_AFX
#define COMMONHEADER_AFX

#include <Windows.h>
#include <iostream>
#include <cmath>
#include <Sgge.h>
#include "vector2d.h"
#pragma comment( lib, "Sgge.lib" )
 
const float ANGLE = 3.1415926f/180.0f;
const int MAP_HEIGHT = 600;
const int MAP_WIDTH  = 400;

const float FLOAT_COMPARE_PRECISION = 0.00001f;

const float PLANE_INIT_SPEED = 100.0f;
const float PLANE_HEAD_SCALE_PERCENT = 0.2f;

struct playerState
{
	vector2d pos;
	vector2d dir;

	float initSpeed;
	float selfSpeed;
};

//////////////////////////////////////////////////////////////////////////
// 子弹数据
const float BULLET_SPEED = PLANE_INIT_SPEED*8.0f;
const int BULLET_ROW_NUM = 1;
const int BULLET_CEL_NUM = 100;
const float BULLET_POS_OFFSET_X = 5.0f;
const float BULLET_POS_OFFSET_Y = -15.0f;
const float BULLET_SPACE_TIME = 0.1f;
const float BULLET_SCALE_PERCENT = 0.5f;

struct bulletState
{
	vector2d pos;
	vector2d dir;

	float angle;
	float initSpeed;
	float selfSpeed;

	bool isUsed;
};

//////////////////////////////////////////////////////////////////////////
// 导弹数据
const int MAX_DAODAN_NUM = 5;
const float DAODAN_SELF_SPEED = PLANE_INIT_SPEED*6.0f;
const float DAODAN_ANGLE_START = -20.0f;
const float DAODAN_ANGLE_OFFSET = 10.0f;
const float DAODAN_SPACE_TIME = 0.5f;
const float DAODAN_SCALE_PERCENT = 1.0f;

struct daodanState
{
	vector2d pos;
	vector2d dir;

	float angle;
	float initSpeed;
	float selfSpeed;

	bool isUsed;
};

//////////////////////////////////////////////////////////////////////////
// 敌机数据
struct dijiState
{
	vector2d pos;
	vector2d dir;

	float angle;
	float initSpeed;
	float selfSpeed;

	bool isUsed;
};


bool isFloatLowerEqualThanZero( float f );

#include "myMap.h"
#include "player.h"
#include "Manage.h"

#endif // END COMMONHEADER_AFX