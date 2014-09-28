// myVector3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myVector.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int array[] = { 1,2,3,4,5,6,7 };
	myVector<int> mvec( array, &array[7] );
	myVector<int> mvec2( mvec.rbegin(), mvec.rend() );
	
	myVector<int>::iterator miIter = mvec2.begin();
	for( miIter; miIter != mvec2.end(); ++miIter )
	{
		printf( "%d\n", *miIter );
	}

	return 0;
}

