// myStlString.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include "myBaseString.h"
using std::string;

int _tmain(int argc, _TCHAR* argv[])
{
	string ms = "nihaowomen������һ��������",
			 ms2 = "nihaowomen",
			 ms3 = "������һ��������";

	printf( "ms: %s\n", ms.c_str() );
	printf( "ms2: %s\n", ms2.c_str() );
	printf( "ms3: %s\n", ms3.c_str() );

	printf( "ms comp ms2 %d\n", ms2.compare( ms3 ) );

	ms = ms2 + ms3;
	printf( "ms: %s\n", ms.c_str() );
	printf( "ms comp ms2 %d\n", ms.compare( ms2 ) );

	return 0;
}

