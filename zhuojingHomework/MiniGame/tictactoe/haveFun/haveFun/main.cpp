// firstConsoleCpp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;

//////////////////////////////////////////////////////////////////////////
//
//	����������
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

#define XHAND_STR "��"
#define QHAND_STR "��"
#define WALL_STR  "�~"
#define SPACE_STR "  "

//////////////////////////////////////////////////////////////////////////
//
//	����������
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
//	����������
//
//////////////////////////////////////////////////////////////////////////

// �ƶ�����̨��굽x*2,y��λ��
void gotoXY_width( int x, int y )
{
	COORD pos = { x*2, y };
	SetConsoleCursorPosition( g_hConsoleOutput, pos );
}
// ���������Ƿ�����Ч��
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

// ��տ���̨�����뻺����
void clearInputCache()
{
	while( getchar() != '\n' );
}



// ��⵱ǰ�������Ƿ�Ӯ��
bool isWin( const char chess  )
{
	// ˮƽ������
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
	// Ӯ�˾ͷ�����
	if( numHorLineOne == 3 ||
		numHorLineTwo == 3 ||
		numHorLineThree == 3 ) 
	{
		return true;
	}

	// ��ֱ������
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

	// Ӯ�˾ͷ�����
	if( numVertiLineOne == 3 ||
		numVertiLineTwo == 3 ||
		numVertiLineThree == 3 ) 
	{
		return true;
	}

	// б�ߵ����
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

// �������
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

// ר�����ڽ����û����������λ��
void inputHand( POINT &pos, const char *player )
{
	cout <<  "�ֵ�" << player << ",�������������꣺ ";
	scanf( "%d%d", &pos.x, &pos.y );
	cout << endl;

	while( !isPointValid( pos ) )
	{
		clearInputCache();
		cout << "�����������������룺";
		scanf( "%d%d", &pos.x, &pos.y );
		cout << endl;
	}
}

void startGame( bool isAI )
{
	POINT pos[2] = { { -1, -1 }, { -1, -1 } };

	if( isAI )
	{
		cout << "δ���" << endl;
		return;
	}

	// �Ȼ�һ������
	// ���ñ�����������ɫ
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

		// �����±�ѡ��ǰ��hand
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

	printf( "\n%sӮ��\n", playerName );
	system( "pause" );

}

//
// ��Ϸ�����˵���Ŀǰ����������
// 1 ���˶�ս
// 2 �˻���ս��δ��ɣ�
// 3 ������Ϸ
//
void tictactoeGameMenu()
{
	while( 1 )
	{
		system( "cls" );
		outputHeader( "��������Ϸ" );
		cout <<  "�����Ӧ���ּ�,ִ����Ӧ�Ĺ���" << endl;
		cout <<  "1. ���˶�ս"				<< endl;
		cout <<  "2. �˻���Ϸ��δ��ɣ�"	<< endl;
		cout <<  "3. �˳���Ϸ"				<< endl;

		int n = -1;
		scanf( "%d", &n );
		clearInputCache();

		while ( n < 1 && n > 3 )
		{
			cout << "��Чֵ�����������롣" ;
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
				cout << "�˳���Ϸ��" << endl;
				return;
			}
			break;
		}
	}
}




//////////////////////////////////////////////////////////////////////////
//
//		������ڵ�
//
//////////////////////////////////////////////////////////////////////////
int _tmain(int argc, _TCHAR* argv[])
{
	tictactoeGameMenu();

	return 0;
}