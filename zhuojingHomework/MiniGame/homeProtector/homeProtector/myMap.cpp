#include "commonHeader.h"

myMap::myMap(void)
{
	m_pSgge = SggeCreate( SGGE_VERSION );

	m_pBGTex = NULL;
	m_pBGSpr = NULL;
}

myMap::~myMap(void)
{
	SAFE_DELETE( m_pBGSpr );
	if ( m_pBGTex != NULL )
	{
		m_pSgge->Texture_Free( m_pBGTex );
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
}

void myMap::update()
{

}

void myMap::render()
{
	m_pBGSpr->Render( 0, 0 );
}
