#include "stdafx.h"

#ifndef CURSOR_AFX
#define CURSOR_AFX

class cursor
{
public:
	cursor();

	void init( int x, int y );
	void update();
	void draw();

private:
	void _processInput();
	bool _isPointInvalid( int x, int y );

	char m_Dir;
	cursorState m_CState;
};

#endif // END CURSOR_AFX
