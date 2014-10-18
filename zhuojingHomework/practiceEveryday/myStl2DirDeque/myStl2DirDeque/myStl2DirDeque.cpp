// myStl2DirDeque.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myStl2DirDeque.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myStl2DirDeque<int> ms2dd;

	for ( int i=0; i<10; ++i )
	{
		ms2dd.push_back(i);
	}

	for ( int j=10; j<20; ++j )
	{
		ms2dd.push_front(j);
	}

	for ( myStl2DirDeque<int>::iterator iter = ms2dd.begin();
		iter != ms2dd.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );
// 	for ( size_t i=0; i<ms2dd.size(); ++i )
// 	{
// 		printf( "%d ", ms2dd.at(i) );
// 	}

	for ( int i=0; i<10; ++i )
	{
		ms2dd.pop_front();
	}

	for ( int j=10; j<20; ++j )
	{
		ms2dd.pop_back();
	}

	return 0;
}

