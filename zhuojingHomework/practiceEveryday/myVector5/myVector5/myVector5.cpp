// myVector5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myVectorClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myVector<int> a;

	for ( int i=0; i<10; ++i )
	{
		a.push_back( i );
	}

	myVector<int> b(a);

 	b.insert( b.begin()+4, a.begin()+3, a.begin() + a.size()-5 );
	for ( int i=0; i<b.size(); ++i )
	{
		printf( "%d ", b[i] );
	}
	printf( "\n" );

	return 0;
}

