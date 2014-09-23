/*
 * ember 公共头文件
 *
 */
#include <iostream>
#include <cstdio>
using std::endl;
using std::cout;

#ifndef COMMON_HEADER
#define COMMON_HEADER

// 地图尺寸
const int MAX_HEIGHT = 20;
const int MAX_WIDTH = 60;

void output2DArray( char **a, int h, int w );

#endif // COMMON_HEADER
