// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���ǳ��õ��������ĵ���Ŀ�ض��İ����ļ�
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

// TODO: �ڴ˴����ó���Ҫ��ĸ���ͷ�ļ�
#include "myString.h"