#include "commonHeader.h"

Manage::Manage()
{
	m_pSgge = SggeCreate( SGGE_VERSION );
	isRun = true;
}

void Manage::init()
{
	m_gameMap.init();
	m_hero.init();
}


Manage::~Manage(void)
{
	m_pSgge->Release();
}

bool Manage::update()
{
	_processInput();

	m_gameMap.update();
	m_hero.update( m_gameMap.getMapLen() );

	return !isRun;
}

bool Manage::render()
{
	if( m_pSgge->Render_Begin() )
	{
		m_pSgge->Render_Clear( 0xffffffff );

		///////////////////
		m_gameMap.render();
		m_hero.render( m_gameMap.getMapLen() );
		///////////////////

		m_pSgge->Render_End();
	}

	return true;
}

void Manage::_processInput()
{
	if( m_pSgge->Input_GetKeyState( SGGEK_ESCAPE ) )
	{
		isRun = false;
	}

	///////////////////
	///////////////////
}