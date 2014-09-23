#include ".\tower_slipper.h"

PSTEXTURE tower_Slipper::m_TowerTex = NULL;

tower_Slipper::tower_Slipper(void)
{
	m_pEngine = SggeCreate( SGGE_VERSION );
	m_TowerTex = NULL;
}

tower_Slipper::~tower_Slipper(void)
{
	if( m_TowerTex != NULL )
	{
		m_pEngine->Texture_Free( m_TowerTex );
	}
	m_pEngine->Release();
}

void tower_Slipper::init()
{
	if( m_TowerTex != NULL )
	{
		m_pEngine->Texture_Free( m_TowerTex );
	}
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

}

void tower_Slipper::_processInput()
{

}
