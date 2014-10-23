// drawEllipsemy.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "drawEllipsemy.h"
#define MAX_LOADSTRING 100
#define ANGLE (3.1415926f/180.0f)

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void				myDrawEllipse( HDC hdc, int left, int top, 
								   int right, int bottom, int dividePercent );
void				draw4AngleStar( HDC hdc, int x, int y, int size, float factor );


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAWELLIPSEMY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DRAWELLIPSEMY);

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DRAWELLIPSEMY);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_DRAWELLIPSEMY;
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
   HWND hWnd;

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
	static float factor = 1.0f;
	static float factorOffset = 0.4f;

	switch (message) 
	{
	case WM_CREATE:
		{
			SetTimer( hWnd, 1, 100, NULL );
		}
		break;

	case WM_TIMER:
		{
			if ( factor >= 10.0f ||
				 factor < 1.0f )
			{
				factorOffset = -factorOffset;
			}

			hdc = GetDC( hWnd );
			HPEN hbgpen = CreatePen( 0, 5, RGB( 255, 255, 255 ) );
			HPEN hpen = CreatePen( 0, 5, RGB( 128, 255, 128 ) );

			// 擦掉旧的星星
			SelectObject( hdc, hbgpen );
			draw4AngleStar( hdc, 200, 200, 100, factor );

			// 新的图形
			SelectObject( hdc, hpen );
			myDrawEllipse( hdc, 100, 100, 300, 300, 60 );
			factor += factorOffset;
			draw4AngleStar( hdc, 200, 200, 100, factor );

			DeleteObject( hpen );
			DeleteObject( hbgpen );
			ReleaseDC( hWnd, hdc );
		}
		break;

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
		{
			KillTimer( hWnd, 1 );
			PostQuitMessage(0);
		}
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

void myDrawEllipse( HDC hdc, int left, int top, int right, int bottom,
				    int divideFactor )
{
	float offsetAngle = (360.0f/divideFactor);
	int longRadius = (right-left)/2;
	int shortRadius = (bottom-top)/2;

	POINT middlePoint = { left+longRadius, top+shortRadius };
	POINT curP = { (LONG)(longRadius*cosf( 0 ) + middlePoint.x), 
					(LONG)(shortRadius*sinf( 0 ) + middlePoint.y) };

	MoveToEx( hdc, curP.x, curP.y, NULL );
	for ( int i=1; i<divideFactor; ++i )
	{
		curP.x = (LONG)(longRadius*cosf( offsetAngle*i*ANGLE ) + middlePoint.x);
		curP.y = (LONG)(shortRadius*sinf( offsetAngle*i*ANGLE ) + middlePoint.y); 
		//SetPixel( hdc, curP.x, curP.y, color );
		LineTo( hdc, curP.x, curP.y );
	}
	LineTo( hdc, (LONG)(longRadius*cosf( 0 ) + middlePoint.x), 
		         (LONG)(shortRadius*sinf( 0 ) + middlePoint.y) );
}

void draw4AngleStar( HDC hdc, int x, int y, int size, float factor )
{
	POINT pArray[8], middlePoint = { x, y };

	// 计算外围的四个点
	pArray[0].x = middlePoint.x;
	pArray[0].y = y-size;

	pArray[2].x = x+size;
	pArray[2].y = middlePoint.y;

	pArray[4].x = middlePoint.x;
	pArray[4].y = y+size;

	pArray[6].x = x-size;
	pArray[6].y = middlePoint.y;

	// 计算内圈的四个点
	float ratio = 0.8f/3.6f;
	pArray[1].x = pArray[0].x + (LONG)(ratio*size/factor);
	pArray[1].y = pArray[0].y + (LONG)((1.0f-ratio)*size/factor);

	pArray[3].x = pArray[2].x - (LONG)((1.0f-ratio)*size/factor);
	pArray[3].y = pArray[2].y + (LONG)(ratio*size/factor);

	pArray[5].x = pArray[4].x - (LONG)(ratio*size/factor);
	pArray[5].y = pArray[4].y - (LONG)((1.0f-ratio)*size/factor);

	pArray[7].x = pArray[6].x + (LONG)((1.0f-ratio)*size/factor);
	pArray[7].y = pArray[6].y - (LONG)(ratio*size/factor);

	// 连线
	MoveToEx( hdc, pArray[0].x, pArray[0].y, NULL );
	for ( int i=1; i<8; ++i )
	{
		LineTo( hdc, pArray[i].x, pArray[i].y );
	}
	LineTo( hdc, pArray[0].x, pArray[0].y );
}
