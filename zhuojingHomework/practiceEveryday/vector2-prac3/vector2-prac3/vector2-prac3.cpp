// vector2-prac3.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

#define ANGLE 3.1415926f/180.0f

int _tmain(int argc, _TCHAR* argv[])
{
	vector2d v1, v2( 2.0f, 3.0f ), v3( 12.0f, 5.0f );

	v1 = v2 + v3;
	cout << v1 << endl;

	v1 = v1 - v3;
	cout << v1 << endl;

	v1 = v2 * 3;
	cout << v1 << endl;

	cout << (v2 *= 3) << endl;
	cout << (v2 * v1) << endl;
	cout << (v1 += v3) << endl;
	cout << (v1 -= v3) << endl;

	cout << v1.length() << endl;
	cout << v1.normalized() << endl;
	cout << v3.rotation( ANGLE * 90.0f ) << endl;
	cout << v3.rotationSelf( ANGLE * 90.0f ) << endl;

	return 0;
}

