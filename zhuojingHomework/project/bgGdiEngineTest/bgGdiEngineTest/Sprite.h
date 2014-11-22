#include "EingeDefine.h"

#ifndef AFX_SPRITE
#define AFX_SPRITE

#ifdef _DEBUG
class Sprite
#else
class __declspec(dllexport) Sprite
#endif
{
public:
	Sprite(void);
	Sprite(PSTEXTURE pTexture,int u,int v,int w,int h,bool Ismask=false,COLORREF maskcolor=RGB(0,0,0));
	void SetHotSpot(float ratex,float ratey);
	void SetTexture(PSTEXTURE pTexture);
	void SetTextureRect(int u,int v,int w,int h);
	void SetMaskColor(COLORREF maskcolor);
	void Render(int x,int y);
	void RenderEx(int x,int y,float ScaleX=1.0f,float ScaleY=1.0f);
	void Render4V(int l,int t,int r,int b);
	bool IsNotMaskColor(int x,int y);
	~Sprite(void);
protected:
	HDC m_hdc;
	int m_u,m_v,m_w,m_h;
	int m_hotspotx,m_hotspoty;
	bool m_IsMask;
	COLORREF m_MaskColor;
	PSTEXTURE m_Texture;
	GdiEinge *m_pGdiEinge;
};

#endif


