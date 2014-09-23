#include "commonHeader.h"

myMap::myMap(void)
{
	m_pSgge = SggeCreate( SGGE_VERSION );

	m_pBGTex = NULL;
	m_pBGSpr = NULL;
	m_pTowerTex = NULL;
	m_pTowerSpr = NULL;
}

myMap::~myMap(void)
{
	SAFE_DELETE( m_pBGSpr );
	if ( m_pBGTex != NULL )
	{
		m_pSgge->Texture_Free( m_pBGTex );
	}

	SAFE_DELETE( m_pTowerSpr );
	if ( m_pTowerTex != NULL )
	{
		m_pSgge->Texture_Free( m_pTowerTex );
	}

	m_pSgge->Release();
}

void myMap::init()
{
	SAFE_DELETE( m_pBGSpr );
	if ( m_pBGTex != NULL )
	{
		m_pSgge->Texture_Free( m_pBGTex );
	}
	m_pBGTex = m_pSgge->Texture_Load( "image/bgTest.png" );
	m_pBGSpr = new SggeSprite( m_pBGTex, 1.0f, 1.0f, 
		(float)m_pSgge->Texture_GetWidth(m_pBGTex),
		(float)m_pSgge->Texture_GetHeight(m_pBGTex) );

	SAFE_DELETE( m_pTowerSpr );
	if ( m_pTowerTex != NULL )
	{
		m_pSgge->Texture_Free( m_pTowerTex );
	}
	m_pTowerTex = m_pSgge->Texture_Load( "image/towerSword.png" );
	m_pTowerSpr = new SggeSprite( m_pTowerTex, 1.0f, 1.0f, 
		(float)m_pSgge->Texture_GetWidth(m_pTowerTex),
		(float)m_pSgge->Texture_GetHeight(m_pTowerTex) );
}

void myMap::update()
{

}

void myMap::render()
{
	m_pBGSpr->Render( 0, 0 );
	m_pTowerSpr->Render( 400, 120 );
}
