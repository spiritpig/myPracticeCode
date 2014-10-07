// myStlString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myBaseString.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myString ms = "nihaowomen";

	printf( "%s\n", ms.c_Str() );
	ms.push_back( 's' );
	printf( "%s\n", ms.c_Str() );
	return 0;
}

