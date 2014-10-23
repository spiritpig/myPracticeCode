// drawStarAnyAngle141021.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "drawStarAnyAngle141021.h"
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HFONT hfont;

#define ANGLE (3.1415926/180.0f)

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void drawStar( HDC hdc, int left, int top, int right, int bottom, int angleNum = 5,
			   int pensize = 5, COLORREF color = RGB(128,255,128),
			   float initAngle = 0.0f);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	hfont = CreateFont( 50, 30, 0, 0, 10, 0, 0, 0, GB2312_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"方正舒体" );

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAWSTARANYANGLE141021, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DRAWSTARANYANGLE141021);

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	DeleteObject( hfont );
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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DRAWSTARANYANGLE141021);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_DRAWSTARANYANGLE141021;
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
	static POINT mousePos = { 0, 0 };
	LONG radius = 100;
	static float angle = 0.0f;

	switch (message) 
	{
	case WM_CREATE:
		{
			SetTimer( hWnd, 1, 50, NULL );
		}
		break;

	case WM_TIMER:
		{
			hdc = GetDC( hWnd );
			SelectObject( hdc, hfont );

			// 擦掉旧的星星和字体
			drawStar( hdc, mousePos.x-radius, mousePos.y-radius, 
				mousePos.x+radius, mousePos.y+radius,
				6, 5, RGB(255, 255, 255), angle );
			SetTextColor( hdc, RGB( 255, 255, 255 ) );
			TextOut( hdc, mousePos.x - radius, mousePos.y+radius, "星星图案", 8 );

			// 画新的星星和字体
			GetCursorPos( &mousePos );
			ScreenToClient( hWnd, &mousePos );

			drawStar( hdc, mousePos.x-radius, mousePos.y-radius, 
						mousePos.x+radius, mousePos.y+radius,
						6, 5, RGB(128, 255, 128), angle+=0.05f );
			SetTextColor( hdc, RGB( 128, 255, 128 ) );
			TextOut( hdc, mousePos.x - radius, mousePos.y+radius, "星星图案", 8 );

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

void drawStar( HDC hdc, int left, int top, int right, int bottom, int angleNum, 
			   int pensize /*= 5*/, COLORREF color /*= RGB(128,255, 128)*/, 
			   float initAngle /*= 0.0f*/ )
{
	int radius = (right-left)/2;
	POINT center = { left + radius, top + radius },
		startPos = { 0, -radius };
	POINT *pArray = new POINT[angleNum];
	float angleOffset = (float)(ANGLE*(360.0f/angleNum));
	int type = 2;

	//////////////////////////////////////////////////////////////////////////
	//
	//	1、 确定起始点， 最上方的那个顶点
	//  2、 做一条选段，起始点为星形的中心点，终点为确定好的起始点
	//  3、 按一定角度旋转这条线段，角度为 (360/angleNum)
	//	4、 连线
	//
	//////////////////////////////////////////////////////////////////////////

// 	this->x = this->x*cosf(angle) - this->y*sinf(angle);
// 	this->y = tempX  *sinf(angle) + this->y*cosf(angle);

	for (int i=0; i<angleNum; ++i)
	{
		pArray[i].x = (LONG)(startPos.x*cosf( i*angleOffset + initAngle ) - 
					startPos.y*sinf( i*angleOffset + initAngle ) + center.x);
		pArray[i].y = (LONG)(startPos.x*sinf( i*angleOffset + initAngle ) + 
					startPos.y*cosf( i*angleOffset + initAngle ) + center.y);
	}

	HPEN hpen = CreatePen( 0, pensize, color );
	SelectObject( hdc, hpen );

	int endIndex = 0;
	for ( int j=0; j<angleNum; ++j )
	{
		endIndex = (j+type)%angleNum;
		MoveToEx( hdc, pArray[j].x, pArray[j].y, NULL );
		LineTo( hdc, pArray[endIndex].x, pArray[endIndex].y );
	}

	DeleteObject( hpen );
	delete []pArray;
}
