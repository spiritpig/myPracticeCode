#include "commonHeader.h"
using namespace std;

Tab::Tab( const int &x, const int &y,
		  const HANDLE &hConsole )
	: curListPos(0), prevListPos(0),
	  hConsoleOutput( hConsole ),
	  startX( x ), startY( y )
{
	strcpy( contentList[0], "�� ��" );
	strcpy( contentList[1], "�� ��" );
	strcpy( contentList[2], "�� ��" );

	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // �����Ϣ
	SetConsoleCursorInfo( hConsoleOutput, &cursorInfo );  // ���ù������
}
//----------------------------------------------------------------------------
void Tab::outputList( bool isVertical /*= true*/, 
					  int offset /*= 1 */ )
{
	if( isVertical )
	{
		offset = 1;
	}

	// �ƶ���ָ����λ��
	gotoxy( startX, startY );

	int offsetI = 0;
	for( int i = 0; i < 3; ++i )
	{

		// ���ǰ���Ŀհ�
		offsetI = 0;
		SetConsoleTextAttribute( hConsoleOutput, 0x07 );
		while( offsetI < offset )
		{
			cout << ' ';
			offsetI++;
		}

		// ���ѡ�������
		if( i == curListPos )
		{
			SetConsoleTextAttribute( hConsoleOutput, 0xA0 );
			cout << contentList[i];
		}
		else
		{
			SetConsoleTextAttribute( hConsoleOutput, 0x07 );
			cout << contentList[i];
		}

		// ֻ�д�ֱ����б��ʱ�򣬲Ż���
		if( isVertical )
		{
			cout << endl;
			gotoxy( startX, startY+i+1 );
		}
	}
}
//----------------------------------------------------------------------------
void Tab::updateList( bool isVertical /*= true*/, const int offset /*= 1 */ )
{
	//  ����Ҫˢ��ʱ��ֱ�ӷ���
	if( prevListPos == curListPos )
	{
		return;
	}

	int x = startX,y = startY,
		prevX = startX, prevY = startY;
	// ��������ֵ
	if( isVertical )
	{
		y = curListPos;
		prevY = prevListPos;

		x = 1;
		prevX = 1;
	}
	else
	{
		x = curListPos * ( int )strlen( contentList[0] ) 
			+ (curListPos + 1) * offset + startX;
		prevX = prevListPos * ( int )strlen( contentList[0] ) 
			+ (prevListPos + 1) * offset + startX;
	}

	gotoxy( x, y);
	SetConsoleTextAttribute( hConsoleOutput, 0xA0 );
	cout << contentList[ curListPos ];

	gotoxy( prevX, prevY);
	SetConsoleTextAttribute( hConsoleOutput, 0x07 );
	cout << contentList[ prevListPos ];

	return;
}
//----------------------------------------------------------------------------
int Tab::moveListPos()
{
	prevListPos = curListPos;
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
			curListPos--;
		}
		break;

	case 'S': case 's': 
		{
			curListPos++;
		}
		break;

	case '\r':
		{
			return curListPos;
		}
		break;
	}

	// �±�ֵҪ������ָ����Χ
	if( curListPos < 0 )
	{ 
		curListPos = 0;
	}
	else
	if( curListPos >= 3 )
	{
		curListPos = 2;
	}

	return -1;
}