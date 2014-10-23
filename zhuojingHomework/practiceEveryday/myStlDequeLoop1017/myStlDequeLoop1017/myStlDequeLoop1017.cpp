
// myStlDequeLoop1017.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myStlDequeLoop.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myStlDequeLoop<int> msdl;

	for ( int i=0; i<10; ++i )
	{
		msdl.push_back(i);
	}
	for ( int j=320; j<330; ++j )
	{
		msdl.insert( msdl.begin()+5, 16 );
		msdl.push_front(j);
	}

	myStlDequeLoop<int>::iterator iter = msdl.begin();
	for ( iter; iter != msdl.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	msdl.erase( msdl.begin() );
	iter = msdl.begin();
	for ( iter; iter != msdl.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

// 	for ( int i=0; i<20; ++i )
// 	{
// 		msdl.pop_back();
// 	}
// 	for ( int j=320; j<340; ++j )	
// 	{
// 		msdl.pop_front();
// 	}

	return 0;
}
