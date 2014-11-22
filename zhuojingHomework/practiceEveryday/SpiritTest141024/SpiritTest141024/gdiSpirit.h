#ifndef GDISPIRIT
#define GDISPIRIT

class gdiSpirit
{
public:
	gdiSpirit( TCHAR *filename, int blockSizeX, int blocksizeY, COLORREF maskColor );
	~gdiSpirit(void);

	void setState( int sIndex, int eIndex )
	{
		m_StartIndex = sIndex;
		m_EndIndex = eIndex;

		m_CurSpiRenderIndex = m_StartIndex;
	}

	void render( const HDC &hdc, int x, int y );

private:
	HDC m_hSpidc;
	HBITMAP m_hSpibmp;

	COLORREF m_MaskColor;

	const int m_BlockSizeX;
	const int m_BlockSizeY;
	int m_BlockNumX, m_BlockNumY;
	int m_BlockNumTotal;
	int m_StartIndex, m_EndIndex;
	int m_CurSpiRenderIndex, m_CurSpiRenderY;
};

#endif	// END GDISPIRIT
