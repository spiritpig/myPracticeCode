#include "AllDefine.h"

#ifndef AFX_GDISPRITER
#define AFX_GDISPRITER

class __declspec(dllexport) GdiSpriter
{
public:
	GdiSpriter(HDC *pBackhdc);

	void LoadSpriter(DWORD ResourceId,bool IsSpriter=false,COLORREF MaskColor=RGB(0,0,0));
	void LoadSpriter(char const * const BitmapFn,bool IsSpriter=false,COLORREF MaskColor=RGB(0,0,0));
	void Render(int x,int y);
	void Render(int x,int y,int w,int h);
	int GetWidth();
	int GetHeight();

	~GdiSpriter(void);
private:
	HDC *m_pBackhdc;
private:
	HDC m_SrcHdc;
	HBITMAP m_SrcBit;

#ifndef TRANSPENT
	HDC m_MaskHdc;
	HBITMAP m_MaskBit;
#endif

	COLORREF m_MaskColor;
	bool m_IsSpriter;
	int m_Width,m_Height;
};

#endif
