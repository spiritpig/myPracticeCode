// myStlList1015.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>
#include "myStlList.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myStlList1015<int> msl1015;

	myStlList1015<int>::iterator mListIter;
	mListIter.nodePt = NULL;
	msl1015.insert( mListIter, 102323 );

	mListIter = msl1015.begin();
	msl1015.insert( mListIter, 2345 );

	mListIter.nodePt = NULL;
	for ( int i=0; i<10; ++i )
	{
		msl1015.insert( mListIter, i );
	}

	mListIter = msl1015.begin();
	for ( mListIter; mListIter != msl1015.end(); ++mListIter)
	{
		printf( "%d ", *mListIter );
	}
	printf( "\n" );

	return 0;
}

