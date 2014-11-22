//////////////////////////////////////////////////////////////////////////
//
//	通用定义文件，将所有的包含关系集中到这个文件中方便管理
//
//////////////////////////////////////////////////////////////////////////
#ifndef BNB_COMMON_HEADER
#define BNB_COMMON_HEADER

#include <Windows.h>
#include <Sgge.h>
#include <stdio.h>
#include <math.h>
#include "Vector2D.h"
#pragma comment( lib, "sgge.lib" )

enum BLOCK_KIND
{
	BK_NONE,
	BK_GRASS1,
	BK_GRASS2,
	BK_GRASS3,
	BK_GRASS4,
	BK_GRASS5,
	BK_ROAD1,
	BK_ROAD2,
	BK_ROAD3,

	BK_HOUSE1 = 10,
	BK_HOUSE2,
	BK_HOUSE3,
	BK_TREE,
	BK_BLOCK1,
	BK_BLOCK2,
	BK_BOX,

	BK_HOUSE1TOP = 20,
	BK_HOUSE2TOP,
	BK_HOUSE3TOP,
	BK_TREETOP,
	BK_BLOCK1TOP,
	BK_BLOCK2TOP,
	BK_BOXTOP
};

enum DIR
{
	D_NONE,
	D_UP,
	D_DOWN,
	D_LEFT,
	D_RIGHT
};

struct RoleData
{
	Vec2D pos;
	float speed;
	float maxSpeed;
	DIR dir;
	SggeRect rect;
	SggeFrameAnimat *roleFA;
};

enum ROLE_STATE
{
	RS_STAND,
	RS_WALK,
	RS_DYING,
	RS_DIED
};

struct PlayerData
{
	int curPopNum;
	int maxPopNum;
};

#define CLIENT_WIDTH		800
#define CLIENT_HEIGHT		600
#define MAP_MAX_ROW			13
#define MAP_MAX_CEL			15
#define BLOCK_SIZE			40
#define PATH_ADJUST_RANGE	10

extern Vec2D DirUp;
extern Vec2D DirDown;
extern Vec2D DirLeft;
extern Vec2D DirRight;

//////////////////////////////////////////////////////////////////////////
#include "GameMap.h"
#include "Role.h"
#include "Player.h"
#include "GameManager.h"

#endif // END BNB_COMMON_HEADER