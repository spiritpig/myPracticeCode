#include "StdAfx.h"

chessBoard::chessBoard(void)
{
}

void chessBoard::init()
{
	for ( int i=0; i<BOARD_ROW; ++i )
	{
		for ( int j=0; j<BOARD_CEL; ++j )
		{
			if( i==0 || i==(BOARD_ROW-1) ||
				j==0 || j==(BOARD_CEL-1) )
			{
				m_Board[i][j] = ;
			}
		}
	}
}

