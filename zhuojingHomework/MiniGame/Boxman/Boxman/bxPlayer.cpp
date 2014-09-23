#include "StdAfx.h"

bxPlayer::bxPlayer()
{
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_BoxNum = 0;

	m_PrevPos.x = 1;
	m_PrevPos.y = 1;
}

void bxPlayer::init( int x, int y, int boxNum,
					bxBox *boxes )
{
	m_Pos.x = x;
	m_Pos.y = y;

	this->m_Boxes = boxes;
	m_BoxNum = boxNum;
}

void bxPlayer::update( MAPDATA md, char dir )
{
	_processInput( md, dir );
}

void bxPlayer::draw()
{
	gotoXY( m_PrevPos.x, m_PrevPos.y );
	printf( SPACE_CHAR );

	gotoXY( m_Pos.x, m_Pos.y );
	printf( PLAYER_CHAR );
}

void bxPlayer::_processInput( MAPDATA md, char dir )
{
	point tempP = { m_Pos.x, m_Pos.y },
		 offset = { 0, 0 };

	// 我们采用先走后判断的原则，移动
	// 即先试着移动过去，然后再判断是否可行
	// 采用这种方式，是因为有可移动的盒子存在
	// 所以，移动的时候，必须注意盒子是否会因为
	// 人的移动而碰到墙壁，此时是不应该移动的
	switch(dir)
	{
	case 'w': case 'W':
		{
			if( md[m_Pos.y-1][m_Pos.x] != MS_WALL )
			{
				--tempP.y;
				offset.y = -1;
			}
		}
		break;

	case 's': case 'S':
		{
			if( md[m_Pos.y+1][m_Pos.x] != MS_WALL )
			{
				++tempP.y;
				offset.y = 1;
			}
		}
		break;

	case 'a': case 'A':
		{
			if( md[m_Pos.y][m_Pos.x-1] != MS_WALL )
			{
				--tempP.x;
				offset.x = -1;
			}
		}
		break;

	case 'd': case 'D':
		{
			if( md[m_Pos.y][m_Pos.x+1] != MS_WALL )
			{
				++tempP.x;
				offset.x = 1;
			}
		}
		break;
	}

	int i = 0;
	for ( i; i<m_BoxNum; ++i )
	{
		// 盒子的前面是盒子和墙壁的时候，都不能移动
		if( isPointEqual(tempP, m_Boxes[i].getPos()) &&
			( md[tempP.y + offset.y][tempP.x + offset.x] == MS_WALL ||
			  _isBox( tempP.x+offset.x, tempP.y+offset.y ) ) )
		{
			break;
		}
	}

	// 如果不存在盒子撞墙的问题，我们就移动过去
	if( i >= m_BoxNum )
	{
		m_PrevPos.x = m_Pos.x;
		m_PrevPos.y = m_Pos.y;

		m_Pos.x = tempP.x;
		m_Pos.y = tempP.y;
	}
}

bool bxPlayer::_isBox( int px, int py )
{
	for ( int i=0; i<m_BoxNum; ++i )
	{
		if(isPointEqual( px, py, m_Boxes[i].getPos().x, m_Boxes[i].getPos().y )  )
		{
			return true;
		}
	}

	return false;
}