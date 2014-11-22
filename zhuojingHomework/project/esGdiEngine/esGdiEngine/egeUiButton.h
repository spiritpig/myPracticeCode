#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef EGEUIBUTTON
#define EGEUIBUTTON

//////////////////////////////////////////////////////////////////////////
//	button控件，三态按钮
//	由三张精灵图组成
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
class egeUiButton : public egeUiObject
#else
class _declspec( dllexport ) egeUiButton : public egeUiObject
#endif
{
public:
	egeUiButton( char *pName, int id, int x, int y, int width, int height,
				char *pUpFN, char *pOnFN, char *pDownFN,
				bool isUpMask = false, COLORREF upMaskColor = RGB( 0, 0, 0 ),
				bool isOnMask = false, COLORREF onMaskColor = RGB( 0, 0, 0 ),
				bool isDownMask = false, COLORREF downMaskColor = RGB( 0, 0, 0 ), 
				egeUiObject *pParent = NULL );
	virtual ~egeUiButton(void);

	virtual void SetHotSpot( float ratex, float ratey );
	virtual void SetUpTex(char *pUpFN, bool isUpMask = false, 
		COLORREF upMaskColor = RGB( 0, 0, 0 ) );
	virtual void SetOnTex(char *pOnFN, bool isOnMask = false, 
		COLORREF onMaskColor = RGB( 0, 0, 0 ) );
	virtual void SetDownTex(char *pDownFN, bool isDownMask = false, 
		COLORREF downMaskColor = RGB( 0, 0, 0 ));
	virtual bool IsClicked()
	{
		return m_isClicked;
	}
	virtual bool IsPress()
	{
		return m_isPress;
	}

	virtual bool IsMouseIntersectObject();
	virtual void Update();
	virtual void Render();

private:
	egeSprite *m_pUpSprite;
	PTEXTURE m_pUpTex;
	COLORREF m_UpMaskColor;

	egeSprite *m_pOnSprite;
	PTEXTURE m_pOnTex;
	COLORREF m_OnMaskColor;

	egeSprite *m_pDownSprite;
	PTEXTURE m_pDownTex;
	COLORREF m_DownMaskColor;

	bool m_isOn, m_isDown, m_isPress,
		 m_isClicked, m_isUp;
};

#endif	// END EGEUIBUTTON