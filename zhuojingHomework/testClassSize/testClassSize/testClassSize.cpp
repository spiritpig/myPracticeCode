// testClassSize.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

class A
{
private:
	int x,y;
};

int _tmain(int argc, _TCHAR* argv[])
{
	A aObj;
	int myX;

	A bObj;
	int myY;

	A cObj,dObj;

	printf( "%d\n", sizeof( A ) );
	printf( "aObj: %p\n", &aObj );
	printf( "x: %p\n", &myX );

	printf( "bObj: %p\n", &bObj );
	printf( "y: %p\n", &myY );

	printf( "cObj: %p\n", &cObj );
	printf( "dObj: %p\n", &dObj );

	return 0;
}

