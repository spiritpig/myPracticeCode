// stdafx.cpp : 只包括标准包含文件的源文件
// Boxman.pch 将成为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
//引用任何所需的附加头文件，而不是在此文件中引用

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
