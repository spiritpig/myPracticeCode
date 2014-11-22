#include "esGdiEngine.h"

//////////////////////////////////////////////////////////////////////////
//	文件域变量，将其隐藏在本cpp中
//	可以省去将其作为类变量的繁复的
//	类型转换过程。
//	（减少直接以及间接地使用windows的数据类型）
//////////////////////////////////////////////////////////////////////////
static HDC hBackBuffer = NULL,hMainBuffer = NULL;
static HINSTANCE hGameInst = NULL;
static HINSTANCE hInst = NULL;
static HWND hWnd = NULL;
static HBITMAP backBmp;
static BITMAP bmpInfo;
static HBRUSH clearBrush = NULL;
static RECT clientRect;
static int engineRef = 0;
static esGdiEngine *pEngine;


static void swap( unsigned char **ca, unsigned char **cb )
{
	static unsigned char *temp;
	temp = *ca;
	*ca = *cb;
	*cb = temp;
}

//************************************
// Method:		getStringLastLinePos
// FullName:	getStringLastLinePos
// Access:		public static 
// Returns:		char*
// Qualifier:
// Parameter:	const char * const str
// Description: 找到输入文本中最后一个\n，并返回
//************************************
static char* getStringLastLinePos( const char * const str )
{
	if( str == NULL )
	{
		return NULL;
	}
	else
	{
		int index = (int)strlen( str )-1;
		while ( index > -1 && str[index] != '\n' )
		{
			--index;
		}

		return (char *)&str[index+1];
	}
}


//************************************
// Method:		calcOneLineTextWidth
// FullName:	calcOneLineTextWidth
// Access:		public static 
// Returns:		int
// Qualifier:
// Parameter:	HDC hdc
// Parameter:	const char * const str（必须只包含一行的内容,即无两个\n）
// Description: 计算输入文本的宽度
//************************************
static int calcOneLineTextWidth( HDC hdc, const char * const str )
{
	size_t size = strlen( str );
	int len = 0;
	int clen = 0;
	unsigned int ch;

	for ( size_t i = 0; i<size; )
	{
		if ( (str[i] & 0x80) == 0 )
		{
			ch = str[i];
			i += 1;
		}
		else
		{
			ch = *(WCHAR *)str[i];
			i += 2;
		}

		if( GetCharWidth32( hdc, ch, ch, &clen ) )
		{
			len += clen;
		}
	}
	
	return len;
}

PESDC esGdiEngine::getScreenHandle()
{
	return (PESDC)hBackBuffer;
}

LRESULT CALLBACK wndProc(HWND hWnd, UINT message, 
								WPARAM wParam, LPARAM lParam)
{
	switch ( message )
	{
	case WM_CHAR:
		{
			if( pEngine->getManager() != NULL )
			{
				pEngine->getManager()->wndProc( (PESWND)hWnd, message, wParam, lParam );
			}
		}
		break;

	case WM_DESTROY:
		{
			PostQuitMessage( 0 );
		}
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return S_OK;
}

esGdiEngine* Engine_Create( PESINSTANCE hInstance )
{
	if ( engineRef <= 0 )
	{
		hGameInst = (HINSTANCE)hInstance;
		pEngine = new esGdiEngine();
	}
	++engineRef;

	return pEngine;
}

void Engine_Release()
{
	--engineRef;
	if ( engineRef <= 0 )
	{
		delete pEngine;
	}
}

esGdiEngine::esGdiEngine()
:	Update( NULL ), Render( NULL ),
	m_clearColor( RGB( 255, 0, 0 ) ),
	m_screenWidth( 800 ), m_screenHeight( 600 ),
	m_FrameTime( 0.0f ), m_FrameStartTime( 0.0f ),
	m_FrameEndTime( 0.0f ), m_PassTime( 0.0f ),
	m_GetFpsDeltaTime( 0.0f ), m_GetFpsMaxTime( 0.0f )
{
	m_pManager = NULL;
	m_curKeyBuffer = new unsigned char[256];
	ZeroMemory( m_curKeyBuffer, sizeof(unsigned char)*256 );
	m_prevKeyBuffer = new unsigned char[256];
	ZeroMemory( m_prevKeyBuffer, sizeof(unsigned char)*256 );
}

esGdiEngine::~esGdiEngine()
{
	if ( backBmp )
	{
		DeleteObject( backBmp );
	}
	if ( clearBrush )
	{
		DeleteObject( clearBrush );
	}
	if ( hBackBuffer )
	{
		DeleteObject( hBackBuffer );
	}

	if ( hWnd )
	{
		DestroyWindow( hWnd );
	}

	SAFE_DELARR( m_curKeyBuffer );
	SAFE_DELARR( m_prevKeyBuffer );
}

void esGdiEngine::SetTitle( char *title )
{
	SetWindowText( hWnd, title );
}

void esGdiEngine::SetClearColor( unsigned int color )
{
	if ( m_clearColor != color )
	{
		m_clearColor = color;
		DeleteObject( clearBrush );
		clearBrush = CreateSolidBrush( m_clearColor );
	}
}

bool esGdiEngine::KeyDown( unsigned char key )
{
	if ( !(m_prevKeyBuffer[key] & 0x80) &&
		 (m_curKeyBuffer[key] & 0x80) )
	{
		return true;
	}
	return false;
}

bool esGdiEngine::KeyUp( unsigned char key )
{
	if ( (m_prevKeyBuffer[key] & 0x80) &&
		!(m_curKeyBuffer[key] & 0x80) )
	{
		return true;
	}
	return false;
}

bool esGdiEngine::KeyPress( unsigned char key )
{
	return (m_curKeyBuffer[key] & 0x80);
}

PTEXTURE esGdiEngine::Texture_Load( char *filename )
{
	HBITMAP texture = (HBITMAP)LoadImage( hInst, filename,
				IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );

	return (PTEXTURE)texture;
}

void esGdiEngine::Texture_Free( PTEXTURE tex )
{
	DeleteObject( (HGDIOBJ)tex );
}

int esGdiEngine::Texture_GetWidth( PTEXTURE tex )
{
	if ( tex )
	{
		GetObject( (HBITMAP)tex, sizeof(BITMAP), &bmpInfo );
		return bmpInfo.bmWidth;
	}

	return 0;
}

int esGdiEngine::Texture_GetHeight( PTEXTURE tex )
{
	if ( tex )
	{
		GetObject( (HBITMAP)tex, sizeof(BITMAP), &bmpInfo );
		return bmpInfo.bmHeight;
	}

	return 0;
}

void esGdiEngine::_Render_Clear()
{
	::FillRect( hBackBuffer, &clientRect, clearBrush );
}

void esGdiEngine::_Render_SwapBuffer()
{
	hMainBuffer = GetDC( hWnd );
	BitBlt( hMainBuffer, 0, 0, m_screenWidth, m_screenHeight, 
		hBackBuffer, 0, 0, SRCCOPY );
	ReleaseDC( hWnd, hMainBuffer );
}

void esGdiEngine::GetCursorPos( POINT &p )
{
	::GetCursorPos( &p );
	ScreenToClient( hWnd, &p );
}

float esGdiEngine::GetFps( float deltaTime )
{
	if ( deltaTime != m_GetFpsMaxTime )
	{
		m_GetFpsDeltaTime = deltaTime;
		m_GetFpsMaxTime = deltaTime;
		m_curFps = 1.0f/m_FrameTime;
	}
	else
	{
		m_GetFpsDeltaTime -= m_FrameTime;
		if( m_GetFpsDeltaTime <= 0.0f )
		{
			m_GetFpsDeltaTime += m_GetFpsMaxTime;
			m_curFps = 1.0f/m_FrameTime;
		}
	}

	return m_curFps;
}

void esGdiEngine::FillRect( const HBRUSH &brush, const RECT &r )
{
	::FillRect( hBackBuffer, &r, brush );
}

void esGdiEngine::DrawLine( const HPEN &pen, int sx, int sy, int ex, int ey )
{
	SelectObject( hBackBuffer, pen );
	MoveToEx( hBackBuffer, sx, sy, NULL );
	LineTo( hBackBuffer, ex, ey );
}

void esGdiEngine::DrawText( const HFONT &font, const char *str, RECT &r, 
						   UINT format /* = DT_CENTER | DT_VCENTER | DT_SINGLELINE */ )
{
	SelectObject( hBackBuffer, font );strlen(str);
	::DrawText( hBackBuffer, str, (int)strlen(str), &r, format );
}

void esGdiEngine::CalcRect( const HFONT &font, const char *str, RECT &r )
{
	SelectObject( hBackBuffer, font );
	::DrawText( hBackBuffer, str, (int)strlen(str), &r, DT_CALCRECT );
}

void esGdiEngine::Engine_Init()
{
	if( hWnd )
	{
		return;
	}

	hInst = GetModuleHandle( NULL );
	// 注册窗口类
	WNDCLASSEX wndClass;
	ZeroMemory( &wndClass, sizeof(WNDCLASSEX) );
	wndClass.cbSize = sizeof( WNDCLASSEX );
	wndClass.hInstance = hInst;
	wndClass.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;
	wndClass.lpfnWndProc = wndProc;
	wndClass.lpszClassName = "EsGdiEngine";
	wndClass.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;

	int ret = RegisterClassEx( &wndClass );

	// 计算窗口矩形
	RECT windowRect;
	windowRect.right = GetSystemMetrics( SM_CXSCREEN );
	windowRect.bottom = GetSystemMetrics( SM_CYSCREEN );
	windowRect.left = (windowRect.right - m_screenWidth)/2;
	windowRect.top = (windowRect.bottom - m_screenHeight)/2;
	windowRect.right = windowRect.left + m_screenWidth;
	windowRect.bottom = windowRect.top + m_screenHeight;

	m_screenX = windowRect.left;
	m_screenY = windowRect.top;

	// 创建窗口
	hWnd = CreateWindow( "EsGdiEngine", "EsGdiEngine", 
		(WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX), 
		windowRect.left, windowRect.top, m_screenWidth, m_screenHeight, 
		NULL, NULL, hInst, NULL  );

	CopyRect( &clientRect, &windowRect );
	AdjustWindowRectEx( &clientRect,
		GetWindowLong( hWnd, GWL_STYLE ),
		FALSE, GetWindowLong( hWnd, GWL_EXSTYLE ) );
	MoveWindow( hWnd, clientRect.left, clientRect.top,
				clientRect.right-clientRect.left, 
				clientRect.bottom-clientRect.top,true);

	ShowWindow( hWnd, SW_SHOWNORMAL );
	UpdateWindow( hWnd );

	GetClientRect( hWnd, &clientRect );

	hMainBuffer = GetDC( hWnd );
	backBmp = CreateCompatibleBitmap( hMainBuffer, m_screenWidth, m_screenHeight );
	ReleaseDC( hWnd, hMainBuffer );

	hBackBuffer = CreateCompatibleDC( NULL );
	SelectObject( hBackBuffer, backBmp );

	clearBrush = CreateSolidBrush( m_clearColor );
}

void esGdiEngine::Engine_Start()
{
	MSG msg = {0};
	m_FrameEndTime = timeGetTime()/1000.0f;
	while( msg.message != WM_QUIT )
	{
		m_FrameStartTime = m_FrameEndTime;
		if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}

		// 更新按键状态
		swap( &m_prevKeyBuffer, &m_curKeyBuffer );
		GetKeyboardState( m_curKeyBuffer );

		if( Update )
		{
			// update函数返回true，结束进程
			if( Update() )
			{
				break;
			}
		}

		_Render_Clear();
		if ( Render )
		{
			Render();
		}
		_Render_SwapBuffer();

		// 更新帧时间信息
		m_FrameEndTime = timeGetTime()/1000.0f;
		m_FrameTime = m_FrameEndTime-m_FrameStartTime;
		m_PassTime += m_FrameTime;
	}
}

int esGdiEngine::CalcTextHeight( const HFONT &font )
{
	SelectObject(hBackBuffer,font);
	TEXTMETRIC TextMetric;
	GetTextMetrics(hBackBuffer,&TextMetric);
	return TextMetric.tmHeight;
}

int esGdiEngine::CalcLastLineLength( const HFONT &font, const char *str )
{
	SelectObject(hBackBuffer,font);
	return calcOneLineTextWidth( hBackBuffer, getStringLastLinePos( str ) );
}

