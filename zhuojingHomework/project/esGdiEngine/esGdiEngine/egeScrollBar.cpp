#include ".\egescrollbar.h"

egeUiScrollBar::egeUiScrollBar( char *pName, int id, int x, int y, int width, int height, 
							   float scrollPercentPerClick, egeUiObject *pParent /*= NULL */ )
: egeUiObject( pName, id, UT_SCROLLBAR, x, y, pParent )
{
	m_LeftBtn = new egeUiButton( "leftBtn", id*id, x, y, height, height, NULL, NULL, NULL );
	m_LeftBtn->SetPos( x - width/2 + height/2, y );
	m_LeftBtn->SetFocus();

	m_RightBtn = new egeUiButton( "rightBtn", id*id+1, x, y, height, height, NULL, NULL, NULL );
	m_RightBtn->SetPos( x + width/2 - height/2, y );
	m_RightBtn->SetFocus();

	m_ScrollBtn = new egeUiButton( "scrollBtn", id*id+2, x, y, height, height, NULL, NULL, NULL );
	m_ScrollBtn->SetPos( x - width/2 + height/2 + height, y );
	m_ScrollBtn->SetFocus();

	m_bgSprite = new egeSprite( NULL, x, y, width, height, false );
	m_bgSprite->setTextureRect( x - width/2 + height, y - height/2,
		x + width/2 - height, y + height/2 );

	SetPos( x, y );
	m_OuterRect.left = 0;
	m_OuterRect.top = 0;
	m_OuterRect.right = width;
	m_OuterRect.bottom = height;

	m_scrollPercentPerClick = scrollPercentPerClick;
	m_scrollMoveLen = m_OuterRect.right-m_OuterRect.bottom*3;
	m_scrollMoveStartX = x - m_OuterRect.right/2 + m_OuterRect.bottom + m_OuterRect.bottom/2;
	m_rate = 0.0f;
}

egeUiScrollBar::~egeUiScrollBar()
{
	SAFE_DELETE( m_bgSprite );
	SAFE_DELETE( m_ScrollBtn );
	SAFE_DELETE( m_RightBtn );
	SAFE_DELETE( m_LeftBtn );
}

void egeUiScrollBar::Update()
{
	m_LeftBtn->Update();
	m_RightBtn->Update();
	m_ScrollBtn->Update();

	static POINT prevMousePos, curMousePos;
	static bool needMove = false;

	// 分别检测左按钮、右按钮和中间滚动按钮是否按下
	// 以及是否点击了背景精灵的某个位置
	if( m_LeftBtn->IsClicked() || m_LeftBtn->IsPress() )
	{
		m_rate -= m_scrollPercentPerClick;
		m_rate = m_rate < 0.0f ? 0.0f : m_rate;
		m_ScrollBtn->SetPos( (int)(m_scrollMoveStartX + m_rate*m_scrollMoveLen),
				m_ScrollBtn->GetRealPos().y );
	}
	else
	if( m_RightBtn->IsClicked() || m_RightBtn->IsPress())
	{
		m_rate += m_scrollPercentPerClick;
		m_rate = m_rate > 1.0f ? 1.0f : m_rate;
		m_ScrollBtn->SetPos( (int)(m_scrollMoveStartX + m_rate*m_scrollMoveLen),
				m_ScrollBtn->GetRealPos().y );
	}
	else
	{
		if( m_ScrollBtn->IsPress() && !needMove )
		{
			needMove = true;
			m_pEngine->GetCursorPos( prevMousePos );
		}
		else
		if( m_pEngine->KeyDown( VK_LBUTTON ) )
		{
			m_pEngine->GetCursorPos( curMousePos );
			// 为了使滚轴的可点击范围，为整条黑线范围。
			if( curMousePos.x >= m_scrollMoveStartX-m_OuterRect.bottom/2 &&
				curMousePos.x <= m_scrollMoveStartX + m_scrollMoveLen+m_OuterRect.bottom/2 &&
				curMousePos.y >= m_RealPos.y - m_OuterRect.bottom &&
				curMousePos.y <= m_RealPos.y + m_OuterRect.bottom  )
			{
				// 修正当前鼠标位置，让其保持在[滚轴按钮的移动范围]
				if ( curMousePos.x < m_scrollMoveStartX )
				{
					curMousePos.x = m_scrollMoveStartX;
				}
				else
				if( curMousePos.x > (m_scrollMoveStartX + m_scrollMoveLen) )
				{
					curMousePos.x = m_scrollMoveStartX + m_scrollMoveLen;
				}

				m_rate = (float)(curMousePos.x-m_scrollMoveStartX)/m_scrollMoveLen;
				m_ScrollBtn->SetPos( curMousePos.x, m_ScrollBtn->GetRealPos().y );
			}
		}
		else
		if( !m_pEngine->KeyPress( VK_LBUTTON ) ||
			curMousePos.y < m_RealPos.y - m_OuterRect.bottom ||
			curMousePos.y > m_RealPos.y + m_OuterRect.bottom ||
			curMousePos.x < m_scrollMoveStartX - m_OuterRect.bottom ||
			curMousePos.x > m_scrollMoveStartX + m_scrollMoveLen + m_OuterRect.bottom )
		{
			needMove = false;
		}
	}

	if( needMove )
	{
		static int tempScrollPosX;
		m_pEngine->GetCursorPos( curMousePos );

		// 改变滚动按钮的位置
		tempScrollPosX = m_ScrollBtn->GetRealPos().x + curMousePos.x - prevMousePos.x;
		if ( tempScrollPosX > m_scrollMoveStartX && 
			tempScrollPosX < (m_scrollMoveStartX + m_scrollMoveLen) )
		{
			m_rate = (float)(tempScrollPosX-m_scrollMoveStartX)/m_scrollMoveLen;
			m_ScrollBtn->SetPos( tempScrollPosX, m_ScrollBtn->GetRealPos().y );
		}

		prevMousePos = curMousePos;
	}
}

void egeUiScrollBar::Render()
{
	if( m_bgSprite->haveTexture() )
	{
		m_bgSprite->Render( m_RealPos.x, m_RealPos.y );
	}
	else
	{
		m_pEngine->DrawLine( (HPEN)GetStockObject( BLACK_PEN ), 
			m_scrollMoveStartX - m_OuterRect.bottom/2, m_RealPos.y, 
			m_scrollMoveStartX + m_scrollMoveLen + m_OuterRect.bottom, m_RealPos.y );
	}

	m_LeftBtn->Render();
	m_RightBtn->Render();
	m_ScrollBtn->Render();
}
