#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef EGESPRITE
#define EGESPRITE

#ifdef _DEBUG
class egeSprite
#else
class _declspec( dllexport ) egeSprite
#endif
{
public:
	egeSprite(void);
	egeSprite( PTEXTURE tex, int u, int v, int width, int height,
			bool isMask = true, int maskColor = RGB( 0, 0, 0 ) );
	~egeSprite(void);

	void setImage( PTEXTURE tex );
	void setTextureRect( int left, int top, 
						int width, int height )
	{
		m_U = left;
		m_V = top;
		m_Width = width;
		m_Height = height;
	}

	void setHotSpot( int x, int y )
	{
		m_HotSpotX = x;
		m_HotSpotY = y;
	}

	void Render( int x, int y );

private:
	esGdiEngine *pEngine;

	int m_U, m_V;
	int m_Width, m_Height;
	int m_HotSpotX, m_HotSpotY;
	bool m_isMask;
	COLORREF m_MaskColor;
	PESDC hSpriteDc;
};

#endif	// END EGESPRITE
