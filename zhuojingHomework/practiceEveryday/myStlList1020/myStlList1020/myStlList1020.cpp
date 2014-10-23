// myStlList1020.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>
#include "myStlList1020.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myStlList1020<int> msl;

	for ( int i=0; i<5; ++i )
	{
		msl.push_back( i );
		msl.insert( msl.end(), i*4 );
	}

	myStlList1020<int>::iterator iter = msl.begin();
	for ( iter; iter != msl.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	myStlList1020<int> msl2( msl );
	iter = msl2.begin();
	for ( iter; iter != msl2.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	msl.insert( ++msl.begin(), msl2.begin(), msl2.end() );
	iter = msl.begin();
	for ( iter; iter != msl.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	return 0;
}

