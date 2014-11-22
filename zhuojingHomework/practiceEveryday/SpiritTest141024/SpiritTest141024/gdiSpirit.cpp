#include "StdAfx.h"

gdiSpirit::gdiSpirit( TCHAR *filename, int blockSizeX, int blocksizeY, COLORREF maskColor )
:	m_BlockSizeX( blockSizeX ), m_BlockSizeY( blocksizeY ),
	m_CurSpiRenderIndex( -1 ), m_CurSpiRenderY( -1 ),
	m_MaskColor( maskColor )
{
	m_hSpibmp = (HBITMAP)LoadImage( NULL, filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	m_hSpidc = CreateCompatibleDC( NULL );
	SelectObject( m_hSpidc, m_hSpibmp );

	BITMAP bmpInfo;
	GetObject( m_hSpibmp, sizeof( BITMAP ), &bmpInfo );

	m_BlockNumX = bmpInfo.bmWidth/m_BlockSizeX;
	m_BlockNumY = bmpInfo.bmHeight/m_BlockSizeY;

	m_BlockNumTotal = m_BlockNumX*m_BlockNumY;
}

gdiSpirit::~gdiSpirit(void)
{
	DeleteObject( m_hSpidc );
	DeleteObject( m_hSpibmp );
}

void gdiSpirit::render( const HDC &hdc, int x, int y )
{
	
	TransparentBlt( hdc, (int)x, (int)y, m_BlockSizeX, m_BlockSizeY,m_hSpidc, 
					(m_CurSpiRenderIndex%m_BlockNumY)*m_BlockSizeX, 
					(m_CurSpiRenderIndex/m_BlockNumY)*m_BlockSizeY, 
					m_BlockSizeX, m_BlockSizeY, m_MaskColor );

	++m_CurSpiRenderIndex;
	if ( m_CurSpiRenderIndex > m_EndIndex )
	{
		m_CurSpiRenderIndex = m_StartIndex;
	}
}
