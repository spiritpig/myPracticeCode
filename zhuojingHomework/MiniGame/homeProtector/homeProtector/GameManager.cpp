#include "commonHeader.h"

GameManager::GameManager(void)
{
	m_pSgge = SggeCreate( SGGE_VERSION );
	m_pMap = new myMap;
	m_towerSlipper =  new tower_Slipper;
}

GameManager::~GameManager(void)
{
	SAFE_DELETE( m_towerSlipper );
	SAFE_DELETE( m_pMap ); 
	m_pSgge->Release();
}

void GameManager::init()
{
	m_isRun = true;

	m_pMap->init();
	m_towerSlipper->init();
}

bool GameManager::update()
{
	_processInput();
	m_pMap->update();
	m_towerSlipper->update();

	return !m_isRun;
}

bool GameManager::render()
{
	if ( m_pSgge->Render_Begin() )
	{
		m_pSgge->Render_Clear( 0x00f0f0f0 );

		/////////////////////////////////////
		m_pMap->render();
		m_towerSlipper->render();
		/////////////////////////////////////

		m_pSgge->Render_End();
	}

	return true;
}

void GameManager::_processInput()
{
	if ( m_pSgge->Input_KeyDown( SGGEK_ESCAPE ) )
	{
		m_isRun = false;
	}
}
