#include "stdafx.h"

#ifndef CHESSBOARD_AFX
#define CHESSBOARD_AFX

class chessBoard
{
public:
	chessBoard(void);
	void init();
	void draw();
	void setChessOnMap( const Point &pos, char color );

private:
	char m_Board[BOARD_ROW][BOARD_CEL];
};

#endif // END CHESSBOARD_AFX