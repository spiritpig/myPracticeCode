// myStlString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include "myBaseString.h"
using std::string;

int _tmain(int argc, _TCHAR* argv[])
{
	string ms = "nihaowomen今天是一个好日子",
			 ms2 = "nihaowomen",
			 ms3 = "今天是一个好日子";

	printf( "ms: %s\n", ms.c_str() );
	printf( "ms2: %s\n", ms2.c_str() );
	printf( "ms3: %s\n", ms3.c_str() );

	printf( "ms comp ms2 %d\n", ms2.compare( ms3 ) );

	ms = ms2 + ms3;
	printf( "ms: %s\n", ms.c_str() );
	printf( "ms comp ms2 %d\n", ms.compare( ms2 ) );

	return 0;
}

