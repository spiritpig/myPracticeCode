// stdafx.cpp : 只包括标准包含文件的源文件
// firstConsoleCpp.pch 将成为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// TODO: 在 STDAFX.H 中
//引用任何所需的附加头文件，而不是在此文件中引用

int random( int min, int max )
{
	return rand()%( max - min + 1 ) + min;
}

// 移动控制台光标
void gotoxy( int x, int y )
{
	COORD pos = { 2*x, y };
	SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), pos );
}
