#include "stdafx.h"


state::state( int mt )
: maxTime( mt )
{
	pos.x = 0;
	pos.y = 0;

	velocity.x = 0;
	velocity.y = 0;

	isExist = false;

}

state::state( int x, int y, int mt, int vx, int vy )
: maxTime( mt )
{
	isExist = true;

	pos.x = x;
	pos.y = y;

	velocity.x = vx;
	velocity.y = vy;
}

//bool bullet::isOutOfRange( p2DArray mapData, int x, int y )
//{
//	if( x < 0 || x > ROW ||
//		y < 0 || y > CEL )
//	{
//		return true;
//	}
//
//	return false;
//}

bool bullet::isHitObstacle( p2DArray mapData, int x, int y )
{
	if( (mapData[x][y] == MS_STONE) ||
		(mapData[x][y] == MS_TREE) )
	{
		return true;
	}

	return false;
}

bullet::bullet( int x, int y, int maxTime, int vx, int vy )
: bulletState( x, y, maxTime, vx, vy )
{
}

bullet::bullet( int mt )
: bulletState( mt )
{
}

bullet::~bullet( void )
{
}

void bullet::move( p2DArray mapData )
{
	if( !isHitObstacle( mapData, bulletState.pos.x + bulletState.velocity.x,
								 bulletState.pos.y + bulletState.velocity.y ) && 
		bulletState.time < bulletState.maxTime )  
	{
		bulletState.pos.x += bulletState.velocity.x;
		bulletState.pos.y += bulletState.velocity.y;

		++bulletState.time;;
	}
	else
	{
		bulletState.isExist = false;
	}
}

bool bullet::isExist()
{
	return bulletState.isExist;
}

void bullet::resetBullet( int newPosX, int newPosY,
					  	  int newVelX, int newVelY )
{
	bulletState.pos.x = newPosX;
	bulletState.pos.y = newPosY;

	bulletState.velocity.x = newVelX;
	bulletState.velocity.y = newVelY;

	bulletState.isExist = true;

	bulletState.time = 0;
}

const vector2 & bullet::getPos()
{
	return bulletState.pos;
}

bool bullet::isHitPlayer( int x, int y )
{
	return (bulletState.pos.x == x) &&
		   (bulletState.pos.y == y);
}
