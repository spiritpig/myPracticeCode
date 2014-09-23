// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#include <iostream>
#include <tchar.h>
#include <cstring>

#define SAFE_DELARR(p)	\
{						\
	if( p != NULL )		\
	{					\
		delete [] p;	\
		p = NULL;		\
	}					\
}

// TODO: 在此处引用程序要求的附加头文件
#include "myString.h"