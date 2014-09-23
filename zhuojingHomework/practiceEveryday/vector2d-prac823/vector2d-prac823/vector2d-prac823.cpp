// vector2-prac819.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;

#define ANGLE 3.141592f/180.0f

int main( void )
{
	vector2 v1(3.0f, 4.0f),v2,v3;

	v2.x = 1.0f;
	v2.y = -1.0f;

	v3.x = 12.0f;
	v3.y = 5.0f;

	printf( "%f\n",v2.length() );
	printf( "%f\n",v3.length() );

	cout << v3-v2 << endl;
	cout << v3+v2 << endl;

	cout << v3*v2 << endl;
	cout << v2*5 << endl;
	cout << 5*v2 << endl;

	cout << v2.normalized() << endl;
	cout << v2.rotation( ANGLE*90.0f ) << endl;
	cout << v2.rotationSelf( ANGLE*90.0f ) << endl;

	vector2 v4( 0.0f, 0.0f );
	cout << v4.normalizedSelf() << endl;

	return 0;
}