#include ".\BaseObject.h"

// 判断浮点数是否等于0
#define FLOAT_COMPARE_PRECISION 0.00001f
bool isFloatEqualToZero( float f )
{
	if( (f <= FLOAT_COMPARE_PRECISION) &&
		(f >= -FLOAT_COMPARE_PRECISION) )
	{
		return true;
	}

	return false;
}

BaseObject::BaseObject( PTEXTURE tex, bool isMask, COLORREF maskColor )
{
	pEngine = Engine_Create( NULL );
	m_Spr = new egeSprite( tex, isMask, maskColor );
	m_Spr->setHotSpot( 0.5f, 0.5f );

	m_OuterRect.left = 0;
	m_OuterRect.top = 0;
	m_OuterRect.right = m_Spr->getWidth();
	m_OuterRect.bottom = m_Spr->getHeight();

	m_Resistance = 1.0f;
}

BaseObject::~BaseObject(void)
{
	SAFE_DELETE( m_Spr ); 
	Engine_Release();
}

void BaseObject::setPos( const egeVec2D &newPos )
{
	m_Pos = newPos;
}

void BaseObject::setVec( const egeVec2D &newVec )
{
	m_Vec = newVec;
}

void BaseObject::setAccer( const egeVec2D &newAccer )
{
	m_Accer = newAccer;
}

void BaseObject::setResistance( float res )
{
	if( res > 1.0f )
	{
		m_Resistance = 1.0f;
	}
	else
	if( res < 0.0f )
	{
		m_Resistance = 0.0f;
	}
	else
	{
		m_Resistance = res;
	}
}

void BaseObject::setBorderRange( int left, int top, int right, int bottom )
{
	SetRect( &m_BorderRange, left, top, right, bottom );
}

const egeVec2D& BaseObject::getPos() const
{
	return m_Pos;
}

const egeVec2D& BaseObject::getVec() const
{
	return m_Vec;
}

const egeVec2D& BaseObject::getAccer() const
{
	return m_Accer;
}

float BaseObject::getResistance() const
{
	return m_Resistance;
}

const RECT& BaseObject::getBorderRange() const
{
	return m_BorderRange;
}

void BaseObject::Render()
{
	m_Spr->Render( (int)m_Pos.x, (int)m_Pos.y );
}

void BaseObject::Update()
{
	onHitBorder();

	m_Pos += m_Vec*pEngine->Time_GetFrameTime();
	m_Vec += m_Accer*pEngine->Time_GetFrameTime();
}

bool BaseObject::isHitObject( BaseObject *bo )
{
	if ( (abs( m_Pos.x - bo->m_Pos.x )*2 <= (m_OuterRect.right + bo->m_OuterRect.right)) && 
		 (abs( m_Pos.y - bo->m_Pos.y )*2 <= (m_OuterRect.bottom + bo->m_OuterRect.bottom)) )
	{
		return true;
	}

	return false;
}

void BaseObject::onHitObject( BaseObject *bo )
{
	static isHitBefore = false;
	static BaseObject *pTempBo  = bo;

	// 反人类的写法，不符合现实规律
	if ( isHitObject( bo ) )
	{
		if( pTempBo != bo || !isHitBefore )
		{
			m_Vec *= -m_Resistance;

			pTempBo = bo;
			isHitBefore = true;
		}
	}
	else
	{
		isHitBefore = false;
	}
}

BOOL BaseObject::isHitBorder()
{
	BOOL cs = CS_NONE;
	if( m_Pos.x <= m_BorderRange.left )
	{
		cs |= CS_HIT_LEFT;
	}
	else
	if( m_Pos.x >= m_BorderRange.right )
	{
		cs |= CS_HIT_RIGHT;
	}

	if( m_Pos.y <= m_BorderRange.top )
	{
		cs |= CS_HIT_TOP;
	}
	else
	if( m_Pos.y >= m_BorderRange.bottom ) 
	{
		cs |= CS_HIT_BOTTOM;
	}

	return cs;
}

void BaseObject::onHitBorder()
{
	BOOL cs = isHitBorder();

	if ( cs & CS_HIT_RIGHT )
	{ 
		m_Pos.x = (float)m_BorderRange.right;
		m_Vec.x *= -m_Resistance;
	}
	else
	if ( cs & CS_HIT_LEFT )
	{
		m_Pos.x = (float)m_BorderRange.left;
		m_Vec.x *= -m_Resistance;
	}

	if ( cs & CS_HIT_BOTTOM )
	{
		m_Pos.y = (float)m_BorderRange.bottom;
		m_Vec.y *= -m_Resistance;
	}
	else
	if( cs & CS_HIT_TOP )
	{
		m_Pos.y = (float)m_BorderRange.top;
		m_Vec.y *= -m_Resistance;
	}
}
