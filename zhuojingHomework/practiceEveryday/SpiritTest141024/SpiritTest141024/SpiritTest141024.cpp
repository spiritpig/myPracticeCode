// SpiritTest141024.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "SpiritTest141024.h"
#define MAX_LOADSTRING 100
#define KEYDOWN(k) ( GetKeyState(k) & 0x80 )

// ȫ�ֱ���:
HWND hWnd = NULL;
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

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

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: �ڴ˷��ô��롣
	MSG msg;

	// ������Դ
	hBGbmp = (HBITMAP)LoadImage( NULL, "image/bg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	hBGdc = CreateCompatibleDC( NULL );
	SelectObject( hBGdc, hBGbmp );

	gdiSpirit roleSpi( "image/role.bmp", 32, 32, RGB(0, 255, 0) );
// 	hRolebmp = (HBITMAP)LoadImage( NULL, "image/role.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
// 	hRoleDc = CreateCompatibleDC( NULL ); 
// 	SelectObject( hRoleDc, hRolebmp );

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SPIRITTEST141024, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	RECT r;
	GetClientRect( hWnd, &r );
	hBackBufferbmp = (HBITMAP)CreateBitmap( r.right-r.left, r.bottom-r.top, 1, 32, NULL  );
	hBackBufferdc = CreateCompatibleDC( NULL );
	SelectObject( hBackBufferdc, hBackBufferbmp );

	// ����Ϣѭ��:
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

		// �����Ƶ�������䵽��Ļ��
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
	//	ɾ������������GDI����
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��: 
//
//    ����ϣ��������ӵ� Windows 95 ��
//    ��RegisterClassEx������֮ǰ�˴����� Win32 ϵͳ����ʱ��
//    ����Ҫ�˺��������÷������ô˺���
//    ʮ����Ҫ������Ӧ�ó���Ϳ��Ի�ù�����
//   ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ����: InitInstance(HANDLE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, unsigned, WORD, LONG)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
		// TODO: �ڴ���������ͼ����...
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

// �����ڡ������Ϣ�������
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
