#include "stdafx.h"
using std::cout;
using std::endl;

//---------------------------------------------------------------------------
void snakeMap::initMap()
{
	for ( int i = 0; i < MAP_HEIGHT; ++i )
	{
		for ( int j = 0; j < MAP_WIDTH; ++j )
		{
			if( i == 0 || i == MAP_HEIGHT-1 ||
				j == 0 || j == MAP_WIDTH-1 )
			{
				mapData[i][j] = MAP_WALL_CHAR;
			}
			else
			{
				mapData[i][j] = MAP_SPACE_CHAR;
			}
		}
	}
		
}
//---------------------------------------------------------------------------
void snakeMap::draw()
{
	// 擦掉前一次的地图输出
	system( "cls" );

	// 重新画一下地图
	for ( int i = 0; i < MAP_HEIGHT; ++i )
	{
		for ( int j = 0; j < MAP_WIDTH; ++j )
		{
			if( mapData[i][j] == MAP_SPACE_CHAR )
			{
				changeTextColor( DEFAULT_TEXT_COLOR );
				cout << SPACE_CHAR;
			}
			else
			if( mapData[i][j] == MAP_WALL_CHAR )
			{
				changeTextColor( WALL_TEXT_COLOR );
				cout << WALL_CHAR;
			}
		}
		cout << endl;
	}

	changeTextColor( DEFAULT_TEXT_COLOR );
}
