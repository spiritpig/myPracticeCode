#include ".\egeuibutton.h"

egeUiButton::egeUiButton(char *pName, int id, int x, int y, 
		int width /* = 100 */, int height /* = 100 */,
		char *pUpFN, char *pOnFN, char *pDownFN, 
		bool isUpMask /* = false */, COLORREF upMaskColor /* = RGB */,
		bool isOnMask /* = false */, COLORREF onMaskColor /* = RGB */,
		bool isDownMask /* = false */, COLORREF downMaskColor /* = RGB */,
		egeUiObject *pParent /* = NULL */)
: egeUiObject( pName, id, UT_BUTTON, x, y, pParent ),
  m_UpMaskColor( upMaskColor ), m_OnMaskColor( onMaskColor ), 
  m_DownMaskColor( downMaskColor ), m_isDown( false ), 
  m_isOn( false ), m_isUp( false ), m_isClicked( false ),
  m_isPress( false )
{
	if( pUpFN != NULL )
	{
		m_pUpTex = m_pEngine->Texture_Load( pUpFN );

		SetRect( &m_OuterRect, 0, 0, 
			m_pEngine->Texture_GetWidth( m_pUpTex ),
			m_pEngine->Texture_GetHeight( m_pUpTex ) );

		m_pUpSprite = new egeSprite( m_pUpTex, 0, 0, 
			m_OuterRect.right, m_OuterRect.bottom,
			isUpMask, upMaskColor );
	}
	else
	{
		m_pUpTex = NULL;
		m_OuterRect.right = width;
		m_OuterRect.bottom = height;
		m_OuterRect.left = 0;
		m_OuterRect.top = 0;

		m_pUpSprite = new egeSprite( m_pUpTex, 0, 0, 
			m_OuterRect.right, m_OuterRect.bottom, false);
	}

	if( pOnFN != NULL )
	{
		m_pOnTex = m_pEngine->Texture_Load( pOnFN );
		m_pOnSprite = new egeSprite( m_pOnTex, 0, 0, 
			m_pEngine->Texture_GetWidth( m_pOnTex ),
			m_pEngine->Texture_GetHeight( m_pOnTex ),
			isOnMask, onMaskColor );
	}
	else
	{
		m_pOnTex = NULL;
		m_pOnSprite = new egeSprite( m_pOnTex, 0, 0, 
			m_OuterRect.right, m_OuterRect.bottom, false);;
	}

	if ( pDownFN != NULL )
	{
		m_pDownTex = m_pEngine->Texture_Load( pDownFN );
		m_pDownSprite = new egeSprite( m_pDownTex, 0, 0, 
			m_pEngine->Texture_GetWidth( m_pDownTex ),
			m_pEngine->Texture_GetHeight( m_pDownTex ),
			isDownMask, downMaskColor );
	}
	else
	{
		m_pDownTex = NULL;
		m_pDownSprite = new egeSprite( m_pDownTex, 0, 0, 
			m_OuterRect.right, m_OuterRect.bottom, false);;
	}
}

egeUiButton::~egeUiButton(void)
{
	SAFE_DELETE( m_pDownSprite ); 
	if ( m_pDownTex )
	{
		m_pEngine->Texture_Free( m_pDownTex );
	}

	SAFE_DELETE( m_pOnSprite ); 
	if ( m_pOnTex )
	{
		m_pEngine->Texture_Free( m_pOnTex );
	}

	SAFE_DELETE( m_pUpSprite ); 
	if ( m_pUpTex )
	{
		m_pEngine->Texture_Free( m_pUpTex );
	}
}

void egeUiButton::SetUpTex( char *pUpFN, bool isUpMask /*= false*/, 
						   COLORREF upMaskColor /*= RGB( 0, 0, 0 ) */ )
{
	PTEXTURE tex = m_pEngine->Texture_Load( pUpFN );
	m_pUpSprite->setImage( tex, isUpMask, upMaskColor );
}

void egeUiButton::SetOnTex( char *pOnFN, bool isOnMask /*= false*/, 
						   COLORREF onMaskColor /*= RGB( 0, 0, 0 ) */ )
{
	PTEXTURE tex = m_pEngine->Texture_Load( pOnFN );
	m_pOnSprite->setImage( tex, isOnMask, onMaskColor );
}

void egeUiButton::SetDownTex( char *pDownFN, bool isDownMask /*= false*/, 
							 COLORREF downMaskColor /*= RGB( 0, 0, 0 )*/ )
{
	PTEXTURE tex = m_pEngine->Texture_Load( pDownFN );
	m_pOnSprite->setImage( tex, isDownMask, downMaskColor );
}

void egeUiButton::SetHotSpot( float ratex, float ratey )
{
	egeUiObject::SetHotSpot( ratex, ratey );
	if( m_pUpSprite != NULL )
	{
		m_pUpSprite->setHotSpot( ratex, ratey );
	}

	if( m_pOnSprite != NULL )
	{
		m_pOnSprite->setHotSpot( ratex, ratey );
	}
	if( m_pDownSprite != NULL )
	{
		m_pDownSprite->setHotSpot( ratex, ratey );
	}
}

bool egeUiButton::IsMouseIntersectObject()
{
	POINT pt;
	m_pEngine->GetCursorPos( pt );
	pt.x -= m_RealPos.x - (long)(m_OuterRect.right*m_HotSpotRateX);
	pt.y -= m_RealPos.y - (long)(m_OuterRect.bottom*m_HotSpotRateY);

	if( m_pUpSprite != NULL )
	{
		if ( PtInRect( &m_OuterRect, pt ) && 
			m_pUpSprite->isIntersectSprite( pt ) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if ( PtInRect( &m_OuterRect, pt ) )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void egeUiButton::Update()
{
	UpdateFromParent();

	m_isClicked = false;
	if ( isMouseIntersectObject() )
	{
		m_isOn = true;
	}
	else
	{
		m_isOn = false;
	}

	if ( m_pEngine->KeyDown( VK_LBUTTON ) && m_isOn )
	{
		m_isDown = true;
		m_isUp = false;
	}
	else
	if( m_pEngine->KeyUp( VK_LBUTTON ) && m_isOn )
	{
		if( m_isDown )
		{
			m_isClicked = true;
		}
		m_isDown = false;
		m_isUp = true;
		m_isPress = false;
	}
	// 此处是一个小优化， 当持续按下时，只需要保持
	// 为原来的状态即可。所以，可以不处理。
	// 当不再按钮上面时，必然，不是按下状态
	else
	if ( !m_isOn )
	{
		m_isDown = false;
		m_isPress = false;
	}
	else
	{
		if ( m_isDown && m_pEngine->KeyPress( VK_LBUTTON ) )
		{
			m_isPress = true;
		}
	}

}

void egeUiButton::Render()
{
	static RECT drawRect;
	SetRect( &drawRect, (int)(m_RealPos.x - m_OuterRect.right*m_HotSpotRateX), 
		(int)(m_RealPos.y - m_OuterRect.bottom*m_HotSpotRateY),
		(int)(m_RealPos.x + (1 - m_HotSpotRateX)*m_OuterRect.right),
		(int)(m_RealPos.y + (1 - m_HotSpotRateY)*m_OuterRect.bottom) );

	if ( m_isDown )
	{
		if ( m_pDownTex != NULL )
		{
			m_pDownSprite->Render( m_RealPos.x, m_RealPos.y );
		}
		else
		{
			m_pEngine->FillRect( (HBRUSH)GetStockObject( DKGRAY_BRUSH ), drawRect );

			// 按钮边框
			m_pEngine->DrawLine( (HPEN)GetStockObject( BLACK_PEN ), 
				drawRect.right, drawRect.top, drawRect.left, drawRect.top);
			m_pEngine->DrawLine( (HPEN)GetStockObject( BLACK_PEN ), 
				drawRect.left, drawRect.top, drawRect.left, drawRect.bottom );
			m_pEngine->DrawLine( (HPEN)GetStockObject( BLACK_PEN ), 
				drawRect.left, drawRect.bottom, drawRect.right, drawRect.bottom );
			m_pEngine->DrawLine( (HPEN)GetStockObject( BLACK_PEN ), 
				drawRect.right, drawRect. bottom, drawRect.right, drawRect.top );
		}
	}
	else
	if( m_isOn )
	{
		if( m_pOnTex )
		{
			m_pOnSprite->Render( m_RealPos.x, m_RealPos.y );
		}
		else
		{
			m_pEngine->FillRect( (HBRUSH)GetStockObject( LTGRAY_BRUSH ), drawRect );

			// 按钮边框
			m_pEngine->DrawLine( (HPEN)GetStockObject( WHITE_PEN ), 
				drawRect.right, drawRect.top, drawRect.left, drawRect.top);
			m_pEngine->DrawLine( (HPEN)GetStockObject( WHITE_PEN ), 
				drawRect.left, drawRect.top, drawRect.left, drawRect.bottom );
			m_pEngine->DrawLine( (HPEN)GetStockObject( BLACK_PEN ), 
				drawRect.left, drawRect.bottom, drawRect.right, drawRect.bottom );
			m_pEngine->DrawLine( (HPEN)GetStockObject( BLACK_PEN ), 
				drawRect.right, drawRect. bottom, drawRect.right, drawRect.top );
		}
	}
	else
	{
		if( m_pUpTex)
		{
			m_pUpSprite->Render( m_RealPos.x, m_RealPos.y );
		}
		else
		{
			m_pEngine->FillRect( (HBRUSH)GetStockObject( GRAY_BRUSH ), drawRect );

			// 按钮边框
			m_pEngine->DrawLine( (HPEN)GetStockObject( WHITE_PEN ), 
				drawRect.right, drawRect.top, drawRect.left, drawRect.top);
			m_pEngine->DrawLine( (HPEN)GetStockObject( WHITE_PEN ), 
				drawRect.left, drawRect.top, drawRect.left, drawRect.bottom );
			m_pEngine->DrawLine( (HPEN)GetStockObject( BLACK_PEN ), 
				drawRect.left, drawRect.bottom, drawRect.right, drawRect.bottom );
			m_pEngine->DrawLine( (HPEN)GetStockObject( BLACK_PEN ), 
				drawRect.right, drawRect. bottom, drawRect.right, drawRect.top );
		}
	}
}

