// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <iostream>
#include <tchar.h>
#include <cmath>

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
#define ROW 10
#define CEL 10
typedef const char ( * const p2DArray )[CEL];

struct point
{
	int x;
	int y;
};

enum MAP_STATE{ MS_SPACE, MS_STONE=4, MS_WALKED, MS_START, MS_END };

#include "Vector2.h"
#include "Queue.h"
#include "pathFinder.h"