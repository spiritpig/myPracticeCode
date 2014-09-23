// caclRandomRatio.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <conio.h>
#include <Engine_Define.h>
#pragma comment(lib,"Sgge.lib")

#define ONE_TIME_MAX 10000000

int _tmain(int argc, _TCHAR* argv[])
{
	Sgge *pSgge = SggeCreate(SGGE_VERSION);

	__int64 total = 0;
	long long count[6]={0};
	while ( 1 )
	{
		char input;
		if( kbhit() )
		{
			input = getch();
			if( input == 'q' ||
				input == 'Q' )
			{
				system( "pause" );
				break;
			}
		}

		system( "cls" );
		for ( long long i=0; i<ONE_TIME_MAX; ++i )
		{
			++count[pSgge->GetRandomInt(0,5)];
		}
		total += ONE_TIME_MAX;

		for ( int i=0; i<6; ++i )
		{
			printf( "%d: %I64d\n", i, count[i] );
		}
	}

	system( "cls" );
	// 计算概率
	for ( int i=0; i<6; ++i )
	{
		printf( "%d: %f\n", i, count[i]/(double)total );
	}
	pSgge->Release();
	return 0;
}

