#ifndef AFX_GUIBUTTON
#define AFX_GUIBUTTON

class  __declspec(dllexport) GuiButton:public GuiObject
{
public:
	GuiButton(GdiEngine *pGdiEngine);
	virtual void Init(GuiManage *pGuiManage,void *GuiObjectData);
	virtual void Updata(float frametime);
	virtual void Render();
	virtual void ProcessInput();
	virtual void ProcessInput(UINT msg,WPARAM wParam,LPARAM lParam);
	virtual ~GuiButton(void);
private:
	GdiSpriter *m_DownSpr;
	GdiSpriter *m_UpSpr;
	GdiSpriter *m_OnSpr;

	GdiFrameAnimation *m_DownFa;
	GdiFrameAnimation *m_UpFa;
	GdiFrameAnimation *m_OnFa;

	GuiState m_GuiBtnState;
	bool m_3State;
	bool m_IsAnimation;
};

#endif
