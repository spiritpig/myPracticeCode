// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <conio.h>

#define STR_SPACE	"  "
#define STR_CURSOR	"��"
#define MAP_ROW		20
#define MAP_CEL		20

struct Point
{
	int x, y;
};

struct cursorState
{
	Point pos;
	Point prevPos;
};

void gotoXY( int x, int y );
void hideConsoleCursor();

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
#include "cursor.h"