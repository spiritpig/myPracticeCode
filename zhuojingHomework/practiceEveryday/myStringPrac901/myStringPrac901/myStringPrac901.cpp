// myStringPrac901.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>

int _tmain(int argc, _TCHAR* argv[])
{
	myString ms1,
		ms2( "nishadsodhosa" ),
		ms3( ms2 ),
		ms4( 'a', 20 );


	printf( "%s\n", ms1.getStr() );
	printf( "%s\n", ms2.getStr() );
	printf( "%s\n", ms3.getStr() );
	printf( "%s\n", ms4.getStr() );

	ms4 = ms2;
	printf( "%s\n", ms4.getStr() );
	ms4 = "someoneStr";
	printf( "%s\n", ms4.getStr() );
	printf( "%s\n", (ms2+"kengdiedelingdao").getStr() );

	return 0;
}

