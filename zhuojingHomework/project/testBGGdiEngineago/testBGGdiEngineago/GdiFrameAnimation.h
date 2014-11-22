#include "AllDefine.h"

#ifndef AFX_FRAMEANIMATION
#define AFX_FRAMEANIMATION

#define FASTATE_FRONT              0x00
#define FASTATE_BACK                 0x01
#define FASTATE_LOOP                 0x02
#define FASTATE_NOLOOP            0x00
#define FASTATE_PINGPONG        0x04
#define FASTATE_NOPINGPONG   0x00

class __declspec(dllexport) GdiFrameAnimation
{
public:
	GdiFrameAnimation(HDC *pBackhdc);

	void LoadFrameAnimation(DWORD ResourceId,UINT FrameWidth,UINT FrameHeight,
		UINT Fps=26,UINT Frames=0,bool IsSpriter=false,COLORREF MaskColor=RGB(0,0,0));
	void LoadFrameAnimation(char const * const BitmapFn,UINT FrameWidth,UINT FrameHeight,
		UINT Fps=26,UINT Frames=0,bool IsSpriter=false,COLORREF MaskColor=RGB(0,0,0));
	void Updata(float FrameTime);
	void Render(int x,int y);
	void Render(int x,int y,int w,int h);
	void SetFramePlayMode(BYTE playmode);
	void SetFrameRange(UINT Frames,UINT Framee);
	void Play();
	int GetFrameWidth();
	int GetFrameHeight();

	~GdiFrameAnimation(void);
private:
	HDC *m_pBackhdc;
private:
	HDC m_SrcHdc;
	HBITMAP m_SrcBit;

#ifndef TRANSPENT
	HDC m_MaskHdc;
	HBITMAP m_MaskBit;
#endif

	COLORREF m_MaskColor;
	bool m_IsSpriter;
	UINT m_Width,m_Height;
	UINT m_FrameWidth,m_FrameHeight;
	UINT m_FrameS,m_FrameE;
	float m_LostTime;
	float m_FpsTime;
	int m_CurFrame;
	UINT m_Row,m_Col;
	BYTE m_AnimationState;
	int m_AddFrame;
};

#endif
