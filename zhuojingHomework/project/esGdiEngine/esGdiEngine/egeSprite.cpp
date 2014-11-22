#include ".\egesprite.h"

egeSprite::egeSprite(void)
:	m_U( 0 ), m_V( 0 ), m_Width( 0 ), m_Height( 0 ), 
	m_HotSpotRateX( 0.0f ), m_HotSpotRateY( 0.0f ), 
	m_MaskColor( 0x00000000 ), m_isMask( false )
{
	hSpriteDc = (PESDC)CreateCompatibleDC( NULL );
	pEngine = Engine_Create( NULL );

	m_haveTexture = false;
}

egeSprite::egeSprite( PTEXTURE tex, int u, int v, 
					 int width, int height, 
					 bool isMask /*= true*/,
					 int maskColor /*= RGB( 0, 0, 0 )*/ )
:	m_HotSpotRateX( 0.0f ), m_HotSpotRateY( 0.0f )
{
	pEngine = Engine_Create( NULL );

	m_U = u;
	m_V = v;
	m_Width = width;
	m_Height = height;
	m_MaskColor = maskColor;
	m_isMask = isMask;

	hSpriteDc = (PESDC)CreateCompatibleDC( NULL );
	if( tex != NULL )
	{
		SelectObject( (HDC)hSpriteDc, (HBITMAP)tex );
		m_haveTexture = true;
	}
	else
	{
		m_haveTexture = false;
	}
}

egeSprite::egeSprite( PTEXTURE tex, bool isMask /*= true*/,
					  int maskColor /*= RGB( 0, 0, 0 )*/ )
: m_HotSpotRateX( 0.0f ), m_HotSpotRateY( 0.0f )
{
	pEngine = Engine_Create( NULL );

	m_U = 0;
	m_V = 0;
	m_Width = pEngine->Texture_GetWidth( tex );
	m_Height = pEngine->Texture_GetHeight( tex );
	m_MaskColor = maskColor;
	m_isMask = isMask;

	hSpriteDc = (PESDC)CreateCompatibleDC( NULL );
	if( tex != NULL )
	{
		SelectObject( (HDC)hSpriteDc, (HBITMAP)tex );
		m_haveTexture = true;
	}
	else
	{
		m_haveTexture = false;
	}
}

egeSprite::~egeSprite(void)
{
	if ( hSpriteDc )
	{
		DeleteDC( (HDC)hSpriteDc );
	}
	Engine_Release();
}

void egeSprite::setImage( PTEXTURE tex, bool isMask, int maskColor )
{
	SelectObject( (HDC)hSpriteDc, (HBITMAP)tex );
	m_Width = pEngine->Texture_GetWidth( tex );
	m_Height = pEngine->Texture_GetHeight( tex );

	m_isMask = isMask;
	m_MaskColor = maskColor;
	m_haveTexture = true;
}

void egeSprite::setHotSpot( float ratex, float ratey )
{
	if ( ratex < 0.0f )
	{
		m_HotSpotRateX = 0.0f;
	}
	else
	if( ratex > 1.0f )
	{
		m_HotSpotRateX = 1.0f;
	}
	else
	{
		m_HotSpotRateX = ratex;
	}

	if ( ratey < 0.0f )
	{
		m_HotSpotRateY = 0.0f;
	}
	else
	if( ratey > 1.0f )
	{
		m_HotSpotRateY = 1.0f;
	}
	else
	{
		m_HotSpotRateY = ratey;
	}
}


bool egeSprite::isIntersectSprite( const POINT &p )
{
	if ( GetPixel( (HDC)hSpriteDc, p.x, p.y ) != m_MaskColor )
	{
		return true;
	}
	return false;
}

void egeSprite::Render( int x, int y )
{
	// 根据是否需要背景透明，选择不同方案
	if ( m_isMask )
	{
		TransparentBlt( (HDC)pEngine->getScreenHandle(), (int)(x-m_Width*m_HotSpotRateX), 
			(int)(y-m_Height*m_HotSpotRateY), m_Width, m_Height, (HDC)hSpriteDc, m_U, m_V, 
			m_Width, m_Height, m_MaskColor );
	}
	else
	{
		BitBlt( (HDC)pEngine->getScreenHandle(), (int)(x-m_Width*m_HotSpotRateX), 
			(int)(y-m_Height*m_HotSpotRateY), m_Width, m_Height, (HDC)hSpriteDc, 
			m_U, m_V, SRCCOPY );
	}
}