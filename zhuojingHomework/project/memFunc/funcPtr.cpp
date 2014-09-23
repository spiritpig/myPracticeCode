#include "stdafx.h"

typedef char* (*pCharFunc) ( char * const, const char * const );
//typedef int* (*pIntFunc)  ( int (*) ( int, int ), int, int );

typedef int* (*pIntFunc) ( int );
typedef pIntFunc (*pIntFunc) ( void )   ;




int main( void )
{
	//int (*huo) (float);
	//int (*p2d)[10];

	char a[100] = "sdsdsdsd";
	char b[20]  = "123456789";

	pCharFunc pcf = strcpy;
	pcf( a, b );

	printf( "%s\n", a );

	return 0;
}