// boardCursorTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	hideConsoleCursor();

	cursor c;
	c.init( 5, 5 );

	while ( 1 )
	{
		Sleep( 100 );
		c.update();
		c.draw();
	}

	return 0;
}

