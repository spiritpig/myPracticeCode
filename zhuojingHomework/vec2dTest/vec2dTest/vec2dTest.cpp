// vec2dTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "vector2d.h"
using namespace std;
#pragma comment( lib, "vector2d.lib" )

#define ANGLE 3.1415926f/180.0f

int _tmain(int argc, _TCHAR* argv[])
{
	vector2d v1, 
		v2( 1.0f, 2.0f ), 
		v3( 5.0f, 12.0f ), 
		v4( v3 );

	cout << v4 << endl;
	cout << v4 - v3 << endl;
	cout << v4 * v2 << endl;

	v1 = v3 + v2;
	cout << v1 << endl;
	cout << v2*5 << endl;
	cout << 5*v2 << endl;

	cout << v1.length() << endl;
	cout << v1.rotation( ANGLE * 90 ) << endl;
	cout << v1.rotationSelf( ANGLE * 90 ) << endl;
	cout << v1.normalized() << endl;
	cout << v1.normalizedSelf() << endl;

	cout << v4 << " - " << v3 << " = ";
	cout << (v4 -= v3) << endl;

	cout << v4.normalized() << endl;
	cout << v4.normalizedSelf() << endl;

	cout << v2 << " - " << v1 << " = ";
	cout << (v2 -= v1) << endl;

	cout << v2 << " * " << 3 << " = ";
	cout << (v2 *= 3) << endl;

	cout << v4 << " 给 " << v4 << " 赋值 = ";
	cout << (v1 = v4) << endl;

	return 0;
}

