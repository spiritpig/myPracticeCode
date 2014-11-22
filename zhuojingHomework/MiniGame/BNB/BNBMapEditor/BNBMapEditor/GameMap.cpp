#include "StdAfx.h"
#include ".\gamemap.h"

GameMap::GameMap( HDC hBackBuffer )
{
	m_hBackBuffer = hBackBuffer;
	m_MaskColor = RGB( 255, 0, 255 );

	// 为地图分配空间
	m_pBackMapData = new char *[MAP_MAX_ROW];
	m_pMidMapData = new char *[MAP_MAX_ROW];
	m_pTopMapData = new char *[MAP_MAX_ROW];
	for ( int i=0; i<MAP_MAX_ROW; ++i )
	{
		m_pBackMapData[i] = new char[MAP_MAX_CEL];
		m_pMidMapData[i] = new char[MAP_MAX_CEL];
		m_pTopMapData[i] = new char[MAP_MAX_CEL];
	}

	for ( int i=0; i<MAP_MAX_ROW; ++i )
	{
		memset( m_pBackMapData[i], BK_GRASS1, sizeof(char)*MAP_MAX_CEL );
		memset( m_pMidMapData[i], BK_NONE, sizeof(char)*MAP_MAX_CEL );
		memset( m_pTopMapData[i], BK_NONE, sizeof(char)*MAP_MAX_CEL );
	}

	m_hBlockElementDc = CreateCompatibleDC( NULL );
	m_hBlockElementBmp = (HBITMAP)LoadImage( NULL, "Image//blocks.bmp", 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	SelectObject( m_hBlockElementDc, m_hBlockElementBmp );

	m_hBGDc = CreateCompatibleDC( NULL );
	m_hBGBmp = (HBITMAP)LoadImage( NULL, "Image//bg.bmp", 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	SelectObject( m_hBGDc, m_hBGBmp );

	m_Row = MAP_MAX_ROW;
	m_Cel = MAP_MAX_CEL;
}

GameMap::~GameMap(void)
{
	DeleteObject( m_hBGBmp );
	DeleteDC( m_hBGDc );

	DeleteObject( m_hBlockElementBmp );
	DeleteDC( m_hBlockElementDc );

	for( int i=0; i<MAP_MAX_ROW; ++i )
	{
		SAFE_DELARR( m_pBackMapData[i] );
		SAFE_DELARR( m_pMidMapData[i] );
		SAFE_DELARR( m_pTopMapData[i] );
	}
	SAFE_DELARR( m_pBackMapData );
	SAFE_DELARR( m_pMidMapData );
	SAFE_DELARR( m_pTopMapData );

}

void GameMap::RenderBG()
{
	// 绘制背景
	BitBlt( m_hBackBuffer, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, m_hBGDc, 0, 0, SRCCOPY );
}

void GameMap::RenderBack()
{
	for ( int j=0; j<MAP_MAX_ROW; ++j )
	{
		for ( int i=0; i<MAP_MAX_CEL; ++i )
		{
			switch( m_pBackMapData[j][i] )
			{
			case BK_NONE:
				{

				}
				break;

			case BK_GRASS1:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 0, 0, SRCCOPY );
				}
				break;

			case BK_GRASS2:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 0, 40, SRCCOPY );
				}
				break;

			case BK_GRASS3:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 0, 80, SRCCOPY );
				}
				break;

			case BK_GRASS4:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 40, 80, SRCCOPY );
				}
				break;

			case BK_GRASS5:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 80, 80, SRCCOPY );
				}
				break;

			case BK_ROAD1:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 120, 80, SRCCOPY );
				}
				break;

			case BK_ROAD2:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 200, 40, SRCCOPY );
				}
				break;

			case BK_ROAD3:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 200, 0, SRCCOPY );
				}
				break;
			}
		}
	}
}

void GameMap::RenderMidAndTop()
{
	for ( int j=0; j<MAP_MAX_ROW; ++j )
	{
		for ( int i=0; i<MAP_MAX_CEL; ++i )
		{
			switch( m_pMidMapData[j][i] )
			{
			case BK_NONE:
				{

				}
				break;

			case BK_HOUSE1:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 40, 40, SRCCOPY );
				}
				break;

			case BK_HOUSE2:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 80, 40, SRCCOPY );
				}
				break;

			case BK_HOUSE3:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 120, 40, SRCCOPY );
				}
				break;

			case BK_TREE:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 160, 40, SRCCOPY );
				}
				break;

			case BK_BLOCK1:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 240, 40, SRCCOPY );
				}
				break;

			case BK_BLOCK2:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 280, 40, SRCCOPY );
				}
				break;

			case BK_BOX:
				{
					BitBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, j*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 320, 40, SRCCOPY );
				}
				break;
			}
		}
	}

	for ( int j=0; j<MAP_MAX_ROW; ++j )
	{
		for ( int i=0; i<MAP_MAX_CEL; ++i )
		{
			switch( m_pTopMapData[j][i] )
			{
			case BK_NONE:
				{

				}
				break;

			case BK_HOUSE1TOP:
				{
					TransparentBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, (j-1)*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 40, 0,
						BLOCK_SIZE, BLOCK_SIZE, m_MaskColor );
				}
				break;

			case BK_HOUSE2TOP:
				{
					TransparentBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, (j-1)*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 80, 0,
						BLOCK_SIZE, BLOCK_SIZE, m_MaskColor );
				}
				break;

			case BK_HOUSE3TOP:
				{
					TransparentBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, (j-1)*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 120, 0,
						BLOCK_SIZE, BLOCK_SIZE, m_MaskColor );
				}
				break;

			case BK_TREETOP:
				{
					TransparentBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, (j-1)*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 160, 0, 
						BLOCK_SIZE, BLOCK_SIZE, m_MaskColor );
				}
				break;

			case BK_BLOCK1TOP:
				{
					TransparentBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, (j-1)*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 240, 0, 
						BLOCK_SIZE, BLOCK_SIZE, m_MaskColor );
				}
				break;

			case BK_BLOCK2TOP:
				{
					TransparentBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, (j-1)*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 280, 0, 
						BLOCK_SIZE, BLOCK_SIZE, m_MaskColor );
				}
				break;

			case BK_BOXTOP:
				{
					TransparentBlt( m_hBackBuffer, i*BLOCK_SIZE + 20, (j-1)*BLOCK_SIZE + 40,
						BLOCK_SIZE, BLOCK_SIZE, m_hBlockElementDc, 320, 0, 
						BLOCK_SIZE, BLOCK_SIZE, m_MaskColor );
				}
				break;
			}
		}
	}
}

void GameMap::SetBackMap( int row, int cel, BLOCK_KIND bk )
{
	if ( cel >= 0 && cel < MAP_MAX_CEL &&
		row >= 0 && row < MAP_MAX_ROW && 
		bk > BK_NONE && bk <= BK_ROAD3 )
	{
		m_pBackMapData[row][cel] = bk;
	}
}

void GameMap::SetMidAndTopMap( int row, int cel, BLOCK_KIND bk )
{
	if ( cel >= 0 && cel < MAP_MAX_CEL &&
		row >= 0 && row < MAP_MAX_ROW && 
		bk >= BK_HOUSE1 && bk <= BK_BOX )
	{
		m_pMidMapData[row][cel] = bk;
		m_pTopMapData[row][cel] = (BLOCK_KIND)((int)bk + 10);
	}
}

void GameMap::ClearMidAndTopMap( int row, int cel )
{
	m_pMidMapData[row][cel] = BK_NONE;
	m_pTopMapData[row][cel] = BK_NONE;
}

void GameMap::ClearMap()
{
	for ( int j=0; j<MAP_MAX_ROW; ++j )
	{
		for ( int i=0; i<MAP_MAX_CEL; ++i )
		{
			m_pBackMapData[j][i] = BK_GRASS1;
			m_pMidMapData[j][i] = BK_NONE;
			m_pTopMapData[j][i] = BK_NONE;
		}
	}
}

void GameMap::SaveMapToFile( char *filename )
{
	FILE *fp = fopen( filename, "wb" );
	if ( !fp )
	{
		MessageBox( NULL, "文件创建失败", "提示", MB_OK|MB_ICONWARNING );
		return;
	}

	for ( int i=0; i<MAP_MAX_ROW; ++i )
	{
		fwrite( m_pBackMapData[i], sizeof(char), MAP_MAX_CEL, fp );
	}
	for ( int i=0; i<MAP_MAX_ROW; ++i )
	{
		fwrite( m_pMidMapData[i], sizeof(char), MAP_MAX_CEL, fp );
	}
	for ( int i=0; i<MAP_MAX_ROW; ++i )
	{
		fwrite( m_pTopMapData[i], sizeof(char), MAP_MAX_CEL, fp );
	}

	fclose( fp );
}

void GameMap::LoadMapFromFile( char *filename )
{
	FILE *fp = fopen( filename, "rb" );
	if ( !fp )
	{
		MessageBox( NULL, "文件打开失败", "提示", MB_OK|MB_ICONWARNING );
		return;
	}

	for ( int i=0; i<MAP_MAX_ROW; ++i )
	{
		fread( m_pBackMapData[i], sizeof(char), MAP_MAX_CEL, fp );
	}
	for ( int i=0; i<MAP_MAX_ROW; ++i )
	{
		fread( m_pMidMapData[i], sizeof(char), MAP_MAX_CEL, fp );
	}
	for ( int i=0; i<MAP_MAX_ROW; ++i )
	{
		fread( m_pTopMapData[i], sizeof(char), MAP_MAX_CEL, fp );
	}

	fclose( fp );
}

