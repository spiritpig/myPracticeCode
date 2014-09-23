#include "stdafx.h"

bxManager::bxManager()
{
	m_BoxNum = 0;
	m_FinishedBoxNum = 0;

	m_MapRow = 0;
	m_MapCel = 0;
	m_MapData = NULL;

	isRun = true;
}

bxManager::~bxManager()
{
	if( m_Boxes != NULL )
	{
		delete[] m_Boxes;
	}

	if( m_MapData != NULL )
	{
		for ( int i=0; i<m_MapRow; ++i )
		{
			delete[] m_MapData[i];
		}
		delete[] m_MapData;
	}
}

void bxManager::init( const char *filename )
{
	_fillDataFromFile( filename );
}

void bxManager::update()
{
	if( kbhit() )
	{
		char dir = getch();

		m_Hero.update( m_MapData, dir );

		int count = 0;
		for ( int i=0; i<m_BoxNum; ++i )
		{
			m_Boxes[i].update( m_MapData, m_Hero.getPos(), dir );

			if( m_MapData[m_Boxes[i].getPos().y][m_Boxes[i].getPos().x] == MS_GOAL )
			{
				++count;
			}
		}
		m_FinishedBoxNum = count;

	}
}

void bxManager::draw()
{
	int j = 0;
	for ( int i=0; i<m_BoxNum; ++i )
	{
		m_Boxes[i].draw();
		for ( j=0; j<m_BoxNum; ++j )
		{
			if ( isPointEqual( m_Boxes[i].getPrevPos(), m_Boxes[j].getPos() ) )
			{
				break;
			}
		}

		if( j >= 4 )
		{
			_redrawPos( m_Boxes[i].getPrevPos() );
		}
	}

	m_Hero.draw();
	_redrawPos( m_Hero.getPrevPos() );
}

void bxManager::gameLoop()
{
	init();
	drawMap();

	while( isRun )
	{
		Sleep( 100 );
		update();
		draw();
		if( _isWin() )
		{
			isRun = false;
		}
	}

	system( "cls" );
	printf( "赢了\n" );
}

void bxManager::drawMap()
{
	for ( int w=0; w<m_MapRow; ++w )
	{
		for ( int h=0; h<m_MapCel; ++h )
		{
			gotoXY( h, w );
			switch ( m_MapData[w][h] )
			{
			case MS_SPACE:
				{
					printf( SPACE_CHAR );
				}
				break;

			case MS_WALL:
				{
					printf( WALL_CHAR );
				}
				break;

			case MS_GOAL:
				{
					printf( GOAL_CHAR );
				}
				break;
			}
		}
		printf( "\n" );
	}
}

void bxManager::_redrawPos( const point &p )
{
	if( m_MapData[ p.y ][ p.x ] == MS_GOAL )
	{
		gotoXY( p.x, p.y );
		printf( GOAL_CHAR );
	}
	else
	{
		if( m_MapData[ p.y ][ p.x ] == MS_SPACE )
		{
			gotoXY( p.x, p.y );
			printf( SPACE_CHAR );
		}
	}
}


void bxManager::_fillDataFromFile( const char *filename )
{
	FILE *fp;
	fp = fopen( filename, "r" );
	if ( !fp )
	{
		printf( "地图初始化失败" );
		return;
	}
	else
	{
		fscanf( fp, "%d %d %d", &m_MapRow, &m_MapCel, &m_BoxNum );
		// 读取换行符，进入下一行 
		fgetc( fp );

		// 分配空间
		m_MapData = new char *[m_MapRow];
		for ( int i=0; i<m_MapRow; ++i )
		{
			m_MapData[i] = new char[m_MapCel];
	 	}

		m_Boxes = new bxBox[m_BoxNum];

		// 填充数据
		int c = 0, boxI = 0;
		for ( int h=0; h<m_MapRow; ++h )
		{
			for ( int w=0; w<m_MapCel+1; ++w )
			{
				c = fgetc( fp );
				if( c != '\n' )
				{
					c -= '0';

					// 这里地图中并不需要记录盒子和玩家，
					// 将盒子和玩家的位置值为空，他们的绘制由自己来画
					// 我们将会使用控制台句柄，实现地图、盒子和玩家的分开绘制
					switch(c)
					{
					case MS_SPACE:
					case MS_WALL:
					case MS_GOAL:
						{
							m_MapData[h][w] = c;
						}
						break;

					case MS_BOX:
						{
							m_MapData[h][w] = MS_SPACE;
							m_Boxes[boxI].init( w, h );
							++boxI;
						}
						break;

					case MS_PLAYER:
						{
							m_MapData[h][w] = MS_SPACE;
							m_Hero.init( w, h, m_BoxNum, m_Boxes );
						}
						break;
					}
				}
			}
		}
	}
}

bool bxManager::_isWin()
{
	return (m_FinishedBoxNum == m_BoxNum);
}
