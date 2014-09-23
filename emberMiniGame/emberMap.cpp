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
{
}

emberMap::~emberMap()
{
}

void emberMap::init()
{
    readMapFromFile( "map.dat" );

    rangeMap = new char*[ MAX_HEIGHT ];
    for( int i = 0; i < MAX_HEIGHT; ++i )
    {
        rangeMap[i] = new char[ MAX_WIDTH ];

        // 初始化，地图数据为0
        for( int j = 0; j < MAX_WIDTH; ++j )
        {
            if( j == 0 || j == MAX_WIDTH-1 )
            {
                rangeMap[i][j] = '|';
            }
            else
            if( i == 0 || i == MAX_HEIGHT -1 )
            {
                rangeMap[i][j] = '-';
            }
            else
            {
                rangeMap[i][j] = ' ';
            } 
        }
    }
}

void emberMap::destory()
{
    for( int i = 0; i < MAX_HEIGHT; ++i ) 
    {
        delete[] rangeMap[i];
    }
    delete[] rangeMap;
}

char** emberMap::getMap()
{
    return rangeMap;
}

void emberMap::setPosOnMap( int x, int y, int val )
{
    rangeMap[y][x] = val;
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

    fscanf( fp, "%d %d", holeMapY, holeMapX );
    printf( "%d,%d\n", holeMapY, holeMapX );

    holeMap = new char*[holeMapY];
    for( int i = 0; i < holeMapY; ++i )
    {
        holeMap[i] = new char[holeMapX];
//        fgets( holeMap[i], 1024, fp );

        cout << holeMap[i];
    }

    fclose( fp );
}
void emberMap::saveMapIntoFile( const char *filename )
{

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

    // 输出地图
    char **MyMap = em.getMap();
    output2DArray( MyMap, MAX_HEIGHT, MAX_WIDTH );

    em.setPosOnMap( 4, 5, 'q' );
    MyMap = em.getMap();
    cout << MyMap[5][4] << endl;

    em.destory();
    return 0;
}
