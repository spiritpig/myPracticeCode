#ifndef AFX_SPRITERALPHA
#define AFX_SPRITERALPHA

class __declspec(dllexport) GdiSpriterAlpha
{
public:
	GdiSpriterAlpha(HDC *pBackhdc);

	void LoadSpriter(char const * const BitmapFn);
	void Render(int x,int y,float srcalpha=1.0f,float destalpha=0.0f);
	void Render(int x,int y,int w,int h,float alpha=1.0f);

	~GdiSpriterAlpha(void);
private:
	HDC *m_pBackhdc;
private:
	HDC m_SrcHdc;
	HBITMAP m_SrcBit;
	HDC m_AlphaBufferHdc;
	HBITMAP m_AlphaBufferBit;
	int m_Width,m_Height;
	HBRUSH m_BlackBrush;
	BLENDFUNCTION m_BlendFunc;
};

#endif
