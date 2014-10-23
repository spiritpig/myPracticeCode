// drawEllipsemy.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "drawEllipsemy.h"
#define MAX_LOADSTRING 100
#define ANGLE (3.1415926f/180.0f)

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
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
 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAWELLIPSEMY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DRAWELLIPSEMY);

	// ����Ϣѭ��:
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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_DRAWELLIPSEMY);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_DRAWELLIPSEMY;
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

			// �����ɵ�����
			SelectObject( hdc, hbgpen );
			draw4AngleStar( hdc, 200, 200, 100, factor );

			// �µ�ͼ��
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

	// ������Χ���ĸ���
	pArray[0].x = middlePoint.x;
	pArray[0].y = y-size;

	pArray[2].x = x+size;
	pArray[2].y = middlePoint.y;

	pArray[4].x = middlePoint.x;
	pArray[4].y = y+size;

	pArray[6].x = x-size;
	pArray[6].y = middlePoint.y;

	// ������Ȧ���ĸ���
	float ratio = 0.8f/3.6f;
	pArray[1].x = pArray[0].x + (LONG)(ratio*size/factor);
	pArray[1].y = pArray[0].y + (LONG)((1.0f-ratio)*size/factor);

	pArray[3].x = pArray[2].x - (LONG)((1.0f-ratio)*size/factor);
	pArray[3].y = pArray[2].y + (LONG)(ratio*size/factor);

	pArray[5].x = pArray[4].x - (LONG)(ratio*size/factor);
	pArray[5].y = pArray[4].y - (LONG)((1.0f-ratio)*size/factor);

	pArray[7].x = pArray[6].x + (LONG)((1.0f-ratio)*size/factor);
	pArray[7].y = pArray[6].y - (LONG)(ratio*size/factor);

	// ����
	MoveToEx( hdc, pArray[0].x, pArray[0].y, NULL );
	for ( int i=1; i<8; ++i )
	{
		LineTo( hdc, pArray[i].x, pArray[i].y );
	}
	LineTo( hdc, pArray[0].x, pArray[0].y );
}
