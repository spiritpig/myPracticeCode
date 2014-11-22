#include ".\egeuiedit.h"

egeUiEdit::egeUiEdit(char *pName, int id, char *pContentFN, char *pBorderFN, 
				int x, int y, int width /* = 100 */, 
				int height /* = 100 */, int borderWidth /* = 10 */, 
				bool isContentMask /* = false */, COLORREF contentMaskColor /* = RGB */,
				bool isBorderMask /* = false */, COLORREF borderMaskColor /* = RGB( 0, 0, 0 ) */,
				egeUiObject *pParent /* = NULL */ )
: egeUiObject( pName, id, UT_EDIT, x, y, pParent ), m_isFlash( true )
{
	if( pBorderFN != NULL )
	{
		m_pBorderTex = m_pEngine->Texture_Load( pBorderFN );

		SetRect( &m_OuterRect, 0, 0, 
			m_pEngine->Texture_GetWidth( m_pBorderTex ),
			m_pEngine->Texture_GetHeight( m_pBorderTex ) );

		m_pBorderSprite = new egeSprite( m_pBorderTex , 0, 0,
			m_OuterRect.right, m_OuterRect.bottom,
			isBorderMask, borderMaskColor );
	}
	else
	{
		m_pBorderTex = NULL;
		m_pBorderSprite = NULL;

		m_OuterRect.right = width + borderWidth;
		m_OuterRect.bottom = height + borderWidth;
		m_OuterRect.left = 0;
		m_OuterRect.top = 0;
	}

	if( pContentFN != NULL )
	{
		m_pContentTex = m_pEngine->Texture_Load( pContentFN );

		SetRect( &m_drawTextRect, 0, 0, 
			m_pEngine->Texture_GetWidth( m_pContentTex ),
			m_pEngine->Texture_GetHeight( m_pContentTex ) );

		m_pContentSprite = new egeSprite( m_pContentTex, 0, 0, 
			m_drawTextRect.right, m_drawTextRect.bottom,
			isContentMask, contentMaskColor );
	}
	else
	{
		m_pContentTex = NULL;
		m_pContentSprite = NULL;
		
		m_drawTextRect.top = 0;
		m_drawTextRect.left = 0;
		m_drawTextRect.right = width;
		m_drawTextRect.bottom = height;
	}

	m_BorderWidth = borderWidth;
	m_cursorMaxFlashTime = 0.5f;
	m_cursorFlashTime = m_cursorMaxFlashTime;
	m_curLineStartPos = m_pName;
	m_Font = (HFONT)GetStockObject( SYSTEM_FONT );
	m_CharHeight = m_pEngine->CalcTextHeight( m_Font );
}

egeUiEdit::~egeUiEdit(void)
{
	SAFE_DELETE( m_pBorderSprite); 
	if ( m_pBorderTex )
	{
		m_pEngine->Texture_Free( m_pBorderTex );
	}

	SAFE_DELETE( m_pContentSprite ); 
	if ( m_pContentTex )
	{
		m_pEngine->Texture_Free( m_pContentTex );
	}
}

void egeUiEdit::setFont( const HFONT &font )
{
	m_Font = font;
	m_CharHeight = m_pEngine->CalcTextHeight( font );
}

void egeUiEdit::wndProc( PESWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	static char *pTemp;
	static size_t ol;
	ol = strlen( m_pName );
	
	switch( wParam )
	{
	case VK_RETURN:
		{
			ol = strlen( m_pName );
			pTemp = new char[ol+2];
			strcpy( pTemp, m_pName );

			SAFE_DELETE(m_pName);
			m_pName = pTemp;

			m_pName[ol] = '\n';
			m_pName[ol+1] = '\0';
		}
		break;

	case VK_BACK:
		{
			if( ol > 0 )
			{
				if( (m_pName[ol-1] & 0x80) == 0 )
				{
					m_pName[ol-1] = '\0';
				}
				else
				{
					m_pName[ol-2] = '\0';
				}
			}
		}
		break;

	default:
		{
			pTemp = new char[ol+2];

			strcpy( pTemp, m_pName );
			pTemp[ol] = (char)wParam;
			pTemp[ol+1] = '\0';

			SAFE_DELETE( m_pName );  
			m_pName = pTemp;
		}
		break;
	}
}

void egeUiEdit::Update()
{
	UpdateFromParent();
	if( !m_pChildList.empty() )
	{
		UpdateChild();
	}

	m_cursorFlashTime -= m_pEngine->Time_GetFrameTime();
	if ( m_cursorFlashTime <= 0.0f )
	{
		m_cursorFlashTime += m_cursorMaxFlashTime;
		m_isFlash = !m_isFlash;
	}
}

void egeUiEdit::Render()
{
	static RECT tempRect,drawTextRect;

	if ( m_pContentTex != NULL )
	{
		m_pContentSprite->Render( m_RealPos.x, m_RealPos.y );
	}
	else
	{
		SetRect( &tempRect, (int)(m_Pos.x - m_drawTextRect.right*m_HotSpotRateX),
			(int)(m_Pos.y - m_drawTextRect.bottom*m_HotSpotRateY),
			(int)(m_Pos.x + m_drawTextRect.right*(1-m_HotSpotRateX)),
			(int)(m_Pos.y + m_drawTextRect.bottom*(1-m_HotSpotRateY)) );

		m_pEngine->FillRect( (HBRUSH)GetStockObject( WHITE_BRUSH ), tempRect );
	}

	if ( m_pBorderTex != NULL )
	{
		m_pBorderSprite->Render( m_RealPos.x, m_RealPos.y );
	}
	else
	{
		// 左边框
		SetRect( &tempRect, 
			(int)(m_Pos.x - m_drawTextRect.right*m_HotSpotRateX - m_BorderWidth),
			(int)(m_Pos.y - m_drawTextRect.bottom*m_HotSpotRateY - m_BorderWidth),
			(int)(m_Pos.x - m_drawTextRect.right*m_HotSpotRateX),
			(int)(m_Pos.y + m_drawTextRect.bottom*(1-m_HotSpotRateY) + m_BorderWidth ));
		m_pEngine->FillRect( (HBRUSH)GetStockObject( DKGRAY_BRUSH ), tempRect );

		// 下边框
		SetRect( &tempRect, 
			(int)(m_Pos.x - m_drawTextRect.right*m_HotSpotRateX),
			(int)(m_Pos.y + m_drawTextRect.bottom*(1-m_HotSpotRateY)),
			(int)(m_Pos.x + m_drawTextRect.right*(1-m_HotSpotRateX) + m_BorderWidth),
		 	(int)(m_Pos.y + m_drawTextRect.bottom*(1-m_HotSpotRateY) + m_BorderWidth) );
		m_pEngine->FillRect( (HBRUSH)GetStockObject( DKGRAY_BRUSH ), tempRect );

		// 右边框
		SetRect( &tempRect, 
			(int)(m_Pos.x + m_drawTextRect.right*(1-m_HotSpotRateX) + m_BorderWidth),
			(int)(m_Pos.y + m_drawTextRect.bottom*(1-m_HotSpotRateY)),
			(int)(m_Pos.x + m_drawTextRect.right*(1-m_HotSpotRateX)),
			(int)(m_Pos.y - m_drawTextRect.bottom*m_HotSpotRateY - m_BorderWidth) );
		m_pEngine->FillRect( (HBRUSH)GetStockObject( DKGRAY_BRUSH ), tempRect );

		// 上边框
		SetRect( &tempRect, 
			(int)(m_Pos.x + m_drawTextRect.right*(1-m_HotSpotRateX)),
			(int)(m_Pos.y - m_drawTextRect.bottom*m_HotSpotRateY),
			(int)(m_Pos.x - m_drawTextRect.right*m_HotSpotRateX - m_BorderWidth),
			(int)(m_Pos.y - m_drawTextRect.bottom*m_HotSpotRateY - m_BorderWidth) );
		m_pEngine->FillRect( (HBRUSH)GetStockObject( DKGRAY_BRUSH ), tempRect );
	}

	SetRect( &drawTextRect, (int)(m_Pos.x - m_drawTextRect.right*m_HotSpotRateX),
		(int)(m_Pos.y - m_drawTextRect.bottom*m_HotSpotRateY),
		(int)(m_Pos.x + m_drawTextRect.right*(1-m_HotSpotRateX)),
		(int)(m_Pos.y + m_drawTextRect.bottom*(1-m_HotSpotRateY)) );

	// 自动换行
	static char *pTemp;
	static size_t nameSize;
	ZeroMemory( &tempRect, sizeof( RECT ) );
	m_pEngine->CalcRect( m_Font, m_pName, tempRect );
	if( (tempRect.right-tempRect.left) > (drawTextRect.right-drawTextRect.left) )
	{
		nameSize = strlen( m_pName );
		pTemp = new char[nameSize+2];
		strcpy( pTemp, m_pName );

		SAFE_DELETE(m_pName);
		m_pName = pTemp;
		
		// 分别处理unicode码和ascii码
		if ( (m_pName[nameSize-1] & 0x80) == 0 )
		{
			m_pName[nameSize] = m_pName[nameSize-1];
			m_pName[nameSize-1] = '\n';
			m_pName[nameSize+1] = '\0';

			m_curLineStartPos = &m_pName[nameSize];
		}
		else
		{
			m_pName[nameSize] = m_pName[nameSize-1];
			m_pName[nameSize-1] = m_pName[nameSize-2];
			m_pName[nameSize-2] = '\n';
			m_pName[nameSize+1] = '\0';

			m_curLineStartPos = &m_pName[nameSize-1];
		}
	}

	m_pEngine->DrawText( m_Font, m_pName, drawTextRect,
		DT_LEFT | DT_TOP );

	// 光标一闪一闪的特效
	if( isFocus && m_isFlash )
	{
		nameSize = strlen( m_pName );
		if( nameSize > 0 )
		{
			int length = m_pEngine->CalcLastLineLength( m_Font, m_pName );
			m_pEngine->DrawLine( (HPEN)GetStockObject(BLACK_PEN), drawTextRect.left + length + 2, 
				drawTextRect.top+tempRect.bottom-tempRect.top-m_CharHeight,
				drawTextRect.left + length + 2, 
				drawTextRect.top+tempRect.bottom-tempRect.top );
		}
		else
		{
			m_pEngine->DrawLine( (HPEN)GetStockObject(BLACK_PEN), drawTextRect.left + 2, 
				drawTextRect.top,
				drawTextRect.left + 2, 
				drawTextRect.top+m_CharHeight );
		}
	}
}

