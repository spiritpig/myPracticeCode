#include ".\tower_slipper.h"

PSTEXTURE tower_Slipper::m_pTowerTex = NULL;
size_t tower_Slipper::m_TexUseCount = 0;

PSTEXTURE tower_Slipper::m_pTowerBulletTex = NULL;
size_t tower_Slipper::m_BulletTexUseCount = 0;

//////////////////////////////////////////////////////////////////////////
//
//	判断子弹是否有效
//
//////////////////////////////////////////////////////////////////////////
bool tower_Slipper::_isBulletValid( const vector2 &v2 )
{
	if( (m_TowerBulletState.pos.x >= v2.x-20.0f && m_TowerBulletState.pos.x <= v2.x+20.0f && 
		 m_TowerBulletState.pos.y >= v2.y-20.0f && m_TowerBulletState.pos.y <= v2.y+20.0f) ||
		 m_TowerBulletState.pos.x <= 0 || m_TowerBulletState.pos.x >= SCREEN_WIDTH || 
		 m_TowerBulletState.pos.y <= 0 || m_TowerBulletState.pos.y >= SCREEN_HEIGHT )
	{
		return false;
	}

	return true;
}

tower_Slipper::tower_Slipper(void)
{
	m_pEngine = SggeCreate( SGGE_VERSION );
	m_pTowerBulletSpr = NULL;
	m_pTowerSpr = NULL;
}

tower_Slipper::~tower_Slipper(void)
{
	SAFE_DELETE( m_pTowerBulletSpr );
	--m_BulletTexUseCount;
	if( m_BulletTexUseCount <= 0 )
	{
		m_pEngine->Texture_Free( m_pTowerBulletTex );
	}

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
	if ( m_BulletTexUseCount <= 0 )
	{
		m_pTowerBulletTex = m_pEngine->Texture_Load( "image/bullet_TowerSlipper.png" );
	}
	++m_BulletTexUseCount;
	m_pTowerBulletSpr = new SggeSprite( m_pTowerBulletTex, 1.0f, 1.0f, 
		(float)m_pEngine->Texture_GetWidth(m_pTowerBulletTex),
		(float)m_pEngine->Texture_GetHeight(m_pTowerBulletTex) );

	if ( m_TexUseCount <= 0 )
	{
		m_pTowerTex = m_pEngine->Texture_Load( "image/towerSlipper.png" );
	}
	++m_TexUseCount;
	m_pTowerSpr = new SggeSprite( m_pTowerTex, 1.0f, 1.0f, 
		(float)m_pEngine->Texture_GetWidth(m_pTowerTex),
		(float)m_pEngine->Texture_GetHeight(m_pTowerTex) );

	m_TowerState.def = 50;
	m_TowerState.cost = 130;
	m_TowerState.atkRange = 300;
	m_TowerState.pos.x = 400.0f;
	m_TowerState.pos.y = 120.0f;
	m_TowerState.isFire = true;

	m_TowerBulletState.at = DT_PHYSICAL_DAMAGE;
	m_TowerBulletState.min_atk = 13;
	m_TowerBulletState.max_atk = 25;
	m_TowerBulletState.speed = 200.0f;
	m_TowerBulletState.pos = m_TowerState.pos;

	m_hWnd = GetActiveWindow();
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

	static POINT mousePos;
	GetCursorPos( &mousePos );
	ScreenToClient( m_hWnd, &mousePos );
	vector2 mPos( (float)mousePos.x, (float)mousePos.y );
	m_TowerBulletState.dir = (mPos-m_TowerBulletState.pos).normalized();

	// 碰撞检测，判断是否碰到了目标或者跳出了边界
	if( m_TowerState.isFire )
	{
		if ( !_isBulletValid( mPos ) )
		{
			m_TowerBulletState.pos = m_TowerState.pos;
		}

		// 更新子弹的坐标
		m_TowerBulletState.pos += m_TowerBulletState.dir*m_TowerBulletState.speed
									*m_pEngine->Timer_GetDelta();
	}
}

void tower_Slipper::render()
{
	m_pTowerSpr->Render( m_TowerState.pos.x, m_TowerState.pos.y );
	m_pTowerBulletSpr->Render( m_TowerBulletState.pos.x, m_TowerBulletState.pos.y );
}

void tower_Slipper::_processInput()
{
}
