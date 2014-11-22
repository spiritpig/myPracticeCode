#include "commonHeader.h"
#include "esGdiEngineAll.h"

#ifndef ES_GDIENGINE
#define ES_GDIENGINE

// ����ģʽѡ����Ķ��巽ʽ
#ifdef _DEBUG
class esGdiEngine
#else
class _declspec( dllexport ) esGdiEngine
#endif
{
public:
	PESDC getScreenHandle();

	//////////////////////////////////////////////////////////////////////////
	//	���û�ȡ���� �ຯ��
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
	//	������⣨������꣩
	//	ע��: ��һ�ΰ���ĳ������ΪKeyDown
	//////////////////////////////////////////////////////////////////////////
	bool KeyDown( unsigned char key );
	bool KeyUp( unsigned char key );
	bool KeyPress( unsigned char key );


	//////////////////////////////////////////////////////////////////////////
	//	texture ϵ�к�������֧��BMPλͼ
	//////////////////////////////////////////////////////////////////////////
	PTEXTURE Texture_Load( char *filename );
	void Texture_Free( PTEXTURE tex );
	int Texture_GetWidth( PTEXTURE tex );
	int Texture_GetHeight( PTEXTURE tex );


	//////////////////////////////////////////////////////////////////////////
	//	ʱ�� ϵ�к���
	//////////////////////////////////////////////////////////////////////////
	float Time_GetFrameTime()
	{
		return m_FrameTime;
	}
	float GetFps( float deltaTime );


	//////////////////////////////////////////////////////////////////////////
	//	���� ϵ�к���
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
	//	��������ģʽ�������棬���沿��������ӵ��������ֻ�ܴ���Ψһ��һ��
	//	���������Բ�����ʵ����ָ��
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
	//	����DX��Ⱦ���ߵ������ͷ���������
	//	ʹ��˫�������ڽ���������⡣
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
