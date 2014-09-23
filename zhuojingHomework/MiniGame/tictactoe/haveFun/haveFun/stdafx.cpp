// stdafx.cpp : 只包括标准包含文件的源文件
// firstConsoleCpp.pch 将成为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

void outputHeader( char *name )
{
	printf( " -----------------------------------------------------------------------------\n" );
	printf( "!                                                                   \n" );
	printf( "!                           %s                        \n",name );
	printf( "!                                                                   \n" );
	printf( " -----------------------------------------------------------------------------\n" );
}

// TODO: 在 STDAFX.H 中
//引用任何所需的附加头文件，而不是在此文件中引用
