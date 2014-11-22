// SpiritTest141024.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "SpiritTest141024.h"
#define MAX_LOADSTRING 100
#define KEYDOWN(k) ( GetKeyState(k) & 0x80 )

// 全局变量:
HWND hWnd = NULL;
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

//////////////////////////////////////////////////////////////////////////
HDC hMaindc;
HDC hBGdc;
HBITMAP hBGbmp;
// HDC hRoleDc;
// HBITMAP hRolebmp;
HDC hBackBufferdc;
HBITMAP hBackBufferbmp;

float rolex = 0.0f, roley = 0.0f;
float frameStartTime = 0.0f, frameEndTime = 0.0f,
	  frameTime = 0.0f;
float roleSpeed = 100.0f;
//////////////////////////////////////////////////////////////////////////

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: 在此放置代码。
	MSG msg;

	// 加载资源
	hBGbmp = (HBITMAP)LoadImage( NULL, "image/bg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBGdc = CreateCompatibleDC( NULL );
	SelectObject( hBGdc, hBGbmp );

	gdiSpirit roleSpi( "image/role.bmp", 32, 32, RGB(0, 255, 0) );
// 	hRolebmp = (HBITMAP)LoadImage( NULL, "image/role.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
// 	hRoleDc = CreateCompatibleDC( NULL ); 
// 	SelectObject( hRoleDc, hRolebmp );

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SPIRITTEST141024, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	RECT r;
	GetClientRect( hWnd, &r );
	hBackBufferbmp = (HBITMAP)CreateBitmap( r.right-r.left, r.bottom-r.top, 1, 32, NULL  );
	hBackBufferdc = CreateCompatibleDC( NULL );
	SelectObject( hBackBufferdc, hBackBufferbmp );

	// 主消息循环:
	ZeroMemory( &msg, sizeof( MSG ) );
	roleSpi.setState( 0, 1 );
	frameEndTime = timeGetTime()/1000.0f;
	while ( msg.message != WM_QUIT ) 
	{
		frameStartTime = frameEndTime;
		if (PeekMessage( &msg, NULL, 0, 0, PM_REMOVE )) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		GetClientRect( hWnd, &r );
		BitBlt( hBackBufferdc, 0, 0, r.right-r.left, r.bottom-r.top, 
			hBGdc, 0, 0, SRCCOPY );
		roleSpi.render( hBackBufferdc, (int)rolex, (int)roley );
// 		TransparentBlt( hBackBufferdc, (int)rolex, (int)roley, 32, 32,
// 			hRoleDc, 0, 0, 32, 32, RGB(0, 255, 0) );

		// 将绘制的内容填充到屏幕上
		hMaindc = GetDC( hWnd );

		BitBlt( hMaindc, 0, 0, r.right-r.left, r.bottom-r.top, 
			hBackBufferdc, 0, 0, SRCCOPY );

		ReleaseDC( hWnd, hMaindc );

		if ( KEYDOWN('W') )
		{
			roley -= roleSpeed * frameTime;
		}
		else
		if( KEYDOWN('S') )
		{
			roley += roleSpeed * frameTime;
		}

		if ( KEYDOWN('A') )
		{
			rolex -= roleSpeed * frameTime;
		}
		else
		if( KEYDOWN('D') )
		{
			rolex += roleSpeed * frameTime;
		}

		frameEndTime = timeGetTime()/1000.0f;
		frameTime = frameEndTime - frameStartTime;
	}

	//////////////////////////////////////////////////////////////////////////
	//	删除创建出来的GDI对象
	//////////////////////////////////////////////////////////////////////////
	DeleteObject( hBGdc );
	DeleteObject( hBGbmp );
// 	DeleteObject( hRoleDc );
// 	DeleteObject( hRolebmp );
	DeleteObject( hBackBufferdc );
	DeleteObject( hBackBufferbmp );

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释: 
//
//    仅当希望在已添加到 Windows 95 的
//    “RegisterClassEx”函数之前此代码与 Win32 系统兼容时，
//    才需要此函数及其用法。调用此函数
//    十分重要，这样应用程序就可以获得关联的
//   “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_SPIRITTEST141024);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_SPIRITTEST141024;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HANDLE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, unsigned, WORD, LONG)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
