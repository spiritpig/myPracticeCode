// myVector2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myVectorClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myVectorClass<int> v1;

	v1.push_back(0);
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(33);
	v1.push_back(423);
	v1.push_back(654);

	for ( myVectorClass<int>::iterator iter = v1.begin();
		iter != v1.end(); ++iter )
	{
		printf( "%d ", *iter );
	}
	printf( "\n" );

	return 0;
}

