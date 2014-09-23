/*
 * 说明： ember 小游戏地图类
 *
 * 日期： 14.7.17
 * 作者:  pinkbin
 *
 */
#include "commonHeader.h"

#ifndef EMBER_MAP
#define EMBER_MAP

class emberMap
{
private:
    char **holeMap;
    char **rangeMap;
    int holeMapX, holeMapY;

public:
    emberMap();
    ~emberMap();

    void init();
    void destory();

    char** getMap();
    void setPosOnMap( int x, int y, int val );

    void readMapFromFile( const char *filename );
    void saveMapIntoFile( const char *filename );
};

#endif // EMBER_MAP
