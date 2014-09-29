// myVector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vld.h>
#include "myVectorClass.h"

int _tmain(int argc, _TCHAR* argv[])
{
	myVectorClass<int> mv1, mv2;

 	mv1.push_back(1);
 	mv1.push_back(2);
 	mv1.push_back(3);
	mv1.push_back(4);
	mv1.push_back(5);

	mv2.push_back(5);
	mv2.push_back(4);
	mv2.push_back(3);
	mv2.push_back(2);
	mv2.push_back(1);

	myswap( mv1, mv2 );
	mv1.resize( 11 );

	return 0;
}

