//
//	turnTable
//
//	2014.07.27
//
//	by pinkbeen
//
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
using std::endl;
using std::cout;

int g_blockOffsetX = 0;
int g_blockOffsetY = 0;
int g_prevBlockOffsetX = 0;
int g_prevBlockOffsetY = 0;

HANDLE g_hConsoleOutput = GetStdHandle( STD_OUTPUT_HANDLE );
bool haveData[ MAX_NUM ] = {false};

void gotoXY( int x, int y )
{
	COORD pos = { 2*x, y };

	SetConsoleCursorPosition( g_hConsoleOutput, pos );
}

void resetCheckTable()
{
	for ( int i = 0; i < MAX_NUM; ++i )
	{
		haveData[i] = false;
	}
}

//
//		□ □ □ □ □ □ □
//		□           □
//		□           □
//		□           □
//		□           □
//		□           □
//		□ □ □ □ □ □ □
//
void outputTurnTable()
{
	int prevRC = 0;
	int randColor = 0;

	for( int h = 0; h < MAX_HEIGHT; ++h )
	{
		for( int w = 0; w < MAX_WIDTH; ++w )
		{
			if( w == 0 || w == MAX_WIDTH - 1 ||
				h == 0 || h == MAX_HEIGHT - 1 )
			{
				// 相邻的两个颜色不可以相同
				do 
				{
					randColor = random( 1, h+w+1 );
				} while ( randColor == prevRC );
				prevRC = randColor;
				
				SetConsoleTextAttribute( g_hConsoleOutput, 0x17 );
			}
			else
			{
				SetConsoleTextAttribute( g_hConsoleOutput, 0x07 );
			}
			cout << "  ";
		}
		cout << endl;
	}

	SetConsoleTextAttribute( g_hConsoleOutput, 0x07 );
}

void moveBlock()
{	
	g_prevBlockOffsetX = g_blockOffsetX;
	g_prevBlockOffsetY = g_blockOffsetY;

	// 只有被改变了的坐标数才需要被记录
	if( g_blockOffsetY == 0 && g_blockOffsetX != MAX_WIDTH - 1 )
	{
		g_blockOffsetX += 1;
	}
	else
	if( g_blockOffsetX == MAX_WIDTH - 1 && g_blockOffsetY != MAX_HEIGHT - 1 )
	{
		g_blockOffsetY += 1;
	}
	else
	if( g_blockOffsetY == MAX_HEIGHT - 1 && g_blockOffsetX != 0 )
	{
		g_blockOffsetX -= 1;
	}
	else
	{
		g_blockOffsetY -= 1;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	srand( (unsigned int)time( NULL ) );
	outputTurnTable();

	CONSOLE_CURSOR_INFO cci = { false, NULL };
	SetConsoleCursorInfo( g_hConsoleOutput, &cci );
	
	int prevTime = GetTickCount();
	unsigned int maxTime = (unsigned int )random( 1000, 2000 );

	resetCheckTable();

	int i = 0;
	while ( 1 /* GetTickCount() - prevTime < maxTime */ )
	{
		Sleep( 100 );

		moveBlock();

		SetConsoleTextAttribute( g_hConsoleOutput, 0x17 );
		gotoXY( g_prevBlockOffsetX, g_prevBlockOffsetY );
		cout << "  ";

		SetConsoleTextAttribute( g_hConsoleOutput, 0xc7 );
		gotoXY( g_blockOffsetX, g_blockOffsetY );
		cout <<  "  ";


		if( GetTickCount() - prevTime > maxTime )
		{
			// 不可以有重复
			int num = random( MIN_NUM, MAX_NUM );
			while( haveData[num] )
			{
				num = random( MIN_NUM, MAX_NUM );
			}
			haveData[num] = true;

			SetConsoleTextAttribute( g_hConsoleOutput, 0x07 );
			gotoXY( i, MAX_HEIGHT + 2 );
			cout << num;

			prevTime = GetTickCount();
			i += 2;
		}

		if( i == 2*7 )
		{
			break;
		}
	}

	gotoXY( 0, MAX_HEIGHT + 4 );
	return 0;
}