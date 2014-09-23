// firstConsoleCpp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////
//
//	常量定义区
//
//////////////////////////////////////////////////////////////////////////
const int CHESSBOARD_WIDTH = 5;
const int CHESSBOARD_HEIGHT = 5;

const char XHAND = 'X';
const char QHAND = 'Q';
const char WALL  = '-';
const char SPACE = ' ';;


const int QHAND_COLOR  = 0xf1;
const int XHAND_COLOR  = 0xf2;
const int WALL_COLOR   = 0xf0;
const int NORMAL_COLOR = 0xf0;
const int START_COLOR  = 0x07;

#define XHAND_STR "○"
#define QHAND_STR "△"
#define WALL_STR  "▇"
#define SPACE_STR "  "

//////////////////////////////////////////////////////////////////////////
//
//	变量定义区
//
//////////////////////////////////////////////////////////////////////////
HANDLE g_hConsoleOutput = GetStdHandle( STD_OUTPUT_HANDLE );

char chessBoard[CHESSBOARD_HEIGHT][CHESSBOARD_WIDTH+1] = 
{ 
	"-----",
	"-   -",
	"-   -",
	"-   -",
	"-----"
};


//////////////////////////////////////////////////////////////////////////
//
//	函数定义区
//
//////////////////////////////////////////////////////////////////////////

// 移动控制台光标到x*2,y的位置
void gotoXY_width( int x, int y )
{
	COORD pos = { x*2, y };
	SetConsoleCursorPosition( g_hConsoleOutput, pos );
}
// 检测输入点是否是有效点
bool isPointValid( const POINT &pos )
{
	if( pos.x < 0 || pos.x >= CHESSBOARD_WIDTH  ||
		pos.y < 0 || pos.y >= CHESSBOARD_HEIGHT ||
		chessBoard[pos.y][pos.x] != SPACE )
	{
		return false;
	}
	else
	{
		return true;
	}
}

// 清空控制台的输入缓冲区
void clearInputCache()
{
	while( getchar() != '\n' );
}



// 检测当前的棋子是否赢了
bool isWin( const char chess  )
{
	// 水平的三行
	int numHorLineOne = 0,
		numHorLineTwo = 0,
		numHorLineThree = 0;

	for( int i = 1; i <= 3; ++i )
	{
		if( chessBoard[1][i] == chess )
		{
			numHorLineOne++;
		}

		if( chessBoard[2][i] == chess )
		{
			numHorLineTwo++;
		}

		if( chessBoard[3][i] == chess )
		{
			numHorLineThree++;
		}
	}
	// 赢了就返回了
	if( numHorLineOne == 3 ||
		numHorLineTwo == 3 ||
		numHorLineThree == 3 ) 
	{
		return true;
	}

	// 垂直的三行
	int numVertiLineOne = 0,
		numVertiLineTwo = 0,
		numVertiLineThree = 0;

	for( int i = 1; i <= 3; ++i )
	{
		if( chessBoard[i][1] == chess )
		{
			numVertiLineOne++;
		}

		if( chessBoard[i][2] == chess )
		{
			numVertiLineTwo++;
		}

		if( chessBoard[i][3] == chess )
		{
			numVertiLineThree++;
		}
	}

	// 赢了就返回了
	if( numVertiLineOne == 3 ||
		numVertiLineTwo == 3 ||
		numVertiLineThree == 3 ) 
	{
		return true;
	}

	// 斜线的情况
	if( chessBoard[1][1] == chess &&
		chessBoard[2][2] == chess &&
		chessBoard[3][3] == chess )
	{
		return true;
	}
	if( chessBoard[3][1] == chess &&
		chessBoard[2][2] == chess &&
		chessBoard[1][3] == chess )
	{
		return true;
	}

	return false;
}

// 输出棋盘
void outputChessBoard()
{
	for ( int i = 0; i < CHESSBOARD_HEIGHT; ++i )
	{
		for( int j = 0; j < CHESSBOARD_WIDTH; ++j )
		{
			if( chessBoard[i][j] ==  WALL )
			{
				SetConsoleTextAttribute( g_hConsoleOutput, WALL_COLOR );
				cout <<  WALL_STR;
			}
			else
			if( chessBoard[i][j] == SPACE )
			{
				cout << SPACE_STR;
			}
			else
			if( chessBoard[i][j] == XHAND )
			{
				SetConsoleTextAttribute( g_hConsoleOutput, XHAND_COLOR );
				cout << XHAND_STR;
			}
			else
			{
				SetConsoleTextAttribute( g_hConsoleOutput, QHAND_COLOR );
				cout << QHAND_STR;
			}
		}
		cout << endl;
	}
}

// 专门用于接收用户输入的棋子位置
void inputHand( POINT &pos, const char *player )
{
	cout <<  "轮到" << player << ",请输入棋子坐标： ";
	scanf( "%d%d", &pos.x, &pos.y );
	cout << endl;

	while( !isPointValid( pos ) )
	{
		clearInputCache();
		cout << "坐标有误，请重新输入：";
		scanf( "%d%d", &pos.x, &pos.y );
		cout << endl;
	}
}

void startGame( bool isAI )
{
	POINT pos[2] = { { -1, -1 }, { -1, -1 } };

	if( isAI )
	{
		cout << "未完成" << endl;
		return;
	}

	// 先画一次棋盘
	// 重置背景和字体颜色
	SetConsoleTextAttribute( g_hConsoleOutput, NORMAL_COLOR );
	system( "cls" );
	outputChessBoard();

	int i = 0;
	char playerName[10] = "player";
	char curHand = XHAND;
	do 
	{
		sprintf( playerName, "player%d", i+1 );
		inputHand( pos[i], playerName );

		// 根据下标选择当前的hand
		if( i == 0 )
		{
			curHand = XHAND;
		}
		else
		{
			curHand = QHAND;
		}

		chessBoard[pos[i].y][pos[i].x] = curHand;
		++i;
		i%=2;

		system( "cls" );
		outputChessBoard();
	} 
	while ( !isWin( curHand ) );

	printf( "\n%s赢了\n", playerName );
	system( "pause" );

}

//
// 游戏的主菜单，目前有三个功能
// 1 人人对战
// 2 人机对战（未完成）
// 3 结束游戏
//
void tictactoeGameMenu()
{
	while( 1 )
	{
		system( "cls" );
		outputHeader( "井字棋游戏" );
		cout <<  "输入对应数字键,执行相应的功能" << endl;
		cout <<  "1. 人人对战"				<< endl;
		cout <<  "2. 人机游戏（未完成）"	<< endl;
		cout <<  "3. 退出游戏"				<< endl;

		int n = -1;
		scanf( "%d", &n );
		clearInputCache();

		while ( n < 1 && n > 3 )
		{
			cout << "无效值，请重新输入。" ;
			scanf( "%d", &n );
		}
	 
		switch( n )  
		{
		case 1:
			{
				startGame( false );
				SetConsoleTextAttribute( g_hConsoleOutput, START_COLOR );
			}
			break;

		case 2:
			{
				startGame( true );
				SetConsoleTextAttribute( g_hConsoleOutput, START_COLOR );
			}
			break;

		case 3:
			{
				system( "cls" );
				cout << "退出游戏！" << endl;
				return;
			}
			break;
		}
	}
}




//////////////////////////////////////////////////////////////////////////
//
//		程序入口点
//
//////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	tictactoeGameMenu();

	return 0;
}