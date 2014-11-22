// myStlMap141023.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "myStlMap.h"
#include <map>

int _tmain(int argc, _TCHAR* argv[])
{
	myStlMap<int, int, std::less<int> > msm, msm2;

	msm.insert( myStlMap<int, int, std::less<int> >::value_type( 1, 234 ) );
	msm.insert( myStlMap<int, int, std::less<int> >::value_type( 12323231, 2324 ) );
	msm.insert( myStlMap<int, int, std::less<int> >::value_type( -2323231, 23244 ) );
	msm.insert( myStlMap<int, int, std::less<int> >::value_type( -1, 23244 ) );
	msm.insert( myStlMap<int, int, std::less<int> >::value_type( -2323231, 23223234 ) );

	msm2.insert( myStlMap<int, int, std::less<int> >::value_type( 123456, 23244 ) );
	msm2.insert( myStlMap<int, int, std::less<int> >::value_type( 98765, 23223234 ) );

	myStlMap<int, int, std::less<int> >::iterator iter = msm.begin();
	for ( iter; iter != msm.end(); ++iter )
	{
		printf( "%d %d\n", iter->key, iter->val );
	}
	printf( "\n" );

// 
// 	while ( !msm.empty() )
// 	{
// 		msm.erase( msm.end() );
// 	}

	msm.swap( msm2 );

	// 输出map的元素值，以确定成功。
	iter = msm.begin();
	for ( iter; iter != msm.end(); ++iter )
	{
		printf( "%d %d\n", iter->key, iter->val );
	}
	printf( "\n" );

	return 0;
}

