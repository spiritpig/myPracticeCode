// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
// Windows 头文件:
#include <windows.h>
// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

enum CALC_STATE
{
	CS_INIT,
	CS_LEFT,
	CS_RIGHT,
	CS_OPERATOR,
	CS_EQUAL
};

enum CALC_OPERATOR
{
	COP_ADD,
	COP_SUB,
	COP_MUL,
	COP_DIV
};

// TODO: 在此处引用程序要求的附加头文件
#include <stdio.h>