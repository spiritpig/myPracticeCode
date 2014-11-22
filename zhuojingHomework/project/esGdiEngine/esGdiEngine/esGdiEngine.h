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
	//	设置获取参数 类函数
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
	void setManager( egeUiManager *man )
	{
		m_pManager = man;
	}
	egeUiManager* getManager()
	{
		return m_pManager;
	}


	//////////////////////////////////////////////////////////////////////////
	//	按键检测（包括鼠标）
	//	注意: 第一次按下某键，视为KeyDown
	//////////////////////////////////////////////////////////////////////////
	bool KeyDown( unsigned char key );
	bool KeyUp( unsigned char key );
	bool KeyPress( unsigned char key );


	//////////////////////////////////////////////////////////////////////////
	//	texture 系列函数，仅支持BMP位图
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
	float GetFps( float deltaTime );


	//////////////////////////////////////////////////////////////////////////
	//	辅助 系列函数
	//////////////////////////////////////////////////////////////////////////
	void GetCursorPos( POINT &p );
	void FillRect( const HBRUSH &brush, const RECT &r );
	void DrawLine( const HPEN &pen, int sx, int sy, int ex, int ey );
	void DrawText( const HFONT &font, const char *str, RECT &r, 
				UINT format = DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	void CalcRect( const HFONT &font, const char *str, RECT &r );
	int  CalcTextHeight( const HFONT &font );
	int  CalcLastLineLength( const HFONT &font, const char *str );


	void Engine_Init();
	void Engine_Start();

private:

	//////////////////////////////////////////////////////////////////////////
	//	单例工厂模式创建引擎，引擎部件不允许拥有两个，只能存在唯一的一个
	//	不过，可以产生该实例的指针
	//////////////////////////////////////////////////////////////////////////
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

	//////////////////////////////////////////////////////////////////////////
	//	仿照DX渲染管线的清屏和翻屏操作，
	//	使用双缓冲用于解决闪屏问题。
	//////////////////////////////////////////////////////////////////////////
	void _Render_Clear();
	void _Render_SwapBuffer();

	egeUiManager *m_pManager;
	UpdateFunc Update;
	RenderFunc Render;
	unsigned int m_clearColor;
	int m_screenX, m_screenY;
	int m_screenWidth, m_screenHeight;

	unsigned char *m_curKeyBuffer, *m_prevKeyBuffer;

	float m_FrameTime;
	float m_FrameStartTime;
	float m_FrameEndTime;
	float m_PassTime;
	float m_GetFpsDeltaTime, m_GetFpsMaxTime, m_curFps;
	
};

#endif	// END ES_GDIENGINE
