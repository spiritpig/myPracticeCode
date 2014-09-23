//////////////////////////////////////////////////////////////////////////
//
//
//	 程序名：Rock-Paper-Scissors
//
//	 by pinkbeen 
//
//	 2014.7.25
// 
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <ctime>

// 手势宏定义
#define ROCK	"石头"
#define PAPER	"布"
#define SCISSOR	"剪刀"
#define ERROR	"ERROR"

// 常量定义
const int ROCK_ID = 1;
const int PAPER_ID = 2;
const int SCISSOR_ID = 3;
const int ERROR_ID = -1;

const int LEFT_WIN = 1;
const int RIGHT_WIN = -1;
const int DRAW = 0;

void outputHeader( const char *name )
{
	printf( " -----------------------------------------------------------------------------\n" );
	printf( "!                                                                   \n" );
	printf( "!                           %s                        \n",name );
	printf( "!                                                                   \n" );
	printf( " -----------------------------------------------------------------------------\n" );
}

void mapHandIdToHandStr( const int &handId )
{
	if( handId == ROCK_ID  )
	{
		printf( "%s ",ROCK );
	}
	else
	if( handId == PAPER_ID )
	{
		printf( "%s ",PAPER );
	}
	else
	if( handId == SCISSOR_ID )
	{
		printf( "%s ",SCISSOR );
	}
	else
	{
		printf( "%s ",ERROR );
	}
}

// 返回-1则hand2胜利
// 返回1则hand1胜利
// 返回0则平局
int calcRes( int hand1, int hand2 )
{
	if( hand1 == hand2 )
	{
		return DRAW;
	}
	else
	if( hand1 -hand2 == 1 ||
		hand1 - hand2 == -2 )
	{
		return LEFT_WIN;
	}
	else
	{
		return RIGHT_WIN;
	}
}

void rps()
{
	srand( ( unsigned int )time( NULL ) );

	outputHeader("剪刀石头布!");

	int comHandId = random( 4, 1 );
	int plHandId, res;
	printf( "请输入你的手势(石头1\\布2\\剪刀3): " );
	scanf( "%d", &plHandId );

	while( 1 )
	{
		printf( "\n" );
		printf( "玩家： " );
		mapHandIdToHandStr( plHandId );

		printf( " 电脑： " );
		mapHandIdToHandStr( comHandId );

		printf( "\n" );
		res = calcRes( plHandId, comHandId );

		if( res == DRAW )
		{
			printf( "\t打成平局\n" );
			printf( "请输入新的手势(石头1\\布2\\剪刀3): " );
			scanf( "%d", &plHandId );
			comHandId = random( 4, 1 );
		}
		else
		if( res == RIGHT_WIN )
		{
			printf( "\t电脑获胜!\n" );
			break;
		}
		else
		if( res == LEFT_WIN )
		{
			printf( "\t玩家获胜!\n" );
			break;
		}		
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	rps();		

	return 0;
}