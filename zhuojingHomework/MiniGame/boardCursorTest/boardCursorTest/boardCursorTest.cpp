// boardCursorTest.cpp : �������̨Ӧ�ó������ڵ㡣
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

