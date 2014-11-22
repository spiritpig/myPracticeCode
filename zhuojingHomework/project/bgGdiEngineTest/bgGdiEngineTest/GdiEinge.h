#include "EingeDefine.h"

#ifndef AFX_GDIEINGE
#define AFX_GDIEINGE

#define SAFE_DELETE(p) {if(p) {delete p;p=NULL;}}
#define SAFE_DELARR(p) {if(p) {delete []p;p=NULL;}}

#ifdef _DEBUG
class GdiEinge
#else
class __declspec(dllexport) GdiEinge
#endif
{
protected:
	GdiEinge(HINSTANCE hInst);
#ifdef _DEBUG
	friend GdiEinge* GdiEingeCreate(HINSTANCE hInst);
#else
	friend __declspec(dllexport) GdiEinge* GdiEingeCreate(HINSTANCE hInst);
#endif
public:
	bool Eingne_SetState(Einge_State_Fp Es,Funcp fp);
	bool Eingne_SetState(Einge_State_Int Es,int n);
	bool Eingne_SetState(Einge_State_Void Es,void *p);
	bool Eingne_SetState(Einge_State_String Es,char *p);
	bool Eingne_SetState(Einge_State_Bool Es,bool b);
	void Eingne_Init();
	void Eingne_Start();
	void Render_Clear(COLORREF color);
	float GetPassTime();
	float GetFrameTime();
	unsigned int GetFPS();
	int GetRandomInt(int minnum=0,int maxnum=32768);
	float GetRandomfloat(float minnum=0.0f,float maxnum=32768.0f);

	void GetCursorPos(POINT &pt);
	bool MouseKeyDown(unsigned char Vk);
	bool MouseKeyUp(unsigned char Vk);
	bool MouseKeyPress(unsigned char Vk);
	bool KeyDown(unsigned char Vk);
	bool KeyUp(unsigned char Vk);
	bool KeyPress(unsigned char Vk);

	PSTEXTURE LoadTexture(char const * const FnName);
	void TextureFree(PSTEXTURE pTexture);
	int GetTextureWidth(PSTEXTURE pTexture);
	int GetTextureHeight(PSTEXTURE pTexture);

	PSMUSIC LoadMusic(char const * const FnName);
	void MusicPlay(PSMUSIC music,bool loop=false);
	void MusicStop(PSMUSIC music);
	void MusicVolume(PSMUSIC music,unsigned int Vol);
	void MusicFree(PSMUSIC music);

	void SetUiManage(UiManage *pUiManage);

	void DrawText(HFONT hFont, char *pString,RECT *pRect,UINT uFormat=DT_CENTER|DT_SINGLELINE|DT_VCENTER);
	void CalcRect(HFONT hFont, char *pString,RECT *pRect);
	int CalcLastLineLength(HFONT hFont,char *pString);
	int CalcTextHeight(HFONT hFont);
	void FillRect(HBRUSH hBrush,RECT *pRect);
	void Lineto(HPEN hpen,int sx,int sy,int ex,int ey);

	void Release();
	~GdiEinge(void);
private:
	void _FilpBackBuffer();
private:
	friend class Sprite;
private:
	HINSTANCE m_hObjInst;
	HINSTANCE m_hInst;
	HWND m_hWnd;
	MSG m_msg;
	HDC m_hMainHdc;
	HBITMAP m_hBackBuffer;
	HDC m_hBackBufferDc;
	HBRUSH m_hClearBrush;
	COLORREF m_ClearColor;
	bool m_FullScreen;
private:
	float m_PassTime;
	float m_FrameTime;
	float m_FrameStart,m_FrameEnd;
	Funcp m_pUpdate;
	Funcp m_pRender;
private:
	char *m_TitleName;
	int m_ScreenWidth;
	int m_ScreenHigh;
	int m_ClientWidth;
	int m_ClientHigh;
	int m_RealClientWidth;
	int m_RealClientHigh;
	RECT m_ClientRect;
	RECT m_WindowRect;
	bool m_IsDelIcon;
	bool m_IsDelSmIcon;
	bool m_IsDelCursor;
	HICON m_hIcon;
	HICON m_hSmIcon;
	HCURSOR m_hCursor;
	POINT m_CursorPt;
	DWORD m_RandomNum;
	bool m_KeyState[2][128];
	bool *m_pCurKeyState;
	bool *m_pPreKeyState;
	bool *m_pKeySwap;
	int m_i;
	BITMAP m_BitmapInfor;
public:
	UiManage *m_pUiManage;
};

#endif
