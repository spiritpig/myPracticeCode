#include "EingeDefine.h"

#ifndef AFX_UISROCLLBAR
#define AFX_UISROCLLBAR

#ifdef _DEBUG
class UiSrocllBar:public UiObject
#else
class __declspec(dllexport) UiSrocllBar:public UiObject
#endif
{
public:
	UiSrocllBar(DWORD id,char const * const pName,
		int x,int y,int w,int h,UiManage *pUiManage=NULL,UiObject *pParent=NULL);
	void SetLeftBtnInfor(char const * const UpFnName,
		char const * const OnFnName,
		char const * const DownFnName,
		bool IsMaskUp=false,COLORREF maskcolorup=RGB(0,0,0),
		bool IsMaskOn=false,COLORREF maskcoloron=RGB(0,0,0),
		bool IsMaskDown=false,COLORREF maskcolordown=RGB(0,0,0));
	void SetRightBtnInfor(char const * const UpFnName,
		char const * const OnFnName,
		char const * const DownFnName,
		bool IsMaskUp=false,COLORREF maskcolorup=RGB(0,0,0),
		bool IsMaskOn=false,COLORREF maskcoloron=RGB(0,0,0),
		bool IsMaskDown=false,COLORREF maskcolordown=RGB(0,0,0));
	void SetScrollBtnInfor(char const * const UpFnName,
		char const * const OnFnName,
		char const * const DownFnName,
		bool IsMaskUp=false,COLORREF maskcolorup=RGB(0,0,0),
		bool IsMaskOn=false,COLORREF maskcoloron=RGB(0,0,0),
		bool IsMaskDown=false,COLORREF maskcolordown=RGB(0,0,0));
	void SetScrollBackInfor(char const * const FnName,
		bool IsMask=false,COLORREF maskcolor=RGB(0,0,0));
	float GetRate();

	void Update();
	void Render();
	~UiSrocllBar(void);
private:
	UiButton *m_LeftBtn;
	UiButton *m_RightBtn;
	UiButton *m_ScrollBtn;
	PSTEXTURE m_ScrollBackTex;
	Sprite *m_ScrollBack;
	float m_Rate;
	int m_Scrollleng;
	int m_BtnW,m_BtnH;
	bool m_MouseMove;
	bool m_CanMove;
	int m_Offset;
};

#endif