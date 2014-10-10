// myStlMap.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include "myStlMap.h"
using std::string;
using std::wstring;

int _tmain(int argc, _TCHAR* argv[])
{
	mystd::myStlMap<string, int, mystd::less<string> > myMap;

	myMap.insert( mystd::myStlMap<string, int, mystd::less<string> >::value_type( "张三", 802 ) );
	myMap.insert( mystd::myStlMap<string, int, mystd::less<string> >::value_type( "李四", 8202 ) );
	myMap.insert( mystd::myStlMap<string, int, mystd::less<string> >::value_type( "王五", 8402 ) );
	myMap.insert( mystd::myStlMap<string, int, mystd::less<string> >::value_type( "吭吭", 8602 ) );
	myMap.insert( mystd::myStlMap<string, int, mystd::less<string> >::value_type( "烧饼六", 8602 ) );

	mystd::myStlMap<string, int, mystd::less<string> >::iterator iter = myMap.begin();
	for ( iter; iter != myMap.end(); ++iter )
	{
		printf( "%s %d\n", iter->first.c_str(), iter->second );
	}

	return 0;
}
