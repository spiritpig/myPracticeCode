// myStlList1019.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myStlVector1019.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myStlVector<int> msv;

	for ( int i=0; i<14; ++i )
	{
		msv.push_back( i );
	}

	myStlVector<int>::iterator iter = msv.begin();
	for ( iter; iter != msv.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	return 0;
}

