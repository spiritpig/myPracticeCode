//
// 程序名: sameWithMe
//
//	by pinkbben
//
//	2014.7.26
//

#include "stdafx.h"

void outputHeader( char *name )
{
	printf( " -----------------------------------------------------------------------------\n" );
	printf( "!                                                                   \n" );
	printf( "!                           %s                        \n",name );
	printf( "!                                                                   \n" );
	printf( " -----------------------------------------------------------------------------\n" );
}


void sameWithMe()
{
	bool isEqual = true;
	int comNum = 0, plNum = 0;
	int score = 0, curMaxTime = MAX_TIME;
	newTimer myTimer( curMaxTime );

	outputHeader( "SameWithMe!" );
	printf( "每当电脑输出一个三位数时，玩家都需要在一定时间内输入相同的值！\n" );
	printf( "最后，当玩家输入错误时，计算总得分！\n" );

	// 暂停一下 
	system( "pause" );
	system( "cls" );
	myTimer.moveTimer();

	while( isEqual )	
	{
		comNum = random( 1000, 100 );

		printf( "%d\n",comNum );
		scanf( "%d",&plNum );
		
		// 在用户输入完成以后，计算花了多少时间
		// 超时判负
		if( myTimer.isOutOfTime() || plNum != comNum )
		{
			printf( "游戏结束！\n" );
			printf( "您的总分为:%d\n", score );

			system( "pause" );
			system( "cls" );
			break;
		}
		else
		{
			printf( "恭喜！ 下一轮即将开始\n" );

			system( "pause" );
			system( "cls" );

			// 重置计时器
			myTimer.moveTimer();
			curMaxTime -= ONE_TIME_OFFSET;
			myTimer.setMT( curMaxTime  );

			score += 10;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand( ( unsigned int )time(NULL) );
	sameWithMe();

	return 0;
}