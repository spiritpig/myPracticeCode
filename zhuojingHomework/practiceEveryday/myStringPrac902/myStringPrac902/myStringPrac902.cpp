// myStringPrac902.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	myString ms1,
		ms2( "nihaowomen" ),
		ms3( ms2 ),
		ms4 = ms2;

	ms4 = ms1;
	ms3 = ms4;
	ms3 = "sdsdsdsd";

	ms1 = NULL;

	printf( "%s\n", ms1.getStr() );
	printf( "%s\n", ms2.getStr() );
	printf( "%s\n", ms3.getStr() );
	printf( "%s\n", ms4.getStr() );

	return 0;
}

