// vector2-prac819.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

#define ANGLE 3.141592f/180.0f

int main( void )
{
	vector2 v1,v2(1.0f,2.0f),v3(3.0f, 4.0f);

	printf("\n\n\n\n" );

	v1.operator =( v2+v3 );
	printf( "\n" );
	vector2 v4( v2.operator +(v3) );

	return 0;
}