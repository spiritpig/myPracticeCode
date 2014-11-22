#include ".\egeuiobject.h"

egeUiObject::egeUiObject( char *pName, int id, UI_TYPE uType, 						 
						  int x, int y, egeUiObject *pParent /* = NULL */ )
: m_pName( NULL ), m_pParent( pParent ),
  m_Id( id ), m_UIType( uType ), isFocus( false )
{
	m_pEngine = Engine_Create(NULL);
	if ( pName != NULL )
	{
		m_NameCapacity = strlen( pName )+1;
		m_pName = new char[m_NameCapacity];
		strcpy( m_pName, pName );
	}

	m_Id = id;
	m_UIType = uType;

	m_Pos.x = x;
	m_Pos.y = y;
	if( m_pParent )
	{
		m_RealPos.x = m_pParent->m_Pos.x + x;
		m_RealPos.y = m_pParent->m_Pos.y + y;
		m_pParent->AddChild( this );
	}
	else
	{
		m_RealPos.x = x;
		m_RealPos.y = y;
	}

	m_HotSpotRateX = 0.5f;
	m_HotSpotRateY = 0.5f;

	m_pChildList.clear();
}

egeUiObject::~egeUiObject(void)
{
	char buffer[1024];

	sprintf( buffer, "删除%s的uiobject", this->GetText() );
	MessageBox( 0, buffer, 0, 0 );

	if( !m_pChildList.empty() )
	{
		for ( m_pChildListIter = m_pChildList.begin();
			m_pChildListIter != m_pChildList.end();
			++m_pChildListIter )
		{
			sprintf( buffer, "%s 的 Child: %s", this->GetText(),(*m_pChildListIter)->GetText() );
			MessageBox( 0, buffer,  0, 0 );

			SAFE_DELETE( *m_pChildListIter );
		}
		m_pChildList.clear();
	}

	sprintf( buffer, "%s删除完成!", this->GetText() );
	MessageBox( 0, buffer, 0, 0 );

	SAFE_DELETE( m_pName );
	Engine_Release();
}

egeUiObject* egeUiObject::getChildUiById( int id )
{
	egeUiObject *tempRet = NULL;
	if( !m_pChildList.empty() )
	{
		for ( m_pChildListIter = m_pChildList.begin(); 
			m_pChildListIter != m_pChildList.end();
			++m_pChildListIter )
		{
			if ( (*m_pChildListIter)->GetId() == id )
			{
				return *m_pChildListIter;
			}
			else
			{
				tempRet = (*m_pChildListIter)->getChildUiById( id );
				if ( tempRet != NULL )
				{
					return tempRet;
				}
			}
		}
	}

	return NULL;
}

void egeUiObject::SetText( const char *text )
{
	static size_t tempSize;
	if ( text != NULL )
	{
		tempSize = strlen(text);
		// 保证分配的空间足够多
		if( m_NameCapacity <= tempSize )
		{
			SAFE_DELETE(m_pName);
			m_NameCapacity = tempSize+1;
			m_pName = new char[m_NameCapacity];
		}
		strcpy( m_pName, text );
	}
}

void egeUiObject::SetPos( int x, int y )
{
	if( m_pParent )
	{
		m_RealPos.x = m_pParent->m_RealPos.x + x;
		m_RealPos.y = m_pParent->m_RealPos.y + y;
	}
	else
	{
		m_RealPos.x = x;
		m_RealPos.y = y;
	}

	m_Pos.x = x;
	m_Pos.y = y;
}

void egeUiObject::SetHotSpot( float ratex, float ratey )
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

void egeUiObject::AddChild( egeUiObject *child )
{
	child->SetParent( this );
	m_pChildList.push_back( child );
}

bool egeUiObject::isMouseIntersectObject()
{
	POINT pt;
	m_pEngine->GetCursorPos( pt );
	pt.x -= m_RealPos.x - (long)(m_OuterRect.right*m_HotSpotRateX);
	pt.y -= m_RealPos.y - (long)(m_OuterRect.bottom*m_HotSpotRateY);

	if( PtInRect( &m_OuterRect, pt ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void egeUiObject::UpdateFromParent()
{
	if( m_pParent )  
	{
		m_RealPos.x = m_pParent->m_RealPos.x + m_Pos.x;
		m_RealPos.y = m_pParent->m_RealPos.y + m_Pos.y;
	}
}

void egeUiObject::RenderAllChild()
{
	if( !m_pChildList.empty() )
	{
		for ( m_pChildListIter = m_pChildList.begin();
			m_pChildListIter != m_pChildList.end(); 
			++m_pChildListIter )
		{
			(*m_pChildListIter)->Render();
		}
	}
}

void egeUiObject::UpdateChild()
{	
	if( !m_pChildList.empty() )
	{
		for ( m_pChildListIter = m_pChildList.begin();
			m_pChildListIter != m_pChildList.end();
			++m_pChildListIter )
		{
			(*m_pChildListIter)->Update();
		}
	}
}

void* egeUiObject::operator new( size_t size )
{
	return malloc( size );
}

void* egeUiObject::operator new[]( size_t size )
{
	return malloc( size );
}

void egeUiObject::operator delete( void* p )
{
	free(p);
}

void egeUiObject::operator delete[]( void* p )
{
	free(p);
}

