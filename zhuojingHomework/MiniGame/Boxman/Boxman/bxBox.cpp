#include "StdAfx.h"

bxBox::bxBox()
{
	m_Pos.x = 0;
	m_Pos.y = 0;

	m_PrevPos.x = 0;
	m_PrevPos.y = 0;
}

void bxBox::init( int x, int y )
{
	m_Pos.x = x;
	m_Pos.y = y;
}

void bxBox::update( MAPDATA md, const point &heroPos, char dir )
{
	_processInput( md, heroPos, dir );
}

void bxBox::draw()
{
	gotoXY( m_Pos.x, m_Pos.y );
	printf( BOX_CHAR );
}

void bxBox::_processInput( MAPDATA md, const point &heroPos, char dir )
{
	// 只有被主角推到了才需要移动
	if( isPointEqual( m_Pos, heroPos ) )
	{
		m_PrevPos.x = m_Pos.x;
		m_PrevPos.y = m_Pos.y;

		switch(dir)
		{
		case 'w': case 'W':
			{
				if( md[m_Pos.y-1][m_Pos.x] != MS_WALL )
				{
					--m_Pos.y;
				}
			}
			break;

		case 's': case 'S':
			{
				if( md[m_Pos.y+1][m_Pos.x] != MS_WALL )
				{
					++m_Pos.y;
				}
			}
			break;

		case 'a': case 'A':
			{
				if( md[m_Pos.y][m_Pos.x-1] != MS_WALL )
				{
					--m_Pos.x;
				}
			}
			break;

		case 'd': case 'D':
			{
				if(	md[m_Pos.y][m_Pos.x+1] != MS_WALL )
				{
					++m_Pos.x;
				}
			}
			break;
		}
	}
}
