// myDeque2Dir.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <deque>
#include <Windows.h>
#include "myDeque2Dir.h"
#pragma comment( lib, "winmm.lib" )
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	myDeque2Dir<int> md2d;
	for ( int i=1; i<20; i+=2 )
	{
		md2d.push_front(i*2);
		md2d.push_back(i);
	}

	myDeque2Dir<int> md22d;
	for ( int i=40; i<80; i+=2 )
	{
		md22d.push_front(i*2);
		md22d.push_back(i);
	}

	md22d.assign( md2d.begin(), md2d.end() );

	size_t sz = md22d.size();
	myDeque2Dir<int>::iterator iter = md22d.begin();
	int n = 0;
	while( (iter+n) != md22d.end().pointer )
	{
		printf( "%d ", *(iter+n) );
		++n;
	}
	printf( "\n" );

	return 0;
}

//0.17144 debug      myDeque2Dir
//0.00906 release

//0.49016 debug	  deque
//0.01232 release

