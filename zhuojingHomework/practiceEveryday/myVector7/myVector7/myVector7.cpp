// myVector7.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "vectorClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int array[] = { 1,2,3,4,5,6,7,8 };
	myVector<int> mv1( array, &array[8] );

	mv1.insert( mv1.begin()+4, array, &array[8] );

	myVector<int>::iterator iter = mv1.begin();
	for ( iter; iter != mv1.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	return 0;
}

