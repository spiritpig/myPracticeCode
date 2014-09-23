/*
 *  说明： player类的实现文件
 *
 *  日期： 2014.7.31
 *  作者： pinkbeen
 */
#include "commonHeader.h"

//---------------------------------------------------------------------------
bool player::isHitBuilding( const Point &pos, 
						    const char * const mapData )
{
	return mapData[ pos.y * MAP_WIDTH + pos.x] == BUILDING_ROOM;
}
//---------------------------------------------------------------------------
bool player::isHitBuildingRoom( const Point &pos, 
								const char * const mapData )
{
	return mapData[ pos.y * MAP_WIDTH + pos.x] == BUILDING_ROOM;
}
//---------------------------------------------------------------------------
bool player::isHitGrass( const Point &pos, 
						 const char * const mapData )
{
	return mapData[ pos.y * MAP_WIDTH + pos.x] == GRASS;
}
//---------------------------------------------------------------------------
bool player::isHitRock( const Point &pos, 
					    const char * const mapData )
{
	return mapData[pos.y * MAP_WIDTH + pos.x] == ROCK;
}
//---------------------------------------------------------------------------
bool player::isHitMonster( const Point &pos, 
						   const char * const mapData )
{
	return mapData[ pos.y * MAP_WIDTH + pos.x] == MONSTER;
}
//---------------------------------------------------------------------------
bool player::isHitBorder( const Point &pos, 
						  const char * const mapData )
{
	return mapData[ pos.y * MAP_WIDTH + pos.x] == BORDER;
}
//---------------------------------------------------------------------------
int player::move( const char * const mapData, char dir )
{
	Point pos = { state.pos.x, state.pos.y };

	// 这里采用先模拟移动，然后用这个坐标检测是否可以移动的方法
	// 这样写，只需要在switch语句外面，判断是否可行即可
	// 若可行，则将这个临时坐标值赋给主角的实际坐标值
	switch( dir )
	{
	case 'W': case 'w':
		{
			pos.y--;
		}
		break;

	case 'S': case 's':
		{
			pos.y++;
		}
		break;

	case 'A': case 'a':
		{
			pos.x--;
		}
		break;

	case 'D': case 'd':
		{
			pos.x++;
		}
		break;
	}

	if( isHitMonster( pos, mapData ) )
	{
		return HIT_MONSTER;
	}
	else
	if ( !isHitBorder( pos, mapData ) && 
		 !isHitBuilding( pos, mapData ) && 
		 !isHitRock( pos, mapData ) )
	{
		state.pos.x = pos.x;
		state.pos.y = pos.y;

		return MOVEABLE;
	}

	// 仍需要做很多的处理，比如碰到怪物时战斗
	// 碰到入口时进入一个新地点
	/////////////////
	/////////////////
	/////////////////
	return CANNOT_MOVEABLE;
}
