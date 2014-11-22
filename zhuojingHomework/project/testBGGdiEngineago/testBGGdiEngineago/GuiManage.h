#ifndef AFX_GUIMANAGE
#define AFX_GUIMANAGE

class /*__declspec(dllexport)*/ GuiManage
{
public:
	GuiManage(GdiEngine *pGdiEngine);
	bool AddGuiObject(DWORD GuiKind,void *GuiData);
	GuiObject* GetGuiObject(DWORD dwId);
	void Updata(float Frametime);
	void Render();
	void ProcessInput(UINT msg,WPARAM wParam,LPARAM lParam);
	void PostMessage(UINT msg,UINT Param1,UINT Param2);
	bool GetMessage(GuiMsg &guimsg);
	GuiObject* GetForgroundUI();
	void SetForgroundUI(GuiObject *pForgroundUi);
	void* operator new(size_t s);
	void* operator new[](size_t s);
	void operator delete(void *p);
	void operator delete[](void *p);
	virtual ~GuiManage(void);
protected:
	GdiEngine *m_pGdiEngine;
	list<GuiObject *> m_GuiObjectList;
	list<GuiObject *>::iterator m_GuiObjectPt;
	deque<GuiMsg>  m_GuiMsgDeque;
	GuiObject *m_ForgroundUi;
};

#endif
