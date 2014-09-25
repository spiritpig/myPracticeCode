#include "commonHeader.h"

autoTextureManager::autoTextureManager(void)
{
	m_pTexture = NULL;
	m_useCount = 0;
}

autoTextureManager::~autoTextureManager(void)
{
	SAFE_DELETE( m_pTexture );
}

void autoTextureManager::create( Sgge *pEngine, char *filename )
{
	if ( m_useCount <= 0 )
	{
		m_pTexture = pEngine->Texture_Load( filename );
	}
	++m_useCount;
}

void autoTextureManager::release( Sgge *pEngine )
{
	--m_useCount;
	if ( m_useCount <= 0 )
	{
		pEngine->Texture_Free( m_pTexture );
	}
}
