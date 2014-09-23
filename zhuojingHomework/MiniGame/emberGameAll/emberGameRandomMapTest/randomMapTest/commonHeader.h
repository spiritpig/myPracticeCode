/*
 * 说明: ember 公共头文件
 *
 * 日期: 2014.7.17
 * 作者: pinkbeen
 *
 */
#include <iostream>
#include <Windows.h>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <conio.h>
using std::endl;
using std::cout;

#ifndef COMMON_HEADER
#define COMMON_HEADER

struct Point
{
	int x,y;
};

// 地图尺寸
const int MAP_HEIGHT	= 50;
const int MAP_WIDTH		= 200;

const int MAP_DISPLAY_MAX_HEIGHT	= 21;		// 地图显示区域的最大高度和最大宽度，这个值为奇数，是为了方便
const int MAP_DISPLAY_MAX_WIDTH		= 61;		// 在去显示区域时，以中点准，左右区域都是偶数 比如 41 左右都是20
											// 算上中点刚好41

const int MAP_DISPLAY_RANGE_HALFWIDTH = MAP_DISPLAY_MAX_WIDTH/2;
const int MAP_DISPLAY_RANGE_HALFHEIGHT = MAP_DISPLAY_MAX_HEIGHT/2;

const char GRASS			= 'G';
const char ROCK				= 'R';
const char MONSTER			= 'M';
const char HERO				= '@';
const char BORDER			= '*';
const char BUILDING			= 'B';
const char BUILDING_ROOM	= 'B';		// 代表建筑物的门，暂时，与BUILDING的符号相同

// 主角移动的各种情况映射表
const int CANNOT_MOVEABLE	= 0;
const int MOVEABLE			= 1;
const int HIT_ROOM			= 2;
const int HIT_MONSTER		= 3;

// 与 战斗画面有关的常量
const int TABNUM_ATTACK				= 0;
const int TABNUM_DEFENSE			= 1;
const int TABNUM_RUNAWAY			= 2;
const int FIGHTINFO_START_OFFSETX	= 24;
const int FIGHTINFO_START_OFFSETY	= 0;
const int FIGHTINFO_MAX_LINE		= 10;


#include "Tab.h"
#include "life.h"
#include "timer.h"
#include "player.h"
#include "monster.h"
#include "emberMap.h"
#include "emberManager.h"

/**
 *	  输出一个二维数组
 *
 *	  参数 
 *		  a  二级指针
 *		  h  数组高度
 *		  w  数组宽度
 *
 */
void output2DArray( const char **a, int h, int w);


/**
 *	  移动控制台光标到指定位置
 *
 *	  参数 
 *		  x   指定的横坐标
 *		  y   指定的纵坐标
 *
 */
void gotoxy( const int x, const int y );

/**
 *	  生成制定范围的随机数，范围是一个左闭右开区间
 *	  [ min, max )
 *
 *	  参数 
 *		  max	 范围的最大值
 *		  min	 范围的最小值
 *
 */
int random( const int max, const int min = 0 );

#endif // COMMON_HEADER
