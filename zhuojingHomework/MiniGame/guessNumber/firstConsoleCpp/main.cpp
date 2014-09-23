//////////////////////////////////////////////////////////////////////////
//
//	猜数小游戏
//	by pinkbeen
//  2014.7.21
//
//////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <cstring>
#include <cctype>
#include <ctime>



//////////////////////////////////////////////////////////////////////////
//
//	常量区
//
//////////////////////////////////////////////////////////////////////////
#define QUESTION_MAX_NUM 4
#define ANSWER_MAX_NUM   8
// 分数对照表
#define RIGHTANSWER_ONCE			20		// 使用一次答对问题，一下以此类推
#define RIGHTANSWER_TWICE			14
#define RIGHTANSWER_THIRD			10
#define RIGHTANSWER_FOUTH			7
#define RIGHTANSWER_FIFTH_OR_MORE	5		// 使用了5次或者更多次完成答题



//////////////////////////////////////////////////////////////////////////
//
//	函数定义区
//
//////////////////////////////////////////////////////////////////////////
bool haveDuplicateNum( int a, int b, int c )
{
	if( a == b || 
		b == c ||
		a == c )
	{
		return true;
	}
	return false;
}

void addScore( int *score, int time )
{
	switch( time )
	{
	case 1:
		{
			*score += RIGHTANSWER_ONCE;
		}
		break;

	case 2:
		{
			*score += RIGHTANSWER_TWICE;
		}
		break;

	case 3:
		{
			*score += RIGHTANSWER_THIRD;
		}
		break;

	case 4:
		{
			*score += RIGHTANSWER_FOUTH;
		}
		break;

	case 5: case 6: 
	case 7: case 8:
		{
			*score += RIGHTANSWER_FIFTH_OR_MORE;
		}
		break;
	}

}

//////////////////////////////////////////////////////////////////////////
//
// 游戏名： 猜数游戏
//   描述： 顾名思义，我们给出数字让用户猜是什么。
//			用户会有若干次机会进行猜测。
//			同时，程序会给出提示，告诉用户对了几个位置,
//			对了几个数字。
//
//////////////////////////////////////////////////////////////////////////
void guessNumberGame()
{
	int score = 0;
	int qArr[3] = {0};
	int aArr[3] = {0};
	char temp[100] = " ";

	srand( (unsigned)time(NULL) );

	for( int qNum = 0; qNum < QUESTION_MAX_NUM; ++qNum)
	{
		qArr[0] = random( 0, 10 );
		qArr[1] = random( 0, 10 );
		qArr[2] = random( 0, 10 );
		// 生成一个数字，不重复
		while ( qArr[1] == qArr[0] )
		{
			qArr[1] = random( 0, 10 );
		} 
		while ( qArr[2] == qArr[1] || qArr[2] == qArr[0] ) 
		{
			qArr[2] = random( 0, 10 );
		}

		// 不和谐的作弊
		//printf( "原数为：%d%d%d\n", qArr[0], qArr[1], qArr[2] );

		// 允许用户输入尝试一定次数
		for( int aNum = 0; aNum < ANSWER_MAX_NUM; ++aNum )
		{
			// 输入一个数字，不重复
			while( true )
			{
				// 清空多余的字符
				printf( "请输入一个三位数（百位可以为0）\n" );
				scanf( "%s", temp );
				while ( getchar() != '\n' );

				// 当用户输入了过长或者非数字字符时，重新输入
				if( strlen( temp ) > 3 || 
					!isdigit( temp[0] ) || 
					!isdigit( temp[1] ) || 
					!isdigit( temp[2] ) )
				{
					printf( "输入不符合要求，请重新输入\n" );
				}
				else
				{
					aArr[0] = temp[0] - '0';
					aArr[1] = temp[1] - '0';
					aArr[2] = temp[2] - '0';

					if( haveDuplicateNum( aArr[0], aArr[1], aArr[2] ) )
					{
						printf( "有重复数字，请重新输入!\n" );
					}
					else
					{
						break;
					}
				}
			}
			
			// 测试位置的正确数
			int posRightNum = 0;
			for( int i = 0; i < 3; ++i )
			{
				if( qArr[i] == aArr[i] )
				{
					posRightNum++;
				}
			}

			// 回答正确了，进行下一轮的猜数
			if( posRightNum == 3 )
			{
				addScore( &score, aNum+1 );
				printf( "恭喜你答对了，当前的分为%d，少年继续前进吧！", score );

				system( "pause" );
				system( "cls" );
				break;
			}

			// 测试数字的正确数
			int numRightNum = 0;
			for( int i = 0; i < 3; ++i )
			{
				for( int j = 0; j < 3; ++j )
				{
					// 匹配则直接跳出去了
					if( qArr[i] == aArr[j] )
					{
						numRightNum++;
						break;
					}
				}
			}

			printf( "当前第%d题，第%d次猜数，位置的正确数是：%d\n", qNum+1, aNum+1, posRightNum );
			printf( "当前第%d题，第%d次猜数，数字的正确数是：%d\n\n", qNum+1, aNum+1, numRightNum );
		}

		if( aNum >= QUESTION_MAX_NUM )
		{
			printf( "答错了，不要气馁!\n" );
			getchar();
			system( "cls" );
		}
	}
	// 汇报结果
	system( "cls" );
	printf( "本次答题你共获得%d分!\n", score );
}

int _tmain(int argc, _TCHAR* argv[])
{
	guessNumberGame();	

	return 0;
}