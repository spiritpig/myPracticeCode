// firstConsoleCpp.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// ����ǰ��׼��
	myMap.draw();
	mySnake.firstDraw();
	myFood.genRandomFood( mySnake.getHead() );
	myFood.draw();

	// ��Ϸ��ʼ
	char dir = ' ';
	bool isPause = false;
	bool isWin = false;
	while( !isWin )
	{	
		// ��ⰴ���Ƿ���
		if( kbhit() )
		{
			dir = getch();
			// ������ͣ����
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
			
				printf( "������!\n" );
				printf( "���ķ���Ϊ: %d\n", score );
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
		printf( "��ϲ��Ӯ��!\n" );
	} 
	
	return 0;
}