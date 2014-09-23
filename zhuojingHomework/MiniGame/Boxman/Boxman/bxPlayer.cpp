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

	// ���ǲ������ߺ��жϵ�ԭ���ƶ�
	// ���������ƶ���ȥ��Ȼ�����ж��Ƿ����
	// �������ַ�ʽ������Ϊ�п��ƶ��ĺ��Ӵ���
	// ���ԣ��ƶ���ʱ�򣬱���ע������Ƿ����Ϊ
	// �˵��ƶ�������ǽ�ڣ���ʱ�ǲ�Ӧ���ƶ���
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
		// ���ӵ�ǰ���Ǻ��Ӻ�ǽ�ڵ�ʱ�򣬶������ƶ�
		if( isPointEqual(tempP, m_Boxes[i].getPos()) &&
			( md[tempP.y + offset.y][tempP.x + offset.x] == MS_WALL ||
			  _isBox( tempP.x+offset.x, tempP.y+offset.y ) ) )
		{
			break;
		}
	}

	// ��������ں���ײǽ�����⣬���Ǿ��ƶ���ȥ
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