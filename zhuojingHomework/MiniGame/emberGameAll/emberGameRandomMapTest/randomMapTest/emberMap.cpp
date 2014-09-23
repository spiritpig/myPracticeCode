/*
 *  说明： emberMap类的实现文件
 *
 *  日期： 2014.7.17
 *  作者： pinkbeen
 */
#include "commonHeader.h"
using std::endl;
using std::cout;

//---------------------------------------------------------------------------
emberMap::emberMap()
{
	init();
}
//---------------------------------------------------------------------------
emberMap::~emberMap()
{
}
//---------------------------------------------------------------------------
void emberMap::init()
{
	holeMapHeight = MAP_HEIGHT;
	holeMapWidth = MAP_WIDTH;

	curMapCenter.x = holeMapWidth/2,
	curMapCenter.y = holeMapHeight/2;

	curCharacterPos.x = curMapCenter.x;
	curCharacterPos.y = curMapCenter.y;
 
    for( int i = 0; i < holeMapHeight; ++i )
    {
        // 初始化，地图数据为0
        for( int j = 0; j < holeMapWidth; ++j )
        {
            if( j == 0 || j == holeMapWidth - 1 ||
				i == 0 || i == holeMapHeight - 1 )
            {
                holeMap[i][j] = '*';
            }
            else
            {
                holeMap[i][j] = ' ';
            } 
        }
    }

	genRandomMap();
}

/*
// 地图变为定长得了，从文件读取地图暂时放弃
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
*/

//---------------------------------------------------------------------------
void emberMap::draw()
{
	system( "cls" );

	int offsetX = curMapCenter.x- MAP_DISPLAY_RANGE_HALFWIDTH, 
		offsetY = curMapCenter.y - MAP_DISPLAY_RANGE_HALFHEIGHT;

	// 周围有一圈围墙，所以宽度和高度各加2
	for ( int i = 0; i < MAP_DISPLAY_MAX_HEIGHT && offsetY + i < holeMapHeight; ++i )
	{
		for( int j = 0; j < MAP_DISPLAY_MAX_WIDTH && offsetX + j < holeMapWidth; ++j )
		{	
			if( i > 0 && i < MAP_DISPLAY_MAX_HEIGHT-1 &&
				j > 0 && j < MAP_DISPLAY_MAX_WIDTH-1 )
			{ 
				if( offsetX + j == curCharacterPos.x &&
					offsetY + i == curCharacterPos.y )
				{
					cout << HERO;
				}
				else
				{
					cout << holeMap[offsetY + i][offsetX + j];
				}
			}
			else
			{
				cout << '*';
			}
		}
		cout << endl;
	}
		
}
//---------------------------------------------------------------------------
void emberMap::moveMap( char dir )
{
	Point tempPos = { curCharacterPos.x, curCharacterPos.y };

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

	// 检测地图的显示是否越界
	if( !isXValOutOfMapRange( tempPos.x - MAP_DISPLAY_RANGE_HALFWIDTH + 1 ) &&
		!isXValOutOfMapRange( tempPos.x + MAP_DISPLAY_RANGE_HALFWIDTH - 1 ) &&
		offsetX != 0 )
	{
		int posX = curMapCenter.x + offsetX;
		
		// 不能显示原始地图的围墙部分，所以范围限制在 （1，holeMapWidth-2）
		if( posX > 0 && posX < holeMapWidth-1 )
		{
			curMapCenter.x += offsetX;
			return;
		}
	}
	else
	if( !isYValOutOfMapRange( tempPos.y - MAP_DISPLAY_RANGE_HALFHEIGHT + 1) &&
		!isYValOutOfMapRange( tempPos.y + MAP_DISPLAY_RANGE_HALFHEIGHT - 1 ) &&
		offsetY != 0 )
	{
		int posY = curMapCenter.y + offsetY;

		// 不能显示原始地图的围墙部分，所以范围限制在 （1，holeMapHeight-2）
		if( posY > 0 && posY < holeMapHeight-1 )
		{
			curMapCenter.y += offsetY;
			return;
		}
	}
	
}
//---------------------------------------------------------------------------
void emberMap::genRandomMap()
{
	int posNum = holeMapHeight*holeMapWidth;

	int monsterNum = random( posNum/100, posNum/200 );
	int grassNum = random( posNum/80, posNum/160 );
	int rockNum = random( posNum/100, posNum/160 );
	int buildingNum = random( 10, 5 );

	// 随机生成
	randomPutObjIntoMap( monsterNum, MONSTER );  
	randomPutObjIntoMap( grassNum, GRASS );
	randomPutObjIntoMap( rockNum, ROCK );
	randomPutObjIntoMap( buildingNum, BUILDING );
}
//---------------------------------------------------------------------------
void emberMap::randomPutObjIntoMap( const int times, const char flag )
{
	int posX, posY;

	for ( int i = 0; i < times; ++i )
	{
		posX = random( holeMapWidth - 1, 2 );
		posY = random( holeMapHeight - 1, 2 );

		if( flag != MONSTER )
		{
			// 随机生成物体块
			// 这种操作是为了使生成的地图，
			// 更加连续，而不是杂乱无章的单个块
			int blockRangeX = random( 8, 4 ),
				blockRangeY = random( 8, 4 );

			for( int j = 0; j < blockRangeY && !isYValOutOfMapRange( posY + j ); ++j )
			{
				for( int k = 0; k < blockRangeX && !isXValOutOfMapRange( posX + k ); ++k )
				{
					if( holeMap[posY+j][posX+k] == ' ' &&
						!isPosApproachToCenter( posX+k, posY+j ) )
					{
						holeMap[posY+j][posX+k] = flag;
					}
				}
			}
		}
		// 怪物只需要一个格子就够了
		else
		{
			if( holeMap[posY][posX] == ' ' )
			{
				holeMap[posY][posX] = flag;
			}
		}
		
	}
}
