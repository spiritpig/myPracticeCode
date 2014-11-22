#include "EingeDefine.h"

#ifndef AFX_UISTATICTEXT
#define AFX_UISTATICTEXT

#ifdef _DEBUG
class UiStaticText:public UiObject
#else
class __declspec(dllexport) UiStaticText:public UiObject
#endif
{
public:
	UiStaticText(DWORD id,char const * const pName,
		int x,int y,int w,int h,UiManage *pUiManage,UiObject *pParent=NULL);
	void SetFont(HFONT hfont);
	virtual void Update();
	virtual void Render();
	~UiStaticText(void);
private:
	HFONT m_hFont;
};

#endif