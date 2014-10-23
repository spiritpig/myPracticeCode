// drawStarAnyAngle141021.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "drawStarAnyAngle141021.h"
#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HFONT hfont;

#define ANGLE (3.1415926/180.0f)

// �˴���ģ���а����ĺ�����ǰ������:
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
 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	hfont = CreateFont( 50, 30, 0, 0, 10, 0, 0, 0, GB2312_CHARSET, 
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH,
		"��������" );

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAWSTARANYANGLE141021, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DRAWSTARANYANGLE141021);

	// ����Ϣѭ��:
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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DRAWSTARANYANGLE141021);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_DRAWSTARANYANGLE141021;
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
   HWND hWnd;

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

			// �����ɵ����Ǻ�����
			drawStar( hdc, mousePos.x-radius, mousePos.y-radius, 
				mousePos.x+radius, mousePos.y+radius,
				6, 5, RGB(255, 255, 255), angle );
			SetTextColor( hdc, RGB( 255, 255, 255 ) );
			TextOut( hdc, mousePos.x - radius, mousePos.y+radius, "����ͼ��", 8 );

			// ���µ����Ǻ�����
			GetCursorPos( &mousePos );
			ScreenToClient( hWnd, &mousePos );

			drawStar( hdc, mousePos.x-radius, mousePos.y-radius, 
						mousePos.x+radius, mousePos.y+radius,
						6, 5, RGB(128, 255, 128), angle+=0.05f );
			SetTextColor( hdc, RGB( 128, 255, 128 ) );
			TextOut( hdc, mousePos.x - radius, mousePos.y+radius, "����ͼ��", 8 );

			ReleaseDC( hWnd, hdc );
		}
		break;

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
	//	1�� ȷ����ʼ�㣬 ���Ϸ����Ǹ�����
	//  2�� ��һ��ѡ�Σ���ʼ��Ϊ���ε����ĵ㣬�յ�Ϊȷ���õ���ʼ��
	//  3�� ��һ���Ƕ���ת�����߶Σ��Ƕ�Ϊ (360/angleNum)
	//	4�� ����
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
