// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
//

#pragma once

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

const int CLOCK_WIDTH_TIMES = 5;

struct pos
{
	int x;
	int y;
};

int random( int min, int max );
void gotoxy( int x, int y );

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
