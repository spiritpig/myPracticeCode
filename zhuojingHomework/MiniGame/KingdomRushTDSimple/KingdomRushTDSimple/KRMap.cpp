#include "commonHeader.h"
using namespace std;

KingdomRushMap::KingdomRushMap(void)
{
	m_pEngine = SggeCreate( SGGE_VERSION );

	m_pBgTex = m_pEngine->Texture_Load( "Image//background//bg1.bmp" );
	m_pBgSpr = new SggeSprite( m_pBgTex, 0.0f, 0.0f,
		(float)m_pEngine->Texture_GetWidth( m_pBgTex ),
		(float)m_pEngine->Texture_GetHeight( m_pBgTex ) );

	m_pMonsterMoveBlockTex = m_pEngine->Texture_Load( "Image//monsterMoveBlock.bmp" );
	m_pMonsterMoveBlockSpr = new SggeSprite( m_pMonsterMoveBlockTex, 0.0f, 0.0f, 
		(float)m_pEngine->Texture_GetWidth( m_pMonsterMoveBlockTex ),
		(float)m_pEngine->Texture_GetHeight( m_pMonsterMoveBlockTex ) );

	m_pStartPointTex = m_pEngine->Texture_Load( "Image//startPoint.bmp" );
	m_pStartPointSpr = new SggeSprite( m_pStartPointTex, 0.0f, 0.0f,
		(float)m_pEngine->Texture_GetWidth( m_pStartPointTex ),
		(float)m_pEngine->Texture_GetHeight( m_pStartPointTex ) );

	m_pEndPointTex = m_pEngine->Texture_Load( "Image//endPoint.bmp" );
	m_pEndPointSpr = new SggeSprite( m_pEndPointTex, 0.0f, 0.0f,
		(float)m_pEngine->Texture_GetWidth( m_pEndPointTex ),
		(float)m_pEngine->Texture_GetHeight( m_pEndPointTex ) );

	m_MapSize.x = 700;
	m_MapSize.y = 600;
	m_StartPointSize.x = 80.0f;
	m_StartPointSize.y = 40.0f;
	m_EndPointSize.x = 80;
	m_EndPointSize.y = 40;
	m_StartPoint.x = 0.0f;
	m_StartPoint.y = 0.0f;
	m_EndPoint.x = 0.0f;
	m_EndPoint.y = 0.0f;

	m_MonsterMovePath.clear();
}

KingdomRushMap::~KingdomRushMap(void)
{
	SAFE_DELETE( m_pStartPointSpr );
	if( m_pStartPointTex )
	{
		m_pEngine->Texture_Free( m_pStartPointTex );
	}

	SAFE_DELETE( m_pEndPointSpr );
	if( m_pEndPointTex )
	{
		m_pEngine->Texture_Free( m_pEndPointTex );
	}

	SAFE_DELETE( m_pMonsterMoveBlockSpr );
	if( m_pMonsterMoveBlockTex )
	{
		m_pEngine->Texture_Free( m_pMonsterMoveBlockTex );
	}

	SAFE_DELETE( m_pBgSpr );
	if( m_pBgTex )
	{
		m_pEngine->Texture_Free( m_pBgTex );
	}

	m_pEngine->Release();
}

void KingdomRushMap::Init( char *filename )
{
	_LoadMapFromFile( filename );
}

void KingdomRushMap::Render()
{
	// »æÖÆ±³¾°Í¼
	m_pBgSpr->Render( 0, 0 );
}

void KingdomRushMap::SetBackgroundImage( char *filename )
{
	if ( m_pBgTex != NULL )
	{
		m_pEngine->Texture_Free( m_pBgTex );
	}

	m_pBgTex = m_pEngine->Texture_Load( filename );
	m_pBgSpr->SetTexture( m_pBgTex );
}

bool KingdomRushMap::_LoadMapFromFile( char *filename )
{
	if( filename == NULL )
	{
		return false;
	}

	FILE *fp = fopen( filename, "rb" );
	if ( !fp )
	{
		return false;
	}

	isSetStart = true;
	isSetEnd = true;
	fread( &m_StartPoint, sizeof( Vector2D ), 1, fp );
	fread( &m_EndPoint, sizeof( Vector2D ), 1, fp );

	int pathLen;
	fread( &pathLen, sizeof(int), 1, fp );

	Vector2D pt;
	for ( int i=0; i<pathLen; ++i )
	{
		fread( &pt, sizeof( Vector2D ), 1, fp );
		m_MonsterMovePath.push_back( pt );
	}

	fclose( fp );
	return true;
}

