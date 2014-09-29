// myVector4.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myVector.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int array[] = { 1,2,3,4,5 };
	myVector<int> mvec( array, &array[5] );

	myVector<int>::iterator iter;
	for ( iter = mvec.begin(); iter != mvec.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	return 0;
}
