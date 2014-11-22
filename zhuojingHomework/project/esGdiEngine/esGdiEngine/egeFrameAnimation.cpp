#include ".\egeframeanimation.h"

egeFrameAnimation::egeFrameAnimation( PTEXTURE tex, int fps, 
									  int blockWidth, int blockHeight, 
									  int width, int height, unsigned int mode, 
									  COLORREF maskColor )
: m_Sprite( tex, 0, 0, width, height, true, maskColor )
{
	pEngine = Engine_Create(NULL);

	if( tex != NULL )
	{
		m_ImgSizeX = pEngine->Texture_GetWidth( tex );
		m_ImgSizeY = pEngine->Texture_GetHeight( tex );
		m_MaxX = m_ImgSizeX/blockWidth;
		m_MaxY = m_ImgSizeY/blockHeight;
	}
	else
	{
		m_ImgSizeX = width;
		m_ImgSizeY = height;
		m_MaxX = 1;
		m_MaxY = 1;
	}

	m_MaxFrame = m_MaxX*m_MaxY;
	m_StartFrame = 0;
	m_CurFrame = 0;
	m_EndFrame = m_MaxFrame-1;

	// 防止除零错误
	if ( fps == 0 )
	{
		m_FrameTime = 0.0f;
	}
	else
	{
		m_FrameTime = 1.0f/fps;
	}
	m_AnimatTime = 0.0f;
	m_BlockSizeX  = blockWidth;
	m_BlockSizeY = blockHeight;
	m_CurMode = mode;

	if ( mode & FA_BACK )
	{
		m_CurFrame = m_EndFrame;
		m_FrameMoveStep = -1;
	}
	else
	{
		m_FrameMoveStep = 1;
	}
}

egeFrameAnimation::~egeFrameAnimation(void)
{
	Engine_Release();
}

void egeFrameAnimation::SetFps( float fps )
{
	// 防止除零错误
	if ( fps == 0 )
	{
		m_FrameTime = 0.0f;
	}
	else
	{
		m_FrameTime = 1.0f/fps;
	}
}

void egeFrameAnimation::Play()
{
	m_isPlaying = true;
}

void egeFrameAnimation::Pause()
{
	m_isPlaying = false;
}

void egeFrameAnimation::Stop()
{
	m_isPlaying = false;
	m_CurFrame = m_StartFrame;
}

void egeFrameAnimation::Update()
{
	if ( m_isPlaying )
	{
		m_AnimatTime += pEngine->Time_GetFrameTime();
		if ( m_AnimatTime >= m_FrameTime )
		{
			m_CurFrame += m_FrameMoveStep;
			switch( m_CurMode )
			{
			case FA_FRONT | FA_NOLOOP | FA_NOPINGPONG:
				{
					if ( m_CurFrame > m_EndFrame )
					{
						m_CurFrame = m_EndFrame;
						m_isPlaying = false;
					}
				}
				break;

			case FA_BACK | FA_NOLOOP | FA_NOPINGPONG:
				{
					if ( m_CurFrame < m_StartFrame )
					{
						m_CurFrame = m_StartFrame;
						m_isPlaying = false;
					}
				}
				break;

			case FA_FRONT | FA_LOOP | FA_NOPINGPONG:
				{
					if ( m_CurFrame > m_EndFrame )
					{
						m_CurFrame = m_StartFrame;
					}
				}
				break;

			case FA_BACK | FA_LOOP | FA_NOPINGPONG:
				{
					if ( m_CurFrame < m_StartFrame )
					{
						m_CurFrame = m_EndFrame;
					}
				}
				break;

			case FA_FRONT | FA_NOLOOP | FA_PINGPONG:
				{
					if ( m_CurFrame > m_EndFrame )
					{
						m_CurFrame = m_EndFrame;
						m_FrameMoveStep = -m_FrameMoveStep;
					}
					else
					if( m_CurFrame < m_StartFrame )
					{
						m_CurFrame = m_StartFrame;
						m_isPlaying = false;
					}
				}
				break;

			case FA_BACK | FA_NOLOOP | FA_PINGPONG:
				{
					if ( m_CurFrame < m_StartFrame )
					{
						m_CurFrame = m_StartFrame;
						m_FrameMoveStep = -m_FrameMoveStep;
					}
					else
					if( m_CurFrame > m_EndFrame )
					{
						m_CurFrame = m_EndFrame;
						m_isPlaying = false;
					}
				}
				break;

			case FA_FRONT | FA_LOOP | FA_PINGPONG:
			case FA_BACK  | FA_LOOP | FA_PINGPONG:
				{
					if ( m_CurFrame > m_EndFrame )
					{
						m_CurFrame = m_EndFrame;
						m_FrameMoveStep = -m_FrameMoveStep;
					}
					else
					if( m_CurFrame < m_StartFrame )
					{
						m_CurFrame = m_StartFrame;
						m_FrameMoveStep = -m_FrameMoveStep;
					}
				}
				break;
			}

			m_AnimatTime -= m_FrameTime;
		}

	}

	// loop
	// 到头重新播一遍
	// pingpong
	// 播一遍再播回来
	// back
	// 反过来播
}

void egeFrameAnimation::Render( int x, int y )
{
	if( m_Sprite.haveTexture() )
	{
		m_Sprite.setTextureRect( m_CurFrame%m_MaxX*m_BlockSizeX, m_CurFrame/m_MaxX*m_BlockSizeY, 
								m_BlockSizeX, m_BlockSizeY);
		m_Sprite.Render( x, y );
	}
}