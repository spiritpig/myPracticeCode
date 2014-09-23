#include "commonHeader.h"
using namespace std;

Tab::Tab( const int &x, const int &y,
		  const HANDLE &hConsole )
	: curListPos(0), prevListPos(0),
	  hConsoleOutput( hConsole ),
	  startX( x ), startY( y )
{
	strcpy( contentList[0], "进 攻" );
	strcpy( contentList[1], "防 御" );
	strcpy( contentList[2], "逃 跑" );

	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // 光标信息
	SetConsoleCursorInfo( hConsoleOutput, &cursorInfo );  // 设置光标隐藏
}
//----------------------------------------------------------------------------
void Tab::outputList( bool isVertical /*= true*/, 
					  int offset /*= 1 */ )
{
	if( isVertical )
	{
		offset = 1;
	}

	// 移动到指定的位置
	gotoxy( startX, startY );

	int offsetI = 0;
	for( int i = 0; i < 3; ++i )
	{

		// 输出前导的空白
		offsetI = 0;
		SetConsoleTextAttribute( hConsoleOutput, 0x07 );
		while( offsetI < offset )
		{
			cout << ' ';
			offsetI++;
		}

		// 输出选项卡的内容
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

		// 只有垂直输出列表的时候，才换行
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
	//  不需要刷新时，直接返回
	if( prevListPos == curListPos )
	{
		return;
	}

	int x = startX,y = startY,
		prevX = startX, prevY = startY;
	// 设置坐标值
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

	// 检测按键
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

	// 下标值要限制在指定范围
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