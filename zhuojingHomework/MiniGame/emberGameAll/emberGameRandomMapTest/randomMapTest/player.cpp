/*
 *  ˵���� player���ʵ���ļ�
 *
 *  ���ڣ� 2014.7.31
 *  ���ߣ� pinkbeen
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

	// ���������ģ���ƶ���Ȼ��������������Ƿ�����ƶ��ķ���
	// ����д��ֻ��Ҫ��switch������棬�ж��Ƿ���м���
	// �����У��������ʱ����ֵ�������ǵ�ʵ������ֵ
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

	// ����Ҫ���ܶ�Ĵ���������������ʱս��
	// �������ʱ����һ���µص�
	/////////////////
	/////////////////
	/////////////////
	return CANNOT_MOVEABLE;
}
