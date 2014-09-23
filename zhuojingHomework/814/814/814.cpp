// 814.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand( ( unsigned )time( NULL ) );
	miniManage mm;
	mm.gameLoop();

	return 0;
}