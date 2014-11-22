#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef EGEFRAMEANIMATION
#define EGEFRAMEANIMATION

//////////////////////////////////////////////////////////////////////////
//	帧动画类，由于贴图加载的限制，仅支持bmp位图
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
class egeFrameAnimation
#else
class _declspec( dllexport ) egeFrameAnimation
#endif
{
public:
	egeFrameAnimation( PTEXTURE tex, int fps, int blockWidth, int blockHeight, 
						int width, int height, unsigned int mode, 
						COLORREF maskColor );
	~egeFrameAnimation(void);

	void setFrameRange( int start, int end )
	{
		m_StartFrame = start;
		m_EndFrame = end;

		m_CurFrame = m_StartFrame;
	}
	void SetFps( float fps );

	void Play();
	void Pause();
	void Stop();
	void Update();
	void Render( int x, int y );

private:
	esGdiEngine *pEngine;
	egeSprite m_Sprite;

	float m_FrameTime, m_AnimatTime;
	int m_FrameMoveStep;
	int m_CurFrame, m_MaxFrame;
	int m_StartFrame, m_EndFrame;
	int m_MaxX, m_MaxY;
	int m_BlockSizeX, m_BlockSizeY;
	int m_ImgSizeX, m_ImgSizeY;
	unsigned int m_CurMode;

	bool m_isPlaying;
};

#endif	// END EGEFRAMEANIMATION
