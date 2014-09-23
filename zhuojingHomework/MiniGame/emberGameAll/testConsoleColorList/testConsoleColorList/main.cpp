// firstConsoleCpp.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <conio.h>
using std::cout;
using std::endl;

// Ϊ�˷��㶨���˶��ȫ�ֱ���
HANDLE g_hConsoleOutput = GetStdHandle( STD_OUTPUT_HANDLE );
int g_CurListPos = 0;
int g_PrevListPos = 0;
bool g_isVertical = true;

void gotoXY( int x, int y )
{
	COORD pos = { x,y };
	SetConsoleCursorPosition( g_hConsoleOutput, pos );
}

char list[3][20] = {  "�� ʼ �� Ϸ",
				      "�� �� �� Ϸ",
					  "�� �� �� Ϸ"
					};

void outputList( bool isVertical = true, int offset = 1 )
{
	char endChar = ' ';
	if( isVertical )
	{
		endChar = '\n';
		offset = 1;
	}

	int offsetI = 0;
	for( int i = 0; i < 3; ++i )
	{
		offsetI = 0;
		SetConsoleTextAttribute( g_hConsoleOutput, 0x07 );
		while( offsetI < offset )
		{
			cout << ' ';
			offsetI++;
		}

		if( i == g_CurListPos )
		{
			SetConsoleTextAttribute( g_hConsoleOutput, 0xA0 );
			cout << list[i];
		}
		else
		{
			SetConsoleTextAttribute( g_hConsoleOutput, 0x07 );
			cout << list[i];
		}

		cout << endChar;
	}
}

void updateList( bool isVertical = true, int offset = 1 )
{
	//  ����Ҫˢ��ʱ��ֱ�ӷ���
	if( g_PrevListPos == g_CurListPos )
	{
		return;
	}

	int x = 0,y = 0,
		prevX = 0, prevY = 0;
	// ��������ֵ
	if( isVertical )
	{
		y = g_CurListPos;
		prevY = g_PrevListPos;

		x = 1;
		prevX = 1;
	}
	else
	{
		x = g_CurListPos * ( int )strlen( list[0] ) 
			+ (g_CurListPos + 1) * offset;
		prevX = g_PrevListPos * ( int )strlen( list[0] ) 
			+ (g_PrevListPos + 1) * offset;
	}

	gotoXY( x, y );
	SetConsoleTextAttribute( g_hConsoleOutput, 0xA0 );
	cout << list[ g_CurListPos ];

	gotoXY( prevX, prevY);
	SetConsoleTextAttribute( g_hConsoleOutput, 0x07 );
	cout << list[ g_PrevListPos ];

	return;
}

void moveListPos()
{
	g_PrevListPos = g_CurListPos;
	char dir = ' ';

	// ��ⰴ��
	if( kbhit() )
	{
		dir = getch();
	}

	switch( dir )
	{
	case 'W': case 'w': 
		{
			g_CurListPos--;
		}
		break;

	case 'S': case 's': 
		{
			g_CurListPos++;
		}
		break;
	}

	// �±�ֵҪ������ָ����Χ
	if( g_CurListPos < 0 )
	{ 
		g_CurListPos = 0;
	}
	else
	if( g_CurListPos >= 3 )
	{
	 	g_CurListPos = 2;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	int offset = 10;
	outputList( g_isVertical, offset );

	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // �����Ϣ
	SetConsoleCursorInfo(g_hConsoleOutput, &cursorInfo);  // ���ù������

	while( 1 )
	{
		moveListPos();
		updateList( g_isVertical, offset );
	}

	return 0;
}