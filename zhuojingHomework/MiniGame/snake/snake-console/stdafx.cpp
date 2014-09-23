// stdafx.cpp : 只包括标准包含文件的源文件
// firstConsoleCpp.pch 将成为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
//引用任何所需的附加头文件，而不是在此文件中引用
int random( int min, int max )
{
	return rand()%(max - min + 1) + min;
}
void gotoXY( const int x, const int y )
{
	COORD pos = { x*2, y };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
}

void clearInputCache()
{
	int c;
	while( ( c = getchar() ) != '\n' && c != EOF );
}

void changeTextColor( int color )
{
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color );
}