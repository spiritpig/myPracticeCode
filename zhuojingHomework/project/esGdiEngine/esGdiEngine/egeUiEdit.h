#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef EGEUIEDIT
#define EGEUIEDIT

//////////////////////////////////////////////////////////////////////////
//	Edit控件，由四条边框和一个背景图片组成
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
class egeUiEdit : public egeUiObject
#else
class _declspec( dllexport ) egeUiEdit : public egeUiObject
#endif
{
public:
	egeUiEdit( char *pName, int id, char *pContentFN, char *pBorderFN, 
			int x, int y, int width = 100, int height = 100, int borderWidth = 10,
			bool isContentMask = false, COLORREF contentMaskColor = RGB( 0, 0, 0 ),
			bool isBorderMask = false, COLORREF borderMaskColor = RGB( 0, 0, 0 ),
			egeUiObject *pParent = NULL );
	~egeUiEdit(void);

	void setFont( const HFONT &font );
	void wndProc( PESWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	virtual void Update();
	virtual void Render();

private:
	egeSprite *m_pContentSprite;
	PTEXTURE m_pContentTex;
	COLORREF m_ContentMaskColor;

	egeSprite *m_pBorderSprite;
	PTEXTURE m_pBorderTex;
	COLORREF m_BorderMaskColor;

	RECT m_drawTextRect;
	int m_BorderWidth;

	bool m_isFlash;
	float m_cursorFlashTime;
	float m_cursorMaxFlashTime;

	HFONT m_Font;
	int m_CharHeight;
	char *m_curLineStartPos;
};

#endif	// END EGEUIEDIT