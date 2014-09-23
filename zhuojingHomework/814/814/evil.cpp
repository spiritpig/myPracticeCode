#include "stdafx.h"

evil::evil( int bmt )
: myBullet( bmt )
{
	this->pos.x = ROW-2;
	this->pos.y = CEL-2;
}

void evil::walk( p2DArray mapData, int dir )
{
	vector2 vel( 0, 0 );
	if( dir == -1 )
	{
		dir = rand()%4;
	}

	switch( dir )
	{
	case ED_UP:
		{
			if( mapData[pos.x-1][pos.y] == MS_SPACE )
			{
				--pos.x;
			}

			vel.x = -1;
			vel.y = 0;
		}
		break;

	case ED_DOWN:
		{
			if( mapData[pos.x+1][pos.y] == MS_SPACE )
			{
				++pos.x;
			}

			vel.x = 1;
			vel.y = 0;
		}
		break;

	case ED_LEFT:
		{
			if( mapData[pos.x][pos.y-1] == MS_SPACE )
			{
				--pos.y;
			}

			vel.x = 0;
			vel.y = -1;
		}
		break;

	case ED_RIGHT:
		{
			if( mapData[pos.x][pos.y+1] == MS_SPACE )
			{
				++pos.y;
			}

			vel.x = 0;
			vel.y = 1;
		}
		break;
	}

	if( myBullet.isExist() )
	{
		myBullet.move( mapData );
	}
	else
	{
		myBullet.resetBullet( pos.x, pos.y,
							  vel.x, vel.y );
	}
}

const vector2 & evil::getPos()
{
	return pos;
}

const vector2 & evil::getBulletPos()
{
	return myBullet.getPos();
}

bool evil::isBulletHitPlayer( const vector2 &pos )
{
	return myBullet.isHitPlayer( pos.x, pos.y );
}
