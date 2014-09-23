#include "stdafx.h"


miniMap::miniMap()
{
	for ( int i = 0; i < ROW; ++i )
	{
		for ( int j = 0; j < CEL; ++j )
		{
			if( (i == 0) || (i == ROW-1) ||
				(j == 0) || (j == CEL-1) )
			{
				mapData[i][j] = MS_STONE;
			}
			else
			{
				mapData[i][j] = MS_SPACE;
			}
		}
	}

	mapData[5][1] = MS_TREE;
	mapData[5][3] = MS_TREE;
	mapData[5][5] = MS_TREE;

	mapData[3][7] = MS_STONE;
	mapData[5][7] = MS_STONE;
	mapData[7][7] = MS_STONE;

	mapData[3][5] = MS_STONE;
	mapData[5][5] = MS_STONE;
	mapData[7][5] = MS_TREE;

	mapData[3][3] = MS_STONE;
	mapData[5][3] = MS_TREE;
	mapData[7][3] = MS_STONE;
}

miniMap::~miniMap()
{
}

void miniMap::draw()
{
	for ( int i = 0; i < ROW; ++i )
	{
		for ( int j = 0; j < CEL; ++j )
		{
			switch( mapData[i][j] )
			{
			case MS_STONE:
				{
					printf( "¨~" );
				}
				break;

			case MS_TREE:
				{
					printf( "¡ù" );
				}
				break;

			case MS_SPACE:
				{
					printf( "  " );
				}
				break;

			case MS_PLAYER:
				{
					printf( "©I" );
				}
				break;

			case MS_EVIL:
				{
					printf( "©Z" );
				}
				break;

			case MS_BULLET:
				{
					printf( "¨‘" );
				}
				break;
			}
		}

		printf( "\n" );
	}
}

p2DArray miniMap::getMapData()
{
	return mapData;
}

void miniMap::setPlayerData( const vector2 &pos )
{
	mapData[pos.x][pos.y] = MS_PLAYER;
}

void miniMap::clearPlayerData( const vector2 &pos )
{
	mapData[pos.x][pos.y] = MS_SPACE;
}

void miniMap::setEvilData( const vector2 &pos )
{
	mapData[pos.x][pos.y] = MS_EVIL;
}

void miniMap::clearEvilData( const vector2 &pos )
{
	mapData[pos.x][pos.y] = MS_SPACE;
}

void miniMap::setBulletData( const vector2 &pos )
{
	mapData[pos.x][pos.y] = MS_BULLET;
}

void miniMap::clearBulletData( const vector2 &pos )
{
	mapData[pos.x][pos.y] = MS_SPACE;
}