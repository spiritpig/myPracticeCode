// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// Boxman.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
//�����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������

void gotoXY( int x, int y )
{
	COORD pos = { x*2, y };
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), pos );
}

bool isPointEqual( const point &p1, const point &p2 )
{
	return (p1.x == p2.x) &&
		   (p1.y == p2.y);
}

bool isPointEqual( int p1X, int p1Y, int p2X, int p2Y )
{
	return (p1X == p2X) &&
		   (p1Y == p2Y);
}
