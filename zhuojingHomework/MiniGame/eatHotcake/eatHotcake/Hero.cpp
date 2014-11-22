#include ".\hero.h"

Hero::Hero( PTEXTURE tex, bool isMask, COLORREF maskColor )
: BaseObject( tex, isMask, maskColor )
{
}

void Hero::Update()
{
	if ( isHitBorder() )
	{
	}

	_ProcessInput();
}

void Hero::_ProcessInput()
{
	if ( pEngine->KeyPress( 'A' ) )
	{
		m_Pos.x -= pEngine->Time_GetFrameTime()*100.0f;
	}
	else
	if ( pEngine->KeyPress( 'D' ) )
	{
		m_Pos.x += pEngine->Time_GetFrameTime()*100.0f;
	}
}

