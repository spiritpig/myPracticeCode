// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once


#include <iostream>
#include <tchar.h>

#define BOARD_CEL 15
#define BOARD_ROW 15

enum MAP_STATUS
{
	MS_SPACE,
	MS_BORDER,
	MS_BLACKCHESS,
	MS_WHITECHESS
};

struct Point
{
	int x;
	int y;
};

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
#include "chessBoard.h"
