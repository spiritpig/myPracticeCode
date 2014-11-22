#ifndef AFX_GUISTATICTEXT
#define AFX_GUISTATICTEXT

class __declspec(dllexport) GuiStaticText:public GuiObject
{
public:
	GuiStaticText(GdiEngine *pGdiEngine);
	virtual void Init(GuiManage *pGuiManage,void *GuiObjectData);
	virtual void Updata(float frametime);
	virtual void Render();
	virtual void ProcessInput();
	virtual void ProcessInput(UINT msg,WPARAM wParam,LPARAM lParam);
	~GuiStaticText(void);
private:
	HFONT m_hFont;
	COLORREF m_TextColor;
	LOGFONT m_Logfont;
};

#endif