#include "StdAfx.h"

cursor::cursor(void)
{
	m_CState.pos.x = 0;
	m_CState.pos.y = 0;
}

void cursor::init( int x, int y )
{
	m_CState.pos.x = x;
	m_CState.pos.y = y;

	m_CState.prevPos.x = x;
	m_CState.prevPos.y = y;
}

void cursor::update()
{
	_processInput();
}

void cursor::draw()
{
	gotoXY( m_CState.prevPos.x, m_CState.prevPos.y );
	printf( "%s", STR_SPACE );

	gotoXY( m_CState.pos.x, m_CState.pos.y );
	printf( "%s", STR_CURSOR );
}

void cursor::_processInput()
{
	if ( _kbhit() )
	{
		m_Dir = _getch();

		switch ( m_Dir )
		{
		case 'w': case 'W':
			{
				if( !_isPointInvalid( m_CState.pos.x, m_CState.pos.y-1 ) )
				{
					m_CState.prevPos.x = m_CState.pos.x;
					m_CState.prevPos.y = m_CState.pos.y;

					--m_CState.pos.y;
				}
			}
			break;

		case 's': case 'S':
			{
				if( !_isPointInvalid( m_CState.pos.x, m_CState.pos.y+1 ) )
				{
					m_CState.prevPos.x = m_CState.pos.x;
					m_CState.prevPos.y = m_CState.pos.y;

					++m_CState.pos.y;
				}
			}
			break;

		case 'a': case 'A':
			{
				if( !_isPointInvalid( m_CState.pos.x-1, m_CState.pos.y ) )
				{
					m_CState.prevPos.x = m_CState.pos.x;
					m_CState.prevPos.y = m_CState.pos.y;

					--m_CState.pos.x;
				}
			}
			break;

		case 'd': case 'D':
			{
				if( !_isPointInvalid( m_CState.pos.x+1, m_CState.pos.y ) )
				{
					m_CState.prevPos.x = m_CState.pos.x;
					m_CState.prevPos.y = m_CState.pos.y;

					++m_CState.pos.x;
				}
			}
			break;
		}
	}
}

bool cursor::_isPointInvalid( int x, int y )
{
	return (x <= 0) || (x >= MAP_CEL-1) ||
		   (y <= 0) || (y >= MAP_ROW-1);
}

