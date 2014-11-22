#include "EingeDefine.h"

#ifndef AFX_FRAMEANIMATE
#define AFX_FRAMEANIMATE
#include "Sprite.h"

#ifdef _DEBUG
class FrameAnimate:public Sprite
#else
class __declspec(dllexport) FrameAnimate:public Sprite
#endif
{
public:
	FrameAnimate(void);
	FrameAnimate(PSTEXTURE pTexture,int framew,int frameh,int frames=0,
		int fps=24,bool Ismask=false,COLORREF maskcolor=RGB(0,0,0));
	void SetHotSpot(float ratex,float ratey);
	void SetTexture(PSTEXTURE pTexture);
	void SetFrameWH(int w,int h);
	void SetFrames(int frames);
	void SetFps(int fps);
	void SetMaskColor(COLORREF maskcolor);
	void SetMode(char mode);
	void Render(int x,int y);
	void RenderEx(int x,int y,float ScaleX=1.0f,float ScaleY=1.0f);
	void Render4V(int l,int t,int r,int b);
	void Update();
	void Play();
	void Puase();
	void Stop();
	void SetFrameRange(int frames,int framee);
	void SetCurrentFrame(int framecurrent);
	bool GetIsPlaying();
	~FrameAnimate(void);
private:
	int m_FrameStart;
	int m_FrameEnd;
	int m_Fps;
	float m_FpsTime;
	float m_AnimateTime;
	int m_ImageW,m_ImageH;
	int m_FrameW,m_FrameH;
	int m_Row,m_Col;
private:
	int m_CurFrame;
	int m_FrameStep;
	bool m_IsPlaying;
	char m_PlayMode;
};

#endif
