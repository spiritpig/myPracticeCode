#include "stdafx.h"

#ifndef BXBOX_AFX
#define BXBOX_AFX

class bxBox
{
public:
	bxBox(void);
	void init( int x, int y );
	void update( MAPDATA md, const point &heroPos, char dir );
	void draw();

	const point & getPos()
	{
		return m_Pos;
	}

	const point & getPrevPos()
	{
		return m_PrevPos;
	}

private:
	void _processInput( MAPDATA md, const point &heroPos, char dir );

	point m_Pos, m_PrevPos;
};

#endif // END BOX_AFX