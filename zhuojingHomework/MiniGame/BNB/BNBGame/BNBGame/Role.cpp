#include ".\role.h"

Role::Role(void)
{
	m_pEngine = SggeCreate( SGGE_VERSION );

	m_pRoleTex = NULL;
	m_RoleData.dir = D_DOWN;
	m_RoleData.roleFA = NULL;
	m_RoleData.speed = 0.0f;
	m_RoleData.maxSpeed = 0.0f;
	m_RoleState = RS_STAND;
}

Role::~Role(void)
{
	m_pEngine->Release();
}

void Role::Init( GameMap *pMap )
{
	m_pMap = pMap;
}

void Role::Render()
{
	if ( m_RoleData.roleFA != NULL )
	{
		m_RoleData.roleFA->Render( m_RoleData.pos.x, m_RoleData.pos.y );
	}
}

void Role::_KeepRoleInScreenRange( Vec2D &pos )
{
	if ( pos.x <= 20.0f + 20.0f )
	{
		pos.x = 40.0f;
	}
	else
	{
		if ( pos.x >= 620.0f - 20.0f )
		{
			pos.x = 600.0f;
		}
	}

	if ( pos.y <= 40.0f + 20.0f )
	{
		pos.y = 60.0f;
	}
	else
	{
		if( pos.y >= 520.0f + 40.0f - 20.0f )
		{
			pos.y = 540.0f;
		}
	}
}

bool Role::_IsHitZhangAiWu_Left()
{
	if( m_pMap->IsHitZhangAiWu( (int)((m_RoleData.rect.top-40.0f)/40.0f), 
								(int)((m_RoleData.rect.left-20.0f)/40.0f)) ||
		m_pMap->IsHitZhangAiWu( (int)((m_RoleData.rect.bottom-40.0f)/40.0f), 
								(int)((m_RoleData.rect.left-20.0f)/40.0f)) )
	{
		return true;
	}

	return false;
}

bool Role::_IsHitZhangAiWu_Right()
{
	if( m_pMap->IsHitZhangAiWu( (int)((m_RoleData.rect.top-40.0f)/40.0f), 
								(int)((m_RoleData.rect.right-20.0f)/40.0f)) ||
		m_pMap->IsHitZhangAiWu( (int)((m_RoleData.rect.bottom-40.0f)/40.0f), 
								(int)((m_RoleData.rect.right-20.0f)/40.0f)) )
	{
		return true;
	}

	return false;
}

bool Role::_IsHitZhangAiWu_Top()
{
	if( m_pMap->IsHitZhangAiWu( (int)((m_RoleData.rect.top-40.0f)/40.0f), 
								(int)((m_RoleData.rect.left-20.0f)/40.0f)) ||
		m_pMap->IsHitZhangAiWu( (int)((m_RoleData.rect.top-40.0f)/40.0f), 
								(int)((m_RoleData.rect.right-20.0f)/40.0f)) )
	{
		return true;
	}

	return false;
}

bool Role::_IsHitZhangAiWu_Bottom()
{
	if( m_pMap->IsHitZhangAiWu( (int)((m_RoleData.rect.bottom-40.0f)/40.0f), 
								(int)((m_RoleData.rect.left-20.0f)/40.0f)) ||
		m_pMap->IsHitZhangAiWu( (int)((m_RoleData.rect.bottom-40.0f)/40.0f), 
								(int)((m_RoleData.rect.right-20.0f)/40.0f)) )
	{
		return true;
	}

	return false;
}

void Role::_PathAdjust_VertiMove( const Vec2D &tempPos )
{
	if ( ((int)(m_RoleData.rect.left - 20.0f)%40) > 40-PATH_ADJUST_RANGE )
	{
		m_RoleData.pos.x = (int)((tempPos.x - 40.0f)/40.0f + 1.0f)*40.0f + 40.0f;
	}
	else
	{
		if ( ((int)(m_RoleData.rect.right - 20.0f)%40) < PATH_ADJUST_RANGE )
		{
			m_RoleData.pos.x = (int)((tempPos.x - 40.0f)/40.0f)*40.0f + 40.0f;
		}
	}
}

void Role::_PathAdjust_HorziMove( const Vec2D &tempPos )
{
	if ( ((int)(m_RoleData.rect.top - 40.0f)%40) > 40-PATH_ADJUST_RANGE )
	{
		m_RoleData.pos.y = (int)((tempPos.y - 60.0f)/40.0f + 1.0f)*40.0f + 60.0f;
	}
	else
	{
		if ( ((int)(m_RoleData.rect.bottom - 40.0f)%40) < PATH_ADJUST_RANGE )
		{
			m_RoleData.pos.y = (int)((tempPos.y - 60.0f)/40.0f)*40.0f + 60.0f;
		}
	}
}