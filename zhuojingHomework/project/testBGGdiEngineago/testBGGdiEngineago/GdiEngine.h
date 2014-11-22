#include "AllDefine.h"

#ifndef AFX_GDIENGINE
#define AFX_GDIENGINE

extern HINSTANCE g_hInst;

class __declspec(dllexport) GdiEngine
{
public:
	GdiEngine(void);
	void Engine_SetState(EngineState_Handle Es,void const * const Ptr);
	void Engine_SetState(EngineState_String Es,char const * const Str);
	void Engine_SetState(EngineState_Fp Es,FUNCPOINT Fp);
	void Engine_SetState(EngineState_Bool Es,bool b);
	void Engine_Init();
	void Engine_Start();
	void Engine_Clear(COLORREF color=0x00000000);

	GdiSpriter* Spriter_Load(char const * const BitmapFN,bool IsSpriter=false,COLORREF MaskColor=RGB(0,0,0));
	void Spriter_Free(GdiSpriter *pGdispriter);

	GdiSpriterAlpha* SpriterAlpha_Load(char const * const BitmapFN);
	void SpriterAlpha_Free(GdiSpriterAlpha *pGdispriterAlpha);

	GdiFrameAnimation* FrameAnimation_Load(char const * const BitmapFn,UINT FrameWidth,UINT FrameHeight,
		UINT Fps=26,UINT Frames=0,bool IsSpriter=false,COLORREF MaskColor=RGB(0,0,0));
	void FrameAnimation_Free(GdiFrameAnimation *pGdiframeanimation);

	float Timer_GetFrameTime();
	float Timer_GetPassTime();

	bool Input_KeyDown(int vk);
	bool Input_KeyUp(int vk);
	bool Input_KeyState(int vk);
	void Input_GetMousePos(POINT &pt);

	void Timer_SetTimer(int Id,float Elapse,TIMERPOINT TimerProc);
	void Timer_KillTimer(int Id);

	int Random_GetInt(int MinRange=0,int MaxRange=32767);
	float Random_GetFloat(float MinRange=0.0f,float MaxRange=32767.0f);
	bool GethWnd(HWND &hWnd);
	bool GetBackHdc(HDC &BackHdc);
	~GdiEngine(void);
private:
	DWORD m_EngineState;
	RECT m_GameWindowRect;
	RECT m_ScreenRect;
	HINSTANCE m_hInst;
	HWND m_hWnd;
	HICON m_hIcon;
	HCURSOR m_hCursor;
	char *m_TitelName;
	int m_GameRectWidth,m_GameRectHeight;
	FUNCPOINT m_pUpdataFunc;
	FUNCPOINT m_pRenderFunc;
	GUIPROCE m_pGuiProcssFunc;
	GuiManage *m_pGuiManage;
	HDC m_Mainhdc;
	HDC m_Backhdc;
	HBITMAP m_BackBitmap;
	BYTE m_PreKeyState[256];
	BYTE m_CurKeyState[256];
	float m_CurFpsTime;
	TimerData m_TimerList[10];
private:
	float m_FrameStartTime,m_FrameEndTime;
	float m_PassTime,m_PerTime,m_FrameTime;
private:
	DWORD m_Random;
};

#endif
