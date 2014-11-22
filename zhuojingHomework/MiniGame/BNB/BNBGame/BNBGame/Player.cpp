#include ".\player.h"

Player::Player(void)
{
	m_RoleData.maxSpeed = 20.0f;
}

Player::~Player(void)
{
	SAFE_DELETE( m_RoleData.roleFA );
	if( m_pRoleTex )
	{
		m_pEngine->Texture_Free( m_pRoleTex );
	}
}

void Player::Init( int row, int cel, GameMap *pMap )
{
	SAFE_DELETE( m_RoleData.roleFA );
	if( m_pRoleTex )
	{
		m_pEngine->Texture_Free( m_pRoleTex );
	}

	m_pRoleTex = m_pEngine->Texture_Load( ".//Image//panpan.png" );
	m_RoleData.dir = D_NONE;
	m_RoleData.maxSpeed = 20.0f;
	m_RoleData.speed = 100.0f;
	m_RoleData.roleFA = new SggeFrameAnimat( m_pRoleTex, 0, 5, 0, 0, 50.0f, 60.0f );
	m_RoleData.roleFA->SetMode( FRAMEANIM_FWD | FRAMEANIM_LOOP | FRAMEANIM_NOPINGPONG );
	m_RoleData.roleFA->SetFrameRange( 5, 9 );
	m_RoleData.roleFA->SetFrame( 5 );
	m_RoleData.roleFA->SetHotSpot( 26.0f, 42.0f );
	m_RoleState = RS_STAND;

	m_pMap = pMap;
	m_RoleData.pos.x = cel*BLOCK_SIZE + 40.0f;
	m_RoleData.pos.y = row*BLOCK_SIZE + 60.0f;
}

void Player::Update()
{
	// 处理按键输入
	_ProcessInput();

	static Vec2D tempPos( 0.0f, 0.0f );
	tempPos = m_RoleData.pos;
	// 更新角色数据
	if ( m_RoleState == RS_WALK )
	{
		switch( m_RoleData.dir )
		{
		case D_UP:
			{
				tempPos += m_RoleData.speed*DirUp*m_pEngine->Timer_GetDelta();

				_KeepRoleInScreenRange( tempPos );

				m_RoleData.rect.SetRect( tempPos.x - 19.0f,
					tempPos.y - 19.0f, tempPos.x + 18.0f, 
					tempPos.y + 18.0f );

				if ( !_IsHitZhangAiWu_Top() )
				{
					m_RoleData.pos = tempPos;
				}
				else
				{
					_PathAdjust_VertiMove( tempPos );
				}
			}
			break;

		case D_DOWN:
			{
				tempPos += m_RoleData.speed*DirDown*m_pEngine->Timer_GetDelta();

				_KeepRoleInScreenRange( tempPos );

				m_RoleData.rect.SetRect( tempPos.x - 19.0f,
					tempPos.y - 19.0f, tempPos.x + 18.0f, 
					tempPos.y + 18.0f );

				if ( !_IsHitZhangAiWu_Bottom() )
				{
					m_RoleData.pos = tempPos;
				}
				else
				{
					_PathAdjust_VertiMove( tempPos );
				}
			}
			break;

		case D_LEFT:
			{
				tempPos += m_RoleData.speed*DirLeft*m_pEngine->Timer_GetDelta();

				_KeepRoleInScreenRange( tempPos );

				m_RoleData.rect.SetRect( tempPos.x - 19.0f,
					tempPos.y - 19.0f, tempPos.x + 18.0f, 
					tempPos.y + 18.0f );

				if ( !_IsHitZhangAiWu_Left() )
				{
					m_RoleData.pos = tempPos;
				}
				else
				{
					_PathAdjust_HorziMove( tempPos );
				}
			}
			break;

		case D_RIGHT:
			{
				tempPos += m_RoleData.speed*DirRight*m_pEngine->Timer_GetDelta();

				_KeepRoleInScreenRange( tempPos );

				m_RoleData.rect.SetRect( tempPos.x - 19.0f,
					tempPos.y - 19.0f, tempPos.x + 18.0f, 
					tempPos.y + 18.0f );

				if ( !_IsHitZhangAiWu_Right() )
				{
					m_RoleData.pos = tempPos;
				}
				else
				{
					_PathAdjust_HorziMove( tempPos );
				}
			}
			break;
		}
		m_RoleData.roleFA->Update( m_pEngine->Timer_GetDelta() );
	}
}

void Player::_ProcessInput()
{
	bool isDirDown = false;
	// 控制角色移动
	if ( m_pEngine->Input_GetKeyState( SGGEK_W ) )
	{
		isDirDown = true;
		if( m_RoleData.dir != D_UP ||
			m_RoleState == RS_STAND )
		{
			m_RoleData.dir = D_UP;
			m_RoleState = RS_WALK;
			m_RoleData.roleFA->SetFrameRange( 0, 4 );
			m_RoleData.roleFA->Play();
		}
	}
	else
	{
		if( m_pEngine->Input_GetKeyState( SGGEK_S ) )
		{
			isDirDown = true;
			if( m_RoleData.dir != D_DOWN ||
				m_RoleState == RS_STAND )
			{
				m_RoleData.dir = D_DOWN;
				m_RoleState = RS_WALK;
				m_RoleData.roleFA->SetFrameRange( 5, 9 );
				m_RoleData.roleFA->Play();
			}
		}
		else
		{
			if( m_pEngine->Input_GetKeyState( SGGEK_A ) )
			{
				isDirDown = true;
				if( m_RoleData.dir != D_LEFT ||
					m_RoleState == RS_STAND )
				{
					m_RoleData.dir = D_LEFT;
					m_RoleState = RS_WALK;
					m_RoleData.roleFA->SetFrameRange( 10, 14 );
					m_RoleData.roleFA->Play();
				}
			}
			else
			{
				if( m_pEngine->Input_GetKeyState( SGGEK_D ) )
				{
					isDirDown = true;
					if( m_RoleData.dir != D_RIGHT ||
						m_RoleState == RS_STAND )
					{
						m_RoleData.dir = D_RIGHT;
						m_RoleState = RS_WALK;
						m_RoleData.roleFA->SetFrameRange( 15, 19 );
						m_RoleData.roleFA->Play();
					}
				}
				else
				if( !isDirDown )
				{
					m_RoleState = RS_STAND;
					m_RoleData.roleFA->Stop();
					switch ( m_RoleData.dir )
					{
					case D_UP:
						{
							m_RoleData.roleFA->SetFrame( 0 );
						}
						break;

					case D_DOWN:
						{
							m_RoleData.roleFA->SetFrame( 5 );
						}
						break;

					case D_LEFT:
						{
							m_RoleData.roleFA->SetFrame( 10 );
						}
						break;

					case D_RIGHT:
						{
							m_RoleData.roleFA->SetFrame( 15 );
						}
						break;
					}
				}
			}
		}
	}

	if ( m_pEngine->Input_GetKeyState( SGGEK_SPACE ) )
	{
		/////////////////////////////////////
		/////////////////////////////////////
	}


}

