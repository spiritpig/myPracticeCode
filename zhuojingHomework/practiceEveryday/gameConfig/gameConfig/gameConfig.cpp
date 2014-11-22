// gameConfig.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "gameConfig.h"
#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
HWND hWnd;
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

//////////////////////////////////////////////////////////////////////////
HWND hConfigBtn;
HWND hCommitBtn;
HWND hCancleBtn;

HWND hDisplayModeText;
HWND hAspectRatioText;
HWND hSpecialSettingText;

HWND hFullSBtn;
HWND hWinDBtn;

HWND hRate1Btn;
HWND hRate2Btn;
HWND hRate3Btn;

HWND hHardABtn;
HWND hRateSBtn;

char buffer[1024];
//////////////////////////////////////////////////////////////////////////


// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
VOID				InitControl();
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
VOID				ReadConfigFile( char *filename );
VOID				WriteConfigFile( char *filename );

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: �ڴ˷��ô��롣
	MSG msg;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GAMECONFIG, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_GAMECONFIG);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_GAMECONFIG;
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

   hWnd = CreateWindow(szWindowClass, szTitle, 
	   (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ),
      CW_USEDEFAULT, 0, 380, 250, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   InitControl();
   ReadConfigFile( "./config.ini" );

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

VOID InitControl()
{
	hDisplayModeText=CreateWindow("static","��ʾģʽ",WS_CHILD|WS_VISIBLE,
		10,10,60,18,hWnd,(HMENU)IDC_STATIC,hInst,NULL);
	hFullSBtn=CreateWindow("button","ȫ��",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|WS_GROUP,
		75,10,50,16,hWnd,(HMENU)IDBTN_FULLSCREEN,hInst,NULL);
	hWinDBtn=CreateWindow("button","����",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,
		75,35,50,16,hWnd,(HMENU)IDBTN_WINDOWED,hInst,NULL);

	hAspectRatioText=CreateWindow("static","��ʾ�ֱ���",WS_CHILD|WS_VISIBLE,
		170,10,75,18,hWnd,(HMENU)IDC_STATIC,hInst,NULL);
	hRate1Btn=CreateWindow("button","640x480",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON|WS_GROUP,
		250,10,76,16,hWnd,(HMENU)IDBTN_RATE1,hInst,NULL);
	hRate2Btn=CreateWindow("button","800x600",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,
		250,35,76,16,hWnd,(HMENU)IDBTN_RATE2,hInst,NULL);
	hRate3Btn=CreateWindow("button","1024x768",WS_CHILD|WS_VISIBLE|BS_AUTORADIOBUTTON,
		250,60,86,16,hWnd,(HMENU)IDBTN_RATE3,hInst,NULL);

	hSpecialSettingText=CreateWindow("static","��������",WS_CHILD|WS_VISIBLE,
		10,85,60,18,hWnd,(HMENU)IDC_STATIC,hInst,NULL);
	hHardABtn=CreateWindow("button","����Ӳ������",WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,
		40,110,110,16,hWnd,(HMENU)IDBTN_HARDACCEL,hInst,NULL);
	hRateSBtn=CreateWindow("button","���ô�ֱͬ��",WS_CHILD|WS_VISIBLE|BS_AUTOCHECKBOX,
		40,135,110,16,hWnd,(HMENU)IDBTN_VSYNC,hInst,NULL);

	hConfigBtn=CreateWindow("button","����",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		10,180,50,20,hWnd,(HMENU)IDBTN_CONFIG,hInst,NULL);
	hCommitBtn=CreateWindow("button","ȷ��",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		230,180,50,20,hWnd,(HMENU)IDBTN_COMMIT,hInst,NULL);
	hCancleBtn=CreateWindow("button","ȡ��",WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
		290,180,50,20,hWnd,(HMENU)IDBTN_CANCLE,hInst,NULL);
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
	case WM_CLOSE:
		{
// 			DestroyWindow( hDisplayModeText );
// 			DestroyWindow( hFullSBtn );
// 			DestroyWindow( hWinDBtn ); 
// 
// 			DestroyWindow( hAspectRatioText );
// 			DestroyWindow( hRate1Btn );
// 			DestroyWindow( hRate2Btn );
// 			DestroyWindow( hRate3Btn );
// 
// 			DestroyWindow( hSpecialSettingText );
// 			DestroyWindow( hHardABtn );
// 			DestroyWindow( hRateSBtn );
// 
// 			DestroyWindow( hConfigBtn );
// 			DestroyWindow( hCommitBtn );  
// 			DestroyWindow( hCancleBtn );
			DestroyWindow( hWnd );
		}
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDBTN_CANCLE:
			{
				DestroyWindow( hWnd );
			}
			break;
			
		case IDBTN_COMMIT:
			{
				WriteConfigFile( "./config.ini" );
				DestroyWindow( hWnd );
			}
			break;

		case IDBTN_CONFIG:
			{
				WriteConfigFile( "./config.ini" );
			}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint( hWnd, &ps );
			EndPaint( hWnd, &ps );
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

VOID ReadConfigFile( char *filename )
{
	GetPrivateProfileString( "config", "windowMode", "windowed", buffer, 1024, filename );
	if ( strcmp( buffer, "fullscreen" ) == 0 )
	{
		CheckDlgButton( hWnd, IDBTN_FULLSCREEN, BST_CHECKED );
	}
	else
	{
		CheckDlgButton( hWnd, IDBTN_WINDOWED, BST_CHECKED );
	}

	GetPrivateProfileString( "config", "aspectRatio", "640X480", buffer, 1024, filename );
	if ( strcmp( buffer, "640X480" ) == 0 )
	{
		CheckDlgButton( hWnd, IDBTN_RATE1, BST_CHECKED );
	}
	else
	if ( strcmp( buffer, "800X600" ) == 0 )
	{
		CheckDlgButton( hWnd, IDBTN_RATE2, BST_CHECKED );
	}
	else
	{
		CheckDlgButton( hWnd, IDBTN_RATE3, BST_CHECKED );
	}

	GetPrivateProfileString( "config", "hardwareAccelarate", "true", buffer, 1024, filename );
	if ( strcmp( buffer, "true" ) == 0 )
	{
		CheckDlgButton( hWnd, IDBTN_HARDACCEL, BST_CHECKED );
	}

	GetPrivateProfileString( "config", "verticalSync", "true", buffer, 1024, filename );
	if ( strcmp( buffer, "true" ) == 0 )
	{
		CheckDlgButton( hWnd, IDBTN_VSYNC, BST_CHECKED );
	}
}

VOID WriteConfigFile( char *filename )
{
	// д�봰��ģʽ
	if ( IsDlgButtonChecked( hWnd, IDBTN_FULLSCREEN ) )
	{
		WritePrivateProfileString( "config", "windowMode", 
						"fullscreen", filename );
	}
	else
	{
		WritePrivateProfileString( "config", "windowMode", 
						"windowed", filename );
	}

	// д����ʾ�ֱ���
	if ( IsDlgButtonChecked( hWnd, IDBTN_RATE1 ) )
	{
		WritePrivateProfileString( "config", "aspectRatio", 
						"640X480", filename );
	}
	else
	if ( IsDlgButtonChecked( hWnd, IDBTN_RATE2 ) )
	{
		WritePrivateProfileString( "config", "aspectRatio", 
						"800X600", filename );
	}
	else
	{
		WritePrivateProfileString( "config", "aspectRatio", 
						"1024X768", filename );
	}

	// д����������
	if ( IsDlgButtonChecked( hWnd, IDBTN_HARDACCEL ) )
	{
		WritePrivateProfileString( "config", "hardwareAccelarate", 
						"true", filename );
	}
	else
	{
		WritePrivateProfileString( "config", "hardwareAccelarate", 
						"false", filename );
	}

	// д����������
	if ( IsDlgButtonChecked( hWnd, IDBTN_VSYNC ) )
	{
		WritePrivateProfileString( "config", "verticalSync", 
									"true", filename );
	}
	else
	{
		WritePrivateProfileString( "config", "verticalSync", 
									"false", filename );
	}
}

