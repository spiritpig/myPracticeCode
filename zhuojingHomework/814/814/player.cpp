#include "stdafx.h"


player::player()
{
	pos.x = 1;
	pos.y = 1;
}

player::~player()
{
}

void player::walk( p2DArray mapData, char dir )
{
	switch( dir )
	{
	case 'w': case 'W':
		{
			if( mapData[pos.x-1][pos.y] == MS_SPACE )
			{
				--pos.x;
			}
		}
		break;

	case 's': case 'S':
		{
			if( mapData[pos.x+1][pos.y] == MS_SPACE )
			{
				++pos.x;
			}
		}
		break;

	case 'a': case 'A':
		{
			if( mapData[pos.x][pos.y-1] == MS_SPACE )
			{
				--pos.y;
			}
		}
		break;

	case 'd': case 'D':
		{
			if( mapData[pos.x][pos.y+1] == MS_SPACE )
			{
				++pos.y;
			}
		}
		break;
	}
}

vector2 const & player::getPos()
{
	return pos;
}