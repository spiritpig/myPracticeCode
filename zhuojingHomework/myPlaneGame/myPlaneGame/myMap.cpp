#include "commonHeader.h"

myMap::myMap(void)
{
	m_pSgge = SggeCreate( SGGE_VERSION );
	m_pMapBackTextrue = NULL;
	m_pMapBackSpr = NULL;
}

myMap::~myMap(void)
{
	SAFE_DELETE( m_pMapBackSpr );
	if( m_pMapBackTextrue != NULL )
	{
		m_pSgge->Texture_Free( m_pMapBackTextrue );
		m_pMapBackTextrue = NULL;
	}
	m_pSgge->Release();
}

void myMap::init()
{
	// 防止精灵和贴图曾经被使用过
	SAFE_DELETE( m_pMapBackSpr );
	if( m_pMapBackTextrue != NULL )
	{
		m_pSgge->Texture_Free( m_pMapBackTextrue );
		m_pMapBackTextrue = NULL;
	}

	//  读取背景
	m_pMapBackTextrue = m_pSgge->Texture_Load( "image/img_bg.jpg" );
	m_pMapBackSpr=new SggeSprite(m_pMapBackTextrue,0.0f,0.0f,
		(float)m_pSgge->Texture_GetWidth(m_pMapBackTextrue,true),
		(float)m_pSgge->Texture_GetHeight(m_pMapBackTextrue,true));

	m_bgPos1.x = 0.0f;
	m_bgPos1.y = 0.0f;

	m_bgPos2.x = 0.0f;
	m_bgPos2.y = (float)(-MAP_HEIGHT);

	m_mapLen = 0.0f;
}

void myMap::update()
{
	_processInput();

	static float step = 0.0f;
	step = PLANE_INIT_SPEED*m_pSgge->Timer_GetDelta();

	m_mapLen += step;
	m_bgPos1.y += step;
	m_bgPos2.y += step;

	if( m_bgPos2.y >= MAP_HEIGHT )
	{
		m_bgPos2.y = m_bgPos1.y - MAP_HEIGHT;
	}
	else
	if( m_bgPos1.y >= MAP_HEIGHT )
	{
		m_bgPos1.y = m_bgPos2.y - MAP_HEIGHT;
	}
}

void myMap::render()
{
	m_pMapBackSpr->Render( m_bgPos1.x, m_bgPos1.y );
	m_pMapBackSpr->Render( m_bgPos2.x, m_bgPos2.y );
}

void myMap::_processInput()
{

}

float myMap::getMapLen()
{
	return m_mapLen;
}
