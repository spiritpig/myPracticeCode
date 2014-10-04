// myVector6.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myVectorClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int arrayM[] = { 1,2,3,4,5,6,7,8,9,10 };
	myVector<int> mveci( arrayM, &arrayM[10] );

	for ( myVector<int>::iterator iter = mveci.begin(); 
		  iter != mveci.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	mveci.insert( mveci.end(), arrayM, &arrayM[10] );
	for ( myVector<int>::iterator iter = mveci.begin(); 
		iter != mveci.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	return 0;
}

