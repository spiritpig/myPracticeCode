#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef ES_GDIENGINE
#define ES_GDIENGINE

// 根据模式选择类的定义方式
#ifdef _DEBUG
class esGdiEngine
#else
class _declspec( dllexport ) esGdiEngine
#endif
{
public:
	PESDC getScreenHandle();

	//////////////////////////////////////////////////////////////////////////
	//	设置参数 类函数
	//////////////////////////////////////////////////////////////////////////
	void SetClearColor( unsigned int color );
	void SetTitle( char *title );
	void SetUpdateFunc( UpdateFunc update )
	{
		this->Update = update;
	}
	void SetRenderFunc( RenderFunc render )
	{
		this->Render = render;
	}

// 	bool KeyDown( char key );
// 	bool KeyUp( char key );
// 	bool KeyPress( char key );

	//////////////////////////////////////////////////////////////////////////
	//	texture 系列函数
	//////////////////////////////////////////////////////////////////////////
	PTEXTURE Texture_Load( char *filename );
	void Texture_Free( PTEXTURE tex );
	int Texture_GetWidth( PTEXTURE tex );
	int Texture_GetHeight( PTEXTURE tex );

	//////////////////////////////////////////////////////////////////////////
	//	时间 系列函数
	//////////////////////////////////////////////////////////////////////////
	float Time_GetFrameTime()
	{
		return m_FrameTime;
	}

	void Engine_Init();
	void Engine_Start();

private:

#ifdef _DEBUG
	friend esGdiEngine* Engine_Create( PESINSTANCE hInstance );
#else
	friend _declspec( dllexport ) esGdiEngine* Engine_Create( PESINSTANCE hInstance );
#endif

#ifdef _DEBUG
	friend void Engine_Release();
#else
	friend _declspec( dllexport ) void Engine_Release();
#endif

	friend class egeSprite;

	esGdiEngine();
	~esGdiEngine();

	void _Render_Clear();
	void _Render_SwapBuffer();

	unsigned int m_clearColor;
	int m_screenX, m_screenY;
	int m_screenWidth, m_screenHeight;

	//char m_keyBuffer[256];

	UpdateFunc Update;
	RenderFunc Render;

	float m_FrameTime;
	float m_FrameStartTime;
	float m_FrameEndTime;
	float m_PassTime;
};

#endif	// END ES_GDIENGINE