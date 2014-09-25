#include ".\tower_slipper.h"

PSTEXTURE tower_Slipper::m_pTowerTex = NULL;
size_t tower_Slipper::m_TexUseCount = 0;

tower_Slipper::tower_Slipper(void)
{
	m_pEngine = SggeCreate( SGGE_VERSION );
	m_pTowerSpr = NULL;
}

tower_Slipper::~tower_Slipper(void)
{
	SAFE_DELETE( m_pTowerSpr );
	--m_TexUseCount;
	if( m_TexUseCount <= 0 )
	{
		m_pEngine->Texture_Free( m_pTowerTex );
	}
	m_pEngine->Release();
}

void tower_Slipper::init()
{
	if ( m_TexUseCount <= 0 )
	{
		m_pTowerTex = m_pEngine->Texture_Load( "image/towerSlipper.png" );
	}
	++m_TexUseCount;

	m_pTowerSpr = new SggeSprite( m_pTowerTex, 1.0f, 1.0f, 
		(float)m_pEngine->Texture_GetWidth(m_pTowerTex),
		(float)m_pEngine->Texture_GetHeight(m_pTowerTex) );
}

void tower_Slipper::attack()
{

}

void tower_Slipper::levelUp()
{

}

void tower_Slipper::destory()
{

}

void tower_Slipper::update()
{
	_processInput();	
}

void tower_Slipper::render()
{
	m_pTowerSpr->Render( 400, 120 );
}

void tower_Slipper::_processInput()
{

}
