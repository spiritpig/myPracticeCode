#include "esGdiEngineAll.h"

#ifndef EGESPRITE
#define EGESPRITE

//////////////////////////////////////////////////////////////////////////
//	�����࣬��ͼ��������֧��ȫ͸��
//	��֧��bmpλͼ
//////////////////////////////////////////////////////////////////////////
class egeSprite
{
public:
	egeSprite(void);
	egeSprite( PTEXTURE tex, int u, int v, int width, int height,
			bool isMask = true, int maskColor = RGB( 0, 0, 0 ) );
	egeSprite( PTEXTURE tex, bool isMask = true, 
		int maskColor = RGB( 0, 0, 0 ) );
	~egeSprite(void);

	bool haveTexture()
	{
		return m_haveTexture;
	}

	//////////////////////////////////////////////////////////////////////////
	//	��ȡ����Ŀ��
	//////////////////////////////////////////////////////////////////////////
	int getWidth()
	{
		return m_Width;
	}
	int getHeight()
	{
		return m_Height;
	}

	//////////////////////////////////////////////////////////////////////////
	//	���þ����״̬
	//////////////////////////////////////////////////////////////////////////
	void setImage( PTEXTURE tex, bool isMask, int maskColor );
	void setTextureRect( int left, int top, int width, int height )
	{
		m_U = left;
		m_V = top;
		m_Width = width;
		m_Height = height;
	}

	void setHotSpot( float ratex, float ratey );
	bool isIntersectSprite( const POINT &p );
	void Render( int x, int y );

private:
	esGdiEngine *pEngine;

	int m_U, m_V;
	int m_Width, m_Height;
	float m_HotSpotRateX, m_HotSpotRateY;
	bool m_isMask;
	COLORREF m_MaskColor;
	PESDC hSpriteDc;
	bool m_haveTexture;
};

#endif	// END EGESPRITE
