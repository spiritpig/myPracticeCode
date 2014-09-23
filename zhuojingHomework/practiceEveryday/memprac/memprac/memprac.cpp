// memprac.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


void* mymemcpy(void * const dest,void const* const src,size_t count)
{

	if ((dest==NULL)||(src==NULL)||(dest==src))
	{
		return dest;
	}
    else
	{
		char * const Pdest=(char * const) dest;
		char const * const Psrc=(char const * const)src;

		if (dest>src)
		{
			for (int i=count-1;i>-1;--i)
			{
				Pdest[i]=Psrc[i];
			}
		}
		else
		{
			for (size_t i=0;i<count;++i)
			{
				Pdest[i]=Psrc[i];
			}
		}
	}

	return dest;
}
int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}

