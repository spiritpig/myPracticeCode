#include "commonHeader.h"

//////////////////////////////////////////////////////////////////////////
// 导导大作战
//////////////////////////////////////////////////////////////////////////

player::player(void)
{
	m_pSgge = SggeCreate( SGGE_VERSION );
	m_pPLTextrue = NULL;
	m_pPLSpr = NULL;

	m_pBLTextrue = NULL;
	m_pBLSpr = NULL;

	m_pDDTexture = NULL;
	m_pDDSpr = NULL;
}

player::~player(void)
{
	SAFE_DELETE( m_pDDSpr );
	if ( m_pDDTexture != NULL )
	{
		m_pSgge->Texture_Free( m_pDDTexture );
		m_pDDTexture = NULL;
	}

	SAFE_DELETE( m_pPLSpr );
	if( m_pPLTextrue != NULL )
	{
		m_pSgge->Texture_Free( m_pPLTextrue );
		m_pPLTextrue = NULL;
	}

	SAFE_DELETE( m_pBLSpr );
	if( m_pBLTextrue != NULL )
	{
		m_pSgge->Texture_Free( m_pBLTextrue );
		m_pBLTextrue = NULL;
	}

	m_pSgge->Release();
}

void player::init()
{
	// player数据初始化
	SAFE_DELETE( m_pPLSpr );
	if( m_pPLTextrue != NULL )
	{
		m_pSgge->Texture_Free( m_pPLTextrue );
		m_pPLTextrue = NULL;
	}

	m_pPLTextrue = m_pSgge->Texture_Load( "image/headLD.png" );
	m_pPLSpr = new SggeSprite( m_pPLTextrue ,0.0f,0.0f,
		(float)m_pSgge->Texture_GetWidth(m_pPLTextrue,true),
		(float)m_pSgge->Texture_GetHeight(m_pPLTextrue,true));
	m_pPLSpr->SetHotSpot(m_pSgge->Texture_GetWidth(m_pPLTextrue,true)/2.0f,
		m_pSgge->Texture_GetHeight(m_pPLTextrue,true)/2.0f);

	m_plData.pos.x = (float)MAP_WIDTH/2 + 15.0f;
	m_plData.pos.y = (float)MAP_HEIGHT - 200.0f;
	m_plData.initSpeed = PLANE_INIT_SPEED;
	m_plData.selfSpeed = 200.0f;
	m_plData.dir.x = 0.0f;
	m_plData.dir.y = -1.0f;
	m_plHeadScalePercent = PLANE_HEAD_SCALE_PERCENT;


	// bullet数据初始化
	SAFE_DELETE( m_pBLSpr );
	if( m_pBLTextrue != NULL )
	{
		m_pSgge->Texture_Free( m_pBLTextrue );
		m_pBLTextrue = NULL;
	}

	m_pBLTextrue = m_pSgge->Texture_Load( "image/bulletWater.png" );
	m_pBLSpr = new SggeSprite( m_pBLTextrue ,0.0f,0.0f,
		(float)m_pSgge->Texture_GetWidth(m_pBLTextrue,true),
		(float)m_pSgge->Texture_GetHeight(m_pBLTextrue,true));
	m_pBLSpr->SetHotSpot(m_pSgge->Texture_GetWidth(m_pBLTextrue,true)/2.0f,
		m_pSgge->Texture_GetHeight(m_pBLTextrue,true)/2.0f);
	m_pBLSpr->SetFlip( false, true, true );

	for ( int i=0; i<BULLET_ROW_NUM; ++i )
	{
		for ( int j=0; j<BULLET_CEL_NUM; ++j )
		{
			m_blData[i][j].dir = m_plData.dir;
			m_blData[i][j].angle = 0.0f;
			m_blData[i][j].pos = m_plData.pos + m_blPosOffset;
			m_blData[i][j].selfSpeed = BULLET_SPEED;
			m_blData[i][j].initSpeed = m_plData.initSpeed;
			m_blData[i][j].isUsed = false;
		}
	}

	m_blSpaceTime = BULLET_SPACE_TIME;
	m_blPosOffset.x = BULLET_POS_OFFSET_X;
	m_blPosOffset.y = BULLET_POS_OFFSET_Y;
	m_blScalePercent = BULLET_SCALE_PERCENT;


	// 导弹数据初始化
	SAFE_DELETE( m_pDDSpr );
	if ( m_pDDTexture != NULL )
	{
		m_pSgge->Texture_Free( m_pDDTexture );
		m_pDDTexture = NULL;
	}

	m_pDDTexture = m_pSgge->Texture_Load( "image/coin.png" );
	m_pDDSpr = new SggeSprite( m_pDDTexture ,0.0f,0.0f,
		(float)m_pSgge->Texture_GetWidth(m_pDDTexture,true),
		(float)m_pSgge->Texture_GetHeight(m_pDDTexture,true));
	m_pDDSpr->SetHotSpot(m_pSgge->Texture_GetWidth(m_pDDTexture,true)/2.0f,
		m_pSgge->Texture_GetHeight(m_pDDTexture,true)/2.0f);

	for ( int i=0; i<MAX_DAODAN_NUM; ++i )
	{
		m_ddData[i].pos = m_plData.pos;
		m_ddData[i].dir = m_plData.dir;
		m_ddData[i].angle = (DAODAN_ANGLE_START + DAODAN_ANGLE_OFFSET*i) * ANGLE;
		m_ddData[i].initSpeed = m_plData.initSpeed;
		m_ddData[i].selfSpeed = DAODAN_SELF_SPEED;
		m_ddData[i].isUsed = false;
	}
	m_ddScalePercent = DAODAN_SCALE_PERCENT;
	m_ddSpaceTime = DAODAN_SPACE_TIME;
}

void player::update( float mapLen )
{
	// 更新玩家由于地图运动所造成的移动
	m_plData.pos.y -= m_plData.initSpeed*m_pSgge->Timer_GetDelta();


	// 更新子弹由于地图运动所造成的移动
	for ( int i=0; i<BULLET_ROW_NUM; ++i )
	{
		for ( int j=0; j<BULLET_CEL_NUM; ++j )
		{
			if( m_blData[i][j].isUsed )
			{
				m_blData[i][j].pos.y -= m_blData[i][j].initSpeed*m_pSgge->Timer_GetDelta();
			}
		}
	}

	// 更新导弹由于地图运动所造成的移动
	for( int i=0; i<MAX_DAODAN_NUM; ++i )
	{
		m_ddData[i].pos.y -= m_ddData[i].initSpeed*m_pSgge->Timer_GetDelta();
	}

	_processInput( mapLen );

	// 更新子弹的实际位置
	for ( int i=0; i<BULLET_ROW_NUM; ++i )
	{
		for ( int j=0; j<BULLET_CEL_NUM; ++j )
		{
			if( m_blData[i][j].isUsed )
			{
				m_blData[i][j].pos += m_blData[i][j].dir.roration( m_blData
					[i][j].angle )*m_blData[i][j].selfSpeed*m_pSgge->Timer_GetDelta();

				_adjustBulletPos( m_blData[i][j], mapLen );
			}
		}
	}

	// 更新导弹的实际位置
	for( int i=0; i<MAX_DAODAN_NUM; ++i )
	{
		m_ddData[i].pos += m_ddData[i].dir.roration( m_ddData[i].angle )
			*m_ddData[i].selfSpeed*m_pSgge->Timer_GetDelta();

		_adjustDaodanPos( m_ddData[i], mapLen );
	}

	m_blSpaceTime -= m_pSgge->Timer_GetDelta();
	//m_ddSpaceTime -= m_pSgge->Timer_GetDelta();
}

void player::render( float mapLen )
{
	// 绘制玩家飞机
	m_pPLSpr->RenderEx( m_plData.pos.x, m_plData.pos.y + mapLen, ANGLE*180, 
						m_plHeadScalePercent, m_plHeadScalePercent);

	// 绘制子弹
	for ( int i=0; i<BULLET_ROW_NUM; ++i )
	{
		for ( int j=0; j<BULLET_CEL_NUM; ++j )
		{
			if( m_blData[i][j].isUsed )
			{
				m_pBLSpr->RenderEx( m_blData[i][j].pos.x, m_blData[i][j].pos.y + mapLen,
					0.0f, m_blScalePercent, m_blScalePercent );
			}
		}
	}

	// 绘制导弹
	for ( int i=0; i<MAX_DAODAN_NUM; ++i )
	{
		if( m_ddData[i].isUsed )
		{
			m_pDDSpr->RenderEx( m_ddData[i].pos.x, m_ddData[i].pos.y + mapLen, 
					0.0f, m_ddScalePercent, m_ddScalePercent );
		}
	}
}

void player::_processInput( float mapLen )
{
	// 飞机的上下
	float curBorder = 0.0f;
	if( m_pSgge->Input_GetKeyState( SGGEK_W ) )
	{
		m_plData.pos += m_plData.dir*m_plData.selfSpeed
			*m_pSgge->Timer_GetDelta();

		curBorder = (m_pPLSpr->GetHeight()*m_plHeadScalePercent)/2.0f - mapLen;
		if( m_plData.pos.y <= curBorder )
		{
			m_plData.pos.y = curBorder;
		}
	}
	if( m_pSgge->Input_GetKeyState( SGGEK_S ) )
	{
		m_plData.pos -= m_plData.dir*m_plData.selfSpeed
			*m_pSgge->Timer_GetDelta();

		curBorder = MAP_HEIGHT - (m_pPLSpr->GetHeight()*m_plHeadScalePercent)/1.5f - mapLen;
		if( m_plData.pos.y >=  curBorder)
		{
			m_plData.pos.y = curBorder;
		}
	}

	// 飞机的左右
	if( m_pSgge->Input_GetKeyState( SGGEK_A ) )
	{
		m_plData.pos += m_plData.dir.roration( ANGLE*270 )
			*m_plData.selfSpeed*m_pSgge->Timer_GetDelta();

		curBorder = (m_pPLSpr->GetWidth()*m_plHeadScalePercent)/2.0f;
		if( m_plData.pos.x <= curBorder )
		{
			m_plData.pos.x = curBorder;
		}
	}
	else
	if( m_pSgge->Input_GetKeyState( SGGEK_D ) )
	{
		m_plData.pos += m_plData.dir.roration( ANGLE*90 )
			*m_plData.selfSpeed*m_pSgge->Timer_GetDelta();

		curBorder = MAP_WIDTH - (m_pPLSpr->GetWidth()*m_plHeadScalePercent)/2.0f;
		if( m_plData.pos.x >= curBorder )
		{
			m_plData.pos.x = curBorder;
		}
	}

	if( m_pSgge->Input_GetKeyState( SGGEK_J ) && 
		isFloatLowerEqualThanZero( m_blSpaceTime ) )
	{
		for ( int i=0; i<BULLET_ROW_NUM; ++i )
		{
			for ( int j=0; j<BULLET_CEL_NUM; ++j )
			{
				if( !m_blData[i][j].isUsed )
				{
					m_blData[i][j].isUsed = true;
					m_blData[i][j].pos = m_plData.pos + m_blPosOffset;
					break;
				}
			}
		}

		m_blSpaceTime = BULLET_SPACE_TIME;
	}
	if( m_pSgge->Input_GetKeyState( SGGEK_K ) )  
	{
		// 如果有未飞完的导弹，则不发射新的导弹
		int count = 0;
		for ( int i=0; i<MAX_DAODAN_NUM; ++i )
		{
			if( m_ddData[i].isUsed == false )
			{
				++count;
			}
		}

		if( count >= MAX_DAODAN_NUM )
		{
			for ( int i=0; i<MAX_DAODAN_NUM; ++i )
			{
				m_ddData[i].isUsed = true;
				m_ddData[i].pos = m_plData.pos;
			}
		}
	}
}

void player::_adjustDaodanPos( daodanState &ddState, float mapLen )
{
	float curBorder = 0.0f;

	curBorder = -mapLen;
	if( ddState.pos.y <= curBorder )
	{
		ddState.isUsed = false;
	}

	curBorder = 0.0f;
	if( ddState.pos.x <= curBorder )
	{
		ddState.isUsed = false;
		return;
	}
	curBorder = MAP_WIDTH;
	if( ddState.pos.x >= curBorder )
	{
		ddState.isUsed = false;
		return;
	}
}


void player::_adjustBulletPos( bulletState &blState, float mapLen )
{
	float curBorder = 0.0f;

	curBorder = -mapLen;
	if( blState.pos.y <= curBorder )
	{
		blState.isUsed = false;
	}

	curBorder = 0.0f;
	if( blState.pos.x <= curBorder )
	{
		blState.isUsed = false;
		return;
	}
	curBorder = MAP_WIDTH;
	if( blState.pos.x >= curBorder )
	{
		blState.isUsed = false;
		return;
	}
}
