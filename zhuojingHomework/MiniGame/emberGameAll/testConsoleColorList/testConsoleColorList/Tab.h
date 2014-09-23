#ifndef TAB
#define TAB

class Tab
{
	int curListPos, prevListPos;
	char contentList[3][10];
	HANDLE hConsoleOutput;
	int startX, startY;

	void gotoXY( int x, int y )
	{
		COORD pos = { x,y };
		SetConsoleCursorPosition( hConsoleOutput, pos );
	}


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
	void moveListPos();
};

#endif // TAB end