#ifndef MY_TAB
#define MY_TAB

#include "commonHeader.h"

class Tab
{
	int curListPos, prevListPos;
	char contentList[3][10];
	HANDLE hConsoleOutput;
	int startX, startY;

public:
	Tab( const int &x, const int &y, 
		 const HANDLE &hConsole );
	~Tab()
	{
	}

	void outputList( bool isVertical = true, 
					 int offset = 1 );
	void updateList( bool isVertical = true, 
					 const int offset = 1 );

	// 在按下回车时，返回当前选项卡的位置
	// 其他时候，返回-1
	int moveListPos();
};

#endif // MY_TAB end