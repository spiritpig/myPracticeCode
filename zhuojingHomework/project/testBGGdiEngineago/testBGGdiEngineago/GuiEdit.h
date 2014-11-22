#ifndef AFX_GUIEDIT
#define AFX_GUIEDIT

#define DEL1 0x80
#define DEL2 0xC0
#define DEL3 0xE0
#define DEL4 0xF0

class  __declspec(dllexport) GuiEdit:public GuiObject
{
public:
	GuiEdit(GdiEngine *pGdiEngine);
	virtual void Init(GuiManage *pGuiManage,void *GuiObjectData);
	virtual void Updata(float frametime);
	virtual void Render();
	virtual void ProcessInput();
	virtual void ProcessInput(UINT msg,WPARAM wParam,LPARAM lParam);
	void SetFlashFrameTime(float Ft);
	~GuiEdit(void);
private:
	GdiSpriter *m_pBackSpr;
	GdiFrameAnimation *m_pBackFa;
	bool m_IsAnimation;
	int m_EdgeWidth,m_EdgeHeigh;
	int m_Leng;
	int m_UnicodePos;
	POINT m_MyCursorPos;
	HPEN m_CurSurPen;
	int m_ReturnNum;
	int m_CharHeight;
	float m_FlashFrameTime;
	float m_FlashTime;
	bool m_ShowCurSor;
};

#endif
