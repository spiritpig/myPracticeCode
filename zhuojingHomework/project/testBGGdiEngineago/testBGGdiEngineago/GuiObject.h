#ifndef AFX_GUIOBJECT
#define AFX_GUIOBJECT

class __declspec(dllexport) GuiObject
{
public:
	GuiObject(GdiEngine *pGdiEngine);
	virtual void Init(GuiManage *pGuiManage,void *GuiObjectData)=0;
	virtual void Updata(float frametime)=0;
	virtual void Render()=0;
	virtual void ProcessInput()=0;
	virtual void ProcessInput(UINT msg,WPARAM wParam,LPARAM lParam)=0;
	virtual void SetPos(POINT const &pos);
	virtual void GetOffsetPos(POINT &pos);
	virtual void GetScreenPos(POINT &pos);
	virtual void UpDataScreenPos();
	virtual bool PtInObject(POINT const &pt);
	virtual void SetFocus();
	virtual void LostFocus();
	char const * GetGuiCtrlName();
	GuiObject* GetParent();
	virtual ~GuiObject(void);
public:
	DWORD m_dwId;
protected:
	static GdiEngine *m_pGdiEngine;
	static HWND m_hWnd;
	static DWORD m_Ref;

	GuiManage *m_pGuiMange;
	HDC m_BackHdc;
	GuiObject *m_pParent;
	char *m_CtrlName;
	POINT m_OffsetPos;
	POINT m_ScreenPos;
	POINT m_Size;
	bool m_HaveFocus;
};

#endif