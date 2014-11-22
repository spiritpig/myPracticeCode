#include ".\egeuistatic.h"


egeUiStatic::egeUiStatic( char *pName, int id, int x, int y, 
						 int width, int height, egeUiObject *pParent /*= NULL */ )
: egeUiObject( pName, id, UT_STATIC, x, y, pParent )
{
	m_OuterRect.left = 0;
	m_OuterRect.right = width;
	m_OuterRect.top = 0;
	m_OuterRect.bottom = height;

	m_pContentTex = NULL;
	m_pContentSprite = new egeSprite( NULL, 0, 0, 0, 0 );
}

egeUiStatic::egeUiStatic( int id, int x,int y, int width, int height, 
						  char *texFn, bool isMask, COLORREF maskColor, 
						  egeUiObject *pParent /* = NULL */)
: egeUiObject( NULL, id, UT_STATIC, x, y, pParent )
{
	if( texFn != NULL )
	{
		m_pContentTex = m_pEngine->Texture_Load( texFn );
		SetRect( &m_OuterRect, 0, 0, 
			m_pEngine->Texture_GetWidth( m_pContentTex ),
			m_pEngine->Texture_GetHeight( m_pContentTex ) );

		m_pContentSprite = new egeSprite( m_pContentTex , 0, 0, 
			m_OuterRect.right, m_OuterRect.bottom, isMask, maskColor );
	}
	else
	{
		SetRect( &m_OuterRect, 0, 0, width, height );

		m_pContentTex = NULL;
		m_pContentSprite = new egeSprite( NULL, 0, 0, m_OuterRect.right, 
			m_OuterRect.bottom, isMask, maskColor );
	}
}

egeUiStatic::~egeUiStatic(void)
{
	SAFE_DELETE( m_pContentSprite );
	if( m_pContentTex )
	{
		m_pEngine->Texture_Free( m_pContentTex );
	}
}

void egeUiStatic::Update()
{

}

void egeUiStatic::Render()
{
	static RECT drawRect;
	if ( m_pContentTex != NULL )
	{
		m_pContentSprite->Render( m_RealPos.x, m_RealPos.y );
	}
	else
	{
		drawRect.left = m_RealPos.x;
		drawRect.top = m_RealPos.y;
		drawRect.right = drawRect.left + m_OuterRect.right;
		drawRect.bottom = drawRect.top + m_OuterRect.bottom;

		m_pEngine->DrawText( m_textFont, m_pName, drawRect, DT_LEFT | DT_TOP );
	}
}
