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

	printf( "%f\n",v2.Length() );
	printf( "%f\n",v3.Length() );

	cout << v3-v2 << endl;
	cout << v3+v2 << endl;

	cout << v3*v2 << endl;
	cout << v2*5 << endl;
	cout << 5*v2 << endl;

	cout << v2.normal() << endl;
	cout << v2.rotation( ANGLE*90.0f ) << endl;
	cout << v2.rotationself( ANGLE*90.0f ) << endl;

	return 0;
}