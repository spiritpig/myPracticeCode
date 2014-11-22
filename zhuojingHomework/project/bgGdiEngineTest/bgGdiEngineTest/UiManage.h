#include "EingeDefine.h"

#ifndef AFX_UIMANAGE
#define AFX_UIMANAGE
#include "Sprite.h"

#ifdef _DEBUG
class UiManage
#else
class __declspec(dllexport) UiManage
#endif
{
public:
	UiManage(void);
	void AddUiCtrls(UiObject *pUiObject);
	bool DeleteUiCtrls(UiObject *pUiObject);
	UiObject* GetUiCtrls(DWORD Id,int sit=1);
	void WndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam);
	bool PeekUiMessage(UiMsg &uimsg);
	void SetUiMessage(unsigned int id,unsigned int msg,unsigned int fParam,UiObject *pUiObject);
	void Update();
	void Render();
	~UiManage(void);
private:
	GdiEinge *m_pGdiEinge;
	list<UiObject *> m_UiList;
	list<UiObject *>::iterator m_UiListPt;
	list<UiObject *>::reverse_iterator m_UiListRpt;
	list<UiMsg> m_UiMsgDeque;
};

#endif