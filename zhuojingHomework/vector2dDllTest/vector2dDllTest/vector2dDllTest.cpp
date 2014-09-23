// vector2dDllTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "vector2d.h"
#pragma comment( lib, "vector2dAll.lib" )
using std::cout;
using std::endl;

#define ANGLE 3.1415926f/180.0f

void outputExcp( const vector2d &left, 
				 const vector2d &right, 
				 const vector2d &res,
				 const char *op )
{
	outputVector2( left );
	printf( " %s ", op );
	outputVector2( right );
	printf( ": " );
	outputVector2( res );
	printf( "\n" );
}

void outputExcp( const vector2d &left, 
				 const vector2d &right, 
				 float res, const char *op )
{
	outputVector2( left );
	printf( " %s ", op );
	outputVector2( right );
	printf( ": " );
	printf( "%.2f \n" );
}

int _tmain(int argc, _TCHAR* argv[])
{
	vector2d v1, 
		v2( 1.0f, 2.0f ), 
		v3( 5.0f, 12.0f ), 
		v4( v3 );

	outputVector2( v4 );
	printf( "\n" );

	outputExcp( v4, v3, v4-v3, "-" );
	outputExcp( v4, v2, v4-v2, "-" );
	outputExcp( v4, v2, v4*v2, "*" );
	outputExcp( v3, v2, v1 = v3+v2, "=" );

	printf( "(%.2f,%.2f) * 5: ", v2.x, v2.y );
	outputVector2( v2*5 );
	printf( "\n" );

	printf( "5 * (%.2f,%.2f): ", v2.x, v2.y );
	outputVector2( 5*v2 );
	printf( "\n" );

	outputVector2( v1 );
	printf( " 的长度为: %.2f \n", 
		v1.x, v1.y, v1.length() );

	outputVector2( v1 );
	printf( " 旋转90度: " );
	outputVector2( v1.rotation( ANGLE * 90 ) );
	printf( "\n" );

	outputVector2( v1 );
	printf( " 旋转90度: " );
	outputVector2( v1.rotationSelf( ANGLE * 90 ) );
	printf( "\n" );

	outputVector2( v1 );
	printf( " 单位化: " );
	outputVector2( v1.normalized() );
	printf( "\n" );

	outputVector2( v1 );
	printf( " 单位化: " );
	outputVector2( v1.normalizedSelf() );
	printf( "\n" );

	outputExcp( v4, v3, v4 -= v3, "-=" );

	outputVector2( v4 );
	printf( " 单位化: " );
	outputVector2( v4.normalized() );
	printf( "\n" );

	outputVector2( v4 );
	printf( " 单位化: " );
	outputVector2( v4.normalizedSelf() );
	printf( "\n" );

	outputExcp( v2, v1, v2-=v1, "-=" );

	printf( " (%.2f,%.2f) * 3: ", v2.x, v2.y );
	outputVector2( (v2 *= 3) );
	printf( "\n" );

	outputExcp( v4, v1, v4=v1, "=" );

	return 0;
} 
