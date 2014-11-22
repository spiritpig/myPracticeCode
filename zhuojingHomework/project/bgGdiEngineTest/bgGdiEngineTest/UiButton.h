#include "EingeDefine.h"

#ifndef AFX_UIBUTTON
#define AFX_UIBUTTON

#ifdef _DEBUG
class UiButton:public UiObject
#else
class __declspec(dllexport) UiButton:public UiObject
#endif
{
public:
	UiButton(DWORD id,char const * const pName,
		char const * const UpFnName,char const * const OnFnName,
		char const * const DownFnName,int x,int y,int w,int h,UiManage *pUiManage,
		bool IsMaskUp=false,COLORREF maskcolorup=RGB(0,0,0),
		bool IsMaskOn=false,COLORREF maskcoloron=RGB(0,0,0),
		bool IsMaskDown=false,COLORREF maskcolordown=RGB(0,0,0)
		,UiObject *pParent=NULL);
	void SetMaskColorUp(COLORREF maskcolor);
	void SetMaskColorOn(COLORREF maskcolor);
	void SetMaskColorDown(COLORREF maskcolor);
	void SetBtnUpTextrue(char const * const UpFnName,bool ismask=false,COLORREF maskcolor=RGB(255,255,255));
	void SetBtnOnTextrue(char const * const OnFnName,bool ismask=false,COLORREF maskcolor=RGB(255,255,255));
	void SetBtnDownTextrue(char const * const DownFnName,bool ismask=false,COLORREF maskcolor=RGB(255,255,255));
	void ShowText(bool showtext);
	bool IsClicked();
	bool IsPress();

	virtual void SetHotSpot(float ratex,float ratey);
	virtual void Update();
	virtual void Render();
	~UiButton(void);
protected:
	Sprite *m_BtnUp;
	PSTEXTURE m_BtnUpTex;
	Sprite *m_BtnOn;
	PSTEXTURE m_BtnOnTex;
	Sprite *m_BtnDown;
	PSTEXTURE m_BtnDownTex;
	bool m_IsOn;
	bool m_IsDown;
	bool m_IsSprite;
	bool m_IsClicked;
	bool m_ShowText;
	bool m_IsPress;
};

#endif