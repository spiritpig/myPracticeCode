/*
 * ember 公共头文件
 *
 */
#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstring>
using std::endl;
using std::cout;

#ifndef COMMON_HEADER
#define COMMON_HEADER

// 地图尺寸
const int MAP_DISPLAY_MAX_HEIGHT = 21;		// 地图显示区域的最大高度和最大宽度，这个值为奇数，是为了方便
const int MAP_DISPLAY_MAX_WIDTH = 41;		// 在去显示区域时，以中点准，左右区域都是偶数 比如 41 左右都是20
											// 算上中点刚好41

const int MAP_DISPLAY_RANGE_HALFWIDTH = MAP_DISPLAY_MAX_WIDTH/2;
const int MAP_DISPLAY_RANGE_HALFHEIGHT = MAP_DISPLAY_MAX_HEIGHT/2;

void output2DArray( char **a, int h, int w );

#endif // COMMON_HEADER
