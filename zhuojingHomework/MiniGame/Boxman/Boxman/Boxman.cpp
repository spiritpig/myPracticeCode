// Boxman.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CONSOLE_CURSOR_INFO cci  = { 0, false };
	SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &cci );

	bxManager bm;
	bm.gameLoop();
	return 0;
}

