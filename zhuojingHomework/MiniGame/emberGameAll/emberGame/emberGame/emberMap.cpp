/*
 * =====================================================================================
 *
 *       Filename:  emberMap.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014/7/17 9:40:06
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "emberMap.h"
#include "commonHeader.h"
using std::endl;
using std::cout;

emberMap::emberMap()
: mapDisplayOffsetX(0), mapDisplayOffsetY(0),
	dir( ' ' )
{
}

emberMap::~emberMap()
{
}

void emberMap::init()
{
    readMapFromFile( "map.dat" );
	holeMapCenterX = holeMapWidth/2,
	holeMapCenterY = holeMapHeight/2;

  //  rangeMap = new char*[ MAX_HEIGHT ];
  //  for( int i = 0; i < MAX_HEIGHT; ++i )
  //  {
  //      rangeMap[i] = new char[ MAX_WIDTH+1 ];

  //      // 初始化，地图数据为0
  //      for( int j = 0; j < MAX_WIDTH; ++j )
  //      {
  //          if( j == 0 || j == MAX_WIDTH-1 )
  //          {
  //              rangeMap[i][j] = '|';
  //          }
  //          else
  //          if( i == 0 || i == MAX_HEIGHT -1 )
  //          {
  //              rangeMap[i][j] = '-';
  //          }
  //          else
  //          {
  //              rangeMap[i][j] = ' ';
  //          } 
  //      }

		//rangeMap[i][MAX_WIDTH] = '\0';
  //  }
}

void emberMap::destory()
{
    //for( int i = 0; i < MAX_HEIGHT; ++i ) 
    //{
    //    delete[] rangeMap[i];
    //}
    //delete[] rangeMap;

	
	for( int j = 0; j < holeMapHeight; ++j )
	{
		delete[] holeMap[j];
	}
	delete[] holeMap;
}

char** emberMap::getMap()
{
    return holeMap;
}

void emberMap::setPosOnMap( int x, int y, int val )
{
    holeMap[y][x] = val;
}

void emberMap::readMapFromFile( const char *filename )
{
    FILE *fp;
    fp = fopen( filename, "r" );

    if( !fp )
    {
        printf( "can't open map file!\n" );
        return;
    }

	// 从地图的首行读取地图大小
	// 地图的列数比实际的多2，这是为了防止fgets在读取一行字符之后
	// 将数组的最后一位的后一个位置赋值为'\0'
    fscanf( fp, "%d %d", &holeMapHeight, &holeMapWidth );

	char temp[10];
	fgets( temp, 1024, fp );

    holeMap = new char*[holeMapHeight];
    for( int i = 0; i < holeMapHeight; ++i )
    {
        holeMap[i] = new char[holeMapWidth];
        fgets( holeMap[i], 1024, fp );
		holeMap[i][holeMapWidth-2] = '\0';

		// cout << "line" << i+1 << ": " << strlen( holeMap[i] ) << ' ';
    }
	// cout << endl;

    fclose( fp );
}

void emberMap::saveMapIntoFile( const char *filename )
{
	// 保存地图到文件，暂时不使用
	///////////////
	///////////////
	///////////////
}

void emberMap::showMap()
{
	system( "cls" );

	int offsetX = holeMapCenterX- MAP_DISPLAY_RANGE_HALFWIDTH + mapDisplayOffsetX, 
		offsetY = holeMapCenterY - MAP_DISPLAY_RANGE_HALFHEIGHT + mapDisplayOffsetY;

	// 周围有一圈围墙，所以宽度和高度各加2
	for ( int i = 0; i < MAP_DISPLAY_MAX_HEIGHT + 2 && offsetY + i < holeMapHeight; ++i )
	{
		for( int j = 0; j < MAP_DISPLAY_MAX_WIDTH + 2 && offsetX + j < holeMapWidth; ++j )
		{	
			if( i > 0 && i < MAP_DISPLAY_MAX_HEIGHT+1 && 
				j > 0 && j < MAP_DISPLAY_MAX_WIDTH+1 )
			{ 
				cout << holeMap[offsetY + i][offsetX + j];
			}
			else
			{
				cout << "*";
			}
		}
		cout << endl;
	}
		
}

void emberMap::moveMap()
{
	if( kbhit() )
	{
		dir = getch();
	}

	int offsetX = 0, offsetY = 0;
	switch( dir )
	{
	case 'w': case 'W':
		{
			offsetY = -1;
		}
		break;

	case 's': case 'S':
		{
			offsetY = 1;
		}
		break;

	case 'a': case 'A':
		{
			offsetX = -1;
		}
		break;

	case 'd': case 'D':
		{
			offsetX = 1;
		}
		break;
	}


	int left, right, top, bottom;
	// 检测地图的显示是否越界
	if( offsetX != 0 )
	{
		left = mapDisplayOffsetX + holeMapCenterX - MAP_DISPLAY_RANGE_HALFWIDTH + offsetX;
		right = mapDisplayOffsetX + holeMapCenterX + MAP_DISPLAY_RANGE_HALFWIDTH + offsetX;

		// 不能显示原始地图的围墙部分，所以范围限制在 （2，holeMapWidth-3）
		if( left > 2 && right < holeMapWidth-3 )
		{
			mapDisplayOffsetX += offsetX;
			return;
		}
	}
	else
	{
		top = mapDisplayOffsetY + holeMapCenterY - MAP_DISPLAY_RANGE_HALFHEIGHT + offsetY;
		bottom = mapDisplayOffsetY + holeMapCenterY + MAP_DISPLAY_RANGE_HALFHEIGHT + offsetY;

		if( top> 2 && bottom < holeMapHeight-3 )
		{
			mapDisplayOffsetY += offsetY;
		}
	}
	
}


//////////////////////////////////////////////////////////////////////////////////
//
// 入口点函数
//
//////////////////////////////////////////////////////////////////////////////////
int main( void )
{
    emberMap em;
    em.init();

	while ( 1 )
	{
		em.moveMap();
		// 输出地图
		em.showMap();
	}

    //em.setPosOnMap( 4, 5, 'q' );
	//em.showMap();

    em.destory();
    return 0;
}