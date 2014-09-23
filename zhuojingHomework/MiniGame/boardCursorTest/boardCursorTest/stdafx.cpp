// stdafx.cpp : 只包括标准包含文件的源文件
// boardCursorTest.pch 将成为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
//引用任何所需的附加头文件，而不是在此文件中引用
void gotoXY( int x, int y )
{
	COORD pos = { x*2, y };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
}

void hideConsoleCursor()
{
	CONSOLE_CURSOR_INFO cci = { 1, false };
	SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cci );
}
