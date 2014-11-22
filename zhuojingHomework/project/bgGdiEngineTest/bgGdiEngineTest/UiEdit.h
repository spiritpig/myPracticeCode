#include "EingeDefine.h"

#ifndef AFX_UIEDIT
#define AFX_UIEDIT

#ifdef _DEBUG
class UiEdit:public UiObject
#else
class __declspec(dllexport) UiEdit:public UiObject
#endif
{
public:
	UiEdit(DWORD id,char const * const pName,
		char const * const BackFnName,char const * const FrameFnName,
		int x,int y,int framewidth=5,int w=100,int h=100,UiManage *pUiManage=NULL,
		bool IsMaskBack=false,COLORREF maskcolorback=RGB(0,0,0),
		bool IsMaskFrame=false,COLORREF maskcolorframe=RGB(0,0,0),
		UiObject *pParent=NULL);
	void SetMaskColorBack(COLORREF maskcolor);
	void SetMaskColorFrame(COLORREF maskcolor);
	void SetBackTextrue(char const * const BackFnName,bool ismask=false,COLORREF maskcolor=RGB(255,255,255));
	void SetFrameTextrue(char const * const FrameFnName,bool ismask=false,COLORREF maskcolor=RGB(255,255,255));
	virtual void SetHotSpot(float ratex,float ratey);
	void SetFlashTime(float t);
	void SetFont(HFONT hfont);

	virtual void WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	virtual void Update();
	virtual void Render();
	~UiEdit(void);
private:
	Sprite *m_Back;
	PSTEXTURE m_BackTex;
	Sprite *m_Frame;
	PSTEXTURE m_FrameTex;
	RECT m_TextRect;
	bool m_IsSprite;
	int m_FrameWidth;
	float m_FlashTime;
	float m_FlashLostTime;
	bool m_DrawCursor;
	int m_CharHeight;
	HFONT m_hFont;
};

#endif