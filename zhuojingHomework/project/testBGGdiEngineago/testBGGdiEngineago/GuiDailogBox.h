#ifndef AFX_GUIDAILOGBOX
#define AFX_GUIDAILOGBOX

class GuiManage;

//__declspec(dllexport) void DefDailogProcess(UINT Msg,UINT Param1,UINT Param2);

class  __declspec(dllexport) GuiDailogBox:public GuiObject
{
public:
	GuiDailogBox(GdiEngine *pGdiEngine);
	bool AddGuiObject(DWORD GuiKind,void *GuiData);
	GuiObject* GetGuiObject(DWORD dwId);
	virtual void Init(GuiManage *pGuiManage,void *GuiObjectData);
	virtual void Updata(float frametime);
	virtual void Render();
	virtual void ProcessInput();
	virtual void ProcessInput(UINT msg,WPARAM wParam,LPARAM lParam);
	void PostMessage(UINT msg,UINT Param1,UINT Param2);
	bool GetMessage(GuiMsg &guimsg);
	void ShowDailog();
	void CloseDailog();
	virtual void LostFocus();
	~GuiDailogBox(void);
private:
	GdiSpriter *m_LeftTopSpr;
	GdiSpriter *m_TopCenterSpr;
	GdiSpriter *m_RightTopSpr;
	GdiSpriter *m_RightCenterSpr;
	GdiSpriter *m_RightBottomSpr;
	GdiSpriter *m_BottomCenterSpr;
	GdiSpriter *m_LeftBottomSpr;
	GdiSpriter *m_LeftCenterSpr;
	GdiSpriter *m_MidSpr;
	bool m_Show;
private:
	GuiManage *m_pGuiManage;
	GUIPROCE m_pUserProcess;
	RECT m_DragRect;
	bool m_Move;
	POINT m_MoveOffset;
	GuiObject *m_pForgroundUI;
};

#endif