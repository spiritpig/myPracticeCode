// firstConsoleCpp.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int score = 0;

	srand( (unsigned)time( NULL ) );
	snakeMap myMap;
	snake mySnake;
	food  myFood;
	
	CONSOLE_CURSOR_INFO cci = { 1, false };
	SetConsoleCursorInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &cci );

	// 运行前的准备
	myMap.draw();
	mySnake.firstDraw();
	myFood.genRandomFood( mySnake.getHead() );
	myFood.draw();

	// 游戏开始
	char dir = ' ';
	bool isPause = false;
	bool isWin = false;
	while( !isWin )
	{	
		// 检测按键是否按下
		if( kbhit() )
		{
			dir = getch();
			// 简易暂停功能
			if( dir == 'p' || dir == 'P' )
			{
				isPause = true;
			}
			else
			{
				if( dir == 'o' || dir == 'O' )
				{
					isPause = false;
				}
			}
		}

		if( !isPause )
		{
			mySnake.move( dir );

			if( mySnake.isHitWall() || mySnake.isHitSnake() )
			{
				changeTextColor( DEFAULT_TEXT_COLOR );
				system( "cls" );
			
				printf( "死掉了!\n" );
				printf( "您的分数为: %d\n", score );
				system( "pause" );
				break;
			}
			else
			if( mySnake.isHitFood( myFood.getFoodPos() ) )
			{
				mySnake.onEatFood();

				if( mySnake.getCurSnakeNodeNum() < MAX_SNAKE_NODE )
				{
					myFood.genRandomFood( mySnake.getHead() );
					myFood.draw();
				}
				else
				{
					isWin = true;
				}
				++score;
			}

			mySnake.draw();
		}
		Sleep( 100 );
	}

	if( isWin )
	{
		changeTextColor( DEFAULT_TEXT_COLOR );
		system( "cls" );
		printf( "恭喜你赢了!\n" );
	} 
	
	return 0;
}