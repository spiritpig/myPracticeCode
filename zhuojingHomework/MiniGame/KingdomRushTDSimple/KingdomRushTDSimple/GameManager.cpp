#include "commonHeader.h"

GameManager::GameManager(void)
{
	m_pSgge = SggeCreate( SGGE_VERSION );
	m_pMap = new KingdomRushMap;
}

GameManager::~GameManager(void)
{
	SAFE_DELETE( m_pMap ); 
	m_pSgge->Release();
}

void GameManager::init()
{
	m_isRun = true;

	m_pMap->Init( ".//Map//newMap.mpd" );
}

bool GameManager::update()
{
	_processInput();

	return !m_isRun;
}

bool GameManager::render()
{
	if ( m_pSgge->Render_Begin() )
	{
		m_pSgge->Render_Clear( 0xff80ff80 );

		/////////////////////////////////////
		m_pMap->Render();
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
