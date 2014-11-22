#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef EGEUISTATIC
#define EGEUISTATIC

#ifdef _DEBUG
class egeUiStatic : public egeUiObject
#else
class _declspec( dllexport ) egeUiStatic : public egeUiObject
#endif
{
public:
	egeUiStatic( char *pName, int id, int x, int y, 
				int width, int height, egeUiObject *pParent = NULL );
	egeUiStatic( int id, int x,int y, int width, int height, 
				char *texFn, bool isMask, COLORREF maskColor, 
				egeUiObject *pParent = NULL );
	virtual ~egeUiStatic(void);

	virtual void Update();
	virtual void Render();

private:
	PTEXTURE m_pContentTex;
	egeSprite *m_pContentSprite;
	HFONT m_textFont;
};

#endif	// END EGEUISTATIC