#include "commonHeader.h"
#include ".\gamemap.h"

GameMap::GameMap(void)
{
	m_pEngine = SggeCreate( SGGE_VERSION );
	
	m_pBGTex = m_pEngine->Texture_Load( ".\\Image\\bg.png" );
	m_pBGSpr = new SggeSprite(m_pBGTex, 0.0f, 0.0f,
		(float)m_pEngine->Texture_GetWidth( m_pBGTex ),
		(float)m_pEngine->Texture_GetHeight( m_pBGTex ) );

	m_pBlockElementTex = m_pEngine->Texture_Load( ".\\Image\\elem.png" );
	m_pBlockElementSpr = new SggeSprite( m_pBlockElementTex, 0.0f, 0.0f,
		(float)m_pEngine->Texture_GetWidth( m_pBlockElementTex ),
		(float)m_pEngine->Texture_GetHeight( m_pBlockElementTex ) );

	// 清空地图
	for ( int i=0; i<MAP_MAX_ROW; ++i )
	{
		memset( m_pBackMapData[i], BK_GRASS1, sizeof(char)*MAP_MAX_CEL );
		memset( m_pMidMapData[i], BK_NONE, sizeof(char)*MAP_MAX_CEL );
		memset( m_pTopMapData[i], BK_NONE, sizeof(char)*MAP_MAX_CEL );
	}

	m_Row = 0;
	m_Cel = 0;
}

GameMap::~GameMap(void)
{
	SAFE_DELETE( m_pBlockElementSpr );
	if ( m_pBlockElementTex )
	{
		m_pEngine->Texture_Free( m_pBlockElementTex );
	}

	SAFE_DELETE( m_pBGSpr );
	if ( m_pBGTex )
	{
		m_pEngine->Texture_Free( m_pBGTex );
	}

	m_pEngine->Release();
}

void GameMap::Init()
{
}

void GameMap::Update()
{
}

void GameMap::RenderBack()
{
	// 绘制背景
	m_pBGSpr->Render( 0.0f, 0.0f );

	// 绘制背景层地图
	for ( int j=0; j<MAP_MAX_ROW; ++j )
	{
		for ( int i=0; i<MAP_MAX_CEL; ++i )
		{
			if ( m_pBackMapData[j][i] != BK_NONE)
			{		
				_SetCurElemRect( m_pBackMapData[j][i] );
				m_pBlockElementSpr->Render( i*BLOCK_SIZE + 20.0f, 
											j*BLOCK_SIZE + 40.0f );
			}
		}
	}
	
}

void GameMap::RenderMid()
{
	// 中层地图
	for ( int j=0; j<MAP_MAX_ROW; ++j )
	{
		for ( int i=0; i<MAP_MAX_CEL; ++i )
		{
			if ( m_pMidMapData[j][i] != BK_NONE)
			{		
				_SetCurElemRect( m_pMidMapData[j][i] );
				m_pBlockElementSpr->Render( i*BLOCK_SIZE + 20.0f, 
					j*BLOCK_SIZE + 40.0f );
			}
		}
	}
}

void GameMap::RenderTop()
{
	// 中层地图
	for ( int j=0; j<MAP_MAX_ROW; ++j )
	{
		for ( int i=0; i<MAP_MAX_CEL; ++i )
		{
			if ( m_pMidMapData[j][i] != BK_NONE)
			{		
				_SetCurElemRect( m_pTopMapData[j][i] );
				m_pBlockElementSpr->Render( i*BLOCK_SIZE + 20.0f, 
					(j-1)*BLOCK_SIZE + 40.0f );
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

void GameMap::_SetCurElemRect( char block )
{
	switch( block )
	{
	// 背景层地图
	case BK_GRASS1:
		{
			m_pBlockElementSpr->SetTextureRect( 0, 0, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_GRASS2:
		{
			m_pBlockElementSpr->SetTextureRect( 0, 40, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_GRASS3:
		{
			m_pBlockElementSpr->SetTextureRect( 0, 80, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_GRASS4:
		{
			m_pBlockElementSpr->SetTextureRect( 40, 80, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_GRASS5:
		{
			m_pBlockElementSpr->SetTextureRect( 80, 80, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_ROAD1:
		{
			m_pBlockElementSpr->SetTextureRect( 120, 80, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_ROAD2:
		{
			m_pBlockElementSpr->SetTextureRect( 200, 40, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_ROAD3:
		{
			m_pBlockElementSpr->SetTextureRect( 200, 0, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;

	// 中层地图元素
	case BK_HOUSE1:
		{
			m_pBlockElementSpr->SetTextureRect( 40, 40, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_HOUSE2:
		{
			m_pBlockElementSpr->SetTextureRect( 80, 40, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_HOUSE3:
		{
			m_pBlockElementSpr->SetTextureRect( 120, 40, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_TREE:
		{
			m_pBlockElementSpr->SetTextureRect( 160, 40, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_BLOCK1:
		{
			m_pBlockElementSpr->SetTextureRect( 240, 40, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_BLOCK2:
		{
			m_pBlockElementSpr->SetTextureRect( 280, 40, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_BOX:
		{
			m_pBlockElementSpr->SetTextureRect( 320, 40, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;

	// 顶层地图
	case BK_HOUSE1TOP:
		{
			m_pBlockElementSpr->SetTextureRect( 40, 0, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_HOUSE2TOP:
		{
			m_pBlockElementSpr->SetTextureRect( 80, 0, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_HOUSE3TOP:
		{
			m_pBlockElementSpr->SetTextureRect( 120, 0, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_TREETOP:
		{
			m_pBlockElementSpr->SetTextureRect( 160, 0, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_BLOCK1TOP:
		{
			m_pBlockElementSpr->SetTextureRect( 240, 0, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_BLOCK2TOP:
		{
			m_pBlockElementSpr->SetTextureRect( 280, 0, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	case BK_BOXTOP:
		{
			m_pBlockElementSpr->SetTextureRect( 320, 0, BLOCK_SIZE, BLOCK_SIZE );
		}
		break;
	}
}

bool GameMap::IsHitZhangAiWu( int row, int cel )
{
	return m_pMidMapData[row][cel] >= BK_HOUSE1;
}

