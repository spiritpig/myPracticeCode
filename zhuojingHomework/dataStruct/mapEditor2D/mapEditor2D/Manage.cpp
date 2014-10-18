#include ".\manage.h"

Manage::Manage(void)
{
	m_pSgge=SggeCreate(SGGE_VERSION);
	m_pMap=NULL;
}

Manage::~Manage(void)
{
	SAFE_DELETE(m_pMap);
	m_pSgge->Release();
}

void Manage::Init()
{
	SAFE_DELETE(m_pMap);
	m_pMap=new Map;
	m_pMap->Init();

	m_MousePos.x = 0;
	m_MousePos.y = 0;
}

bool Manage::Update()
{
	_ProcessInput();

	m_pMap->Update();
	return false;
}

bool Manage::Render()
{
	if(m_pSgge->Render_Begin())
	{
		m_pSgge->Render_Clear(0xff808080);

		//////////////////////////////////
		m_pMap->Render();
		//////////////////////////////////

		m_pSgge->Render_End();
		return true;
	}
	else
	{
		return false;
	}
}

void Manage::_ProcessInput()
{
	// 开始寻路操作
	if( m_pSgge->Input_KeyDown( SGGEK_RETURN ) )
	{
		m_pMap->setStartPathFinding(true);
	}
	else
	if ( m_pSgge->Input_KeyDown( SGGEK_O ) )
	{
		m_pMap->turnOffPathDisplay();
	}

	// 设置寻路所使用的寻路算法
	if( m_pSgge->Input_KeyDown( SGGEK_1 ) )
	{
		m_pMap->setCurPathFindingMethod( DEPTH_FIRST_SEARCH );
	}
	else
	if( m_pSgge->Input_KeyDown( SGGEK_2 ) )
	{
		m_pMap->setCurPathFindingMethod( BREADTH_FIRST_SEARCH );
	}
	else
	if( m_pSgge->Input_KeyDown( SGGEK_3 ) )
	{
		m_pMap->setCurPathFindingMethod( ASTAR );
	}

	// 设置当前地图编辑器的格子设置属性
	if( m_pSgge->Input_KeyDown( SGGEK_S ) )
	{
		m_pMap->setEditState( ES_SPACE );
	}
	else
	if( m_pSgge->Input_KeyDown( SGGEK_W ) )
	{
		m_pMap->setEditState( ES_WALL );
	}
	else
	if( m_pSgge->Input_KeyDown( SGGEK_E ) )
	{
		m_pMap->setEditState( ES_END );
	}
	else
	if( m_pSgge->Input_KeyDown( SGGEK_R ) )
	{
		m_pMap->setEditState( ES_START );
	}

	// 获取鼠标点击位置
	if ( m_pSgge->Input_MouseKeyState( SGGEM_LEFT ) )
	{
		GetCursorPos( &m_MousePos );
		ScreenToClient( GetActiveWindow(), &m_MousePos );
		m_pMap->changeBlockAttribute( m_MousePos );
	}

	// 保存地图
	if( m_pSgge->Input_GetKeyState(SGGEK_LCONTROL) &&
		m_pSgge->Input_KeyDown( SGGEK_S ) )
	{
		m_pMap->saveMap( MAP_FILENAME );
	}
}

