#include <Windows.h>
#include <tchar.h>
#include <OleDlg.h>
#include "resource.h"

HINSTANCE hInst;
HWND hWnd, diaHwnd;
TCHAR wndClassName[99] = _T("windowsTest"),
	  diaClassName[99] = _T("myDialog");

void createDialogBox()
{
	//////////////////////////////////////////////////////////////////////////
	//	�����Ի��򴰿�
	//////////////////////////////////////////////////////////////////////////
	diaHwnd = CreateWindow(diaClassName, "dialog", 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU , 
		CW_USEDEFAULT, 0, 300, 180, hWnd, NULL, hInst, NULL);

	ShowWindow( diaHwnd, SW_NORMAL );
	UpdateWindow( diaHwnd );
}

//////////////////////////////////////////////////////////////////////////
// ���ڹ��̴�����
//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK wndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
 	{
	case WM_COMMAND:
		{
			switch ( LOWORD( wParam ) )
			{
				// �����ڲ˵����˳���Ϣ
			case ID_FILE_EXIT :
				{
					if ( MessageBox( hWnd, "���Ҫ�˳���", "��ʾ", 
									MB_YESNO | MB_ICONQUESTION ) == IDYES )
					{
						DestroyWindow(hWnd);
					}
				}
				break;

			case ID_ABOUTUS_VERSION:
				{
					createDialogBox();
				}
				break;
			}
		}
		break;

		// ����ϵͳ�ؼ����˳���Ϣ
	case WM_SYSCOMMAND:
		{
			switch( wParam )
			{
			case SC_CLOSE:
				{
					if ( MessageBox( hWnd, "���Ҫ�˳���", "��ʾ", 
						MB_YESNO | MB_ICONQUESTION ) == IDYES )
					{
						DestroyWindow(hWnd);
					}
				}
				break;

			default:
				return DefWindowProc( hWnd, message, wParam, lParam );
			}
		}
		break;

	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return S_OK;
}


LRESULT CALLBACK diaWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	RECT rect = { 10, 10, 200, 100 },
		okButtonRect = { 200, 100, 260, 130 },
		okButtonTextRect = { 205, 105, 255, 125 };
	HDC hdc = GetDC( hWnd );

	switch ( message )
	{
	case WM_QUIT:
		{
			DestroyWindow(hWnd);
		}
		break;

	case WM_LBUTTONDOWN:
		{
			switch ( wParam )
			{
			case MK_LBUTTON:
				{
					static POINT mousePos;
					mousePos.x = LOWORD(lParam);
					mousePos.y = HIWORD(lParam);

					if ( mousePos.x < okButtonRect.right && mousePos.x > okButtonRect.left &&
						 mousePos.y < okButtonRect.bottom && mousePos.y > okButtonRect.top )
					{
						DestroyWindow(diaHwnd);
					}
				}
				break;
			}
		}
		break;

	case WM_PAINT:
		{
			BeginPaint( diaHwnd, &ps );

			// ����������ʾ
			static char content[99];
			strcpy( content, "����һ�����ƶԻ���" );
			DrawText( hdc, content, -1, &rect, DT_LEFT );

			// ���ư�ť
			Rectangle( hdc, okButtonRect.left, okButtonRect.top,
				okButtonRect.right, okButtonRect.bottom );
			strcpy( content, "ȷ��" );
			DrawText( hdc, content, -1, &okButtonTextRect, DT_CENTER | DT_VCENTER );


			EndPaint( hWnd, &ps );
		}
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	}

	return S_OK;
}

int WINAPI _tWinMain( IN HINSTANCE hInstance, 
					  IN HINSTANCE hPrevInstance, 
					  IN LPSTR lpCmdLine, 
					  IN int nShowCmd )
{
	hInst = hInstance;

	//////////////////////////////////////////////////////////////////////////
	//	ע�ᴰ����
	//////////////////////////////////////////////////////////////////////////
	WNDCLASSEX wndex;
	wndex.cbSize = sizeof(wndex);
	wndex.style = CS_HREDRAW | CS_VREDRAW;
	wndex.hbrBackground = (HBRUSH)COLOR_WINDOW+5;
	wndex.hInstance = hInst;
	wndex.lpszClassName = wndClassName;
	wndex.lpszMenuName = (LPCSTR)IDR_MENU1;
	wndex.lpfnWndProc = wndProc;
	wndex.hCursor = LoadCursor( NULL, IDC_HAND );
	wndex.hIcon = LoadIcon( NULL, IDI_WINLOGO );
	wndex.hIconSm = LoadIcon( NULL, IDI_WINLOGO );
	wndex.cbWndExtra = NULL;
	wndex.cbClsExtra = NULL;

	RegisterClassEx( &wndex );



	//////////////////////////////////////////////////////////////////////////
	//	ע��Ի��򴰿���
	//////////////////////////////////////////////////////////////////////////
	WNDCLASSEX wndexDig;
	wndexDig.cbSize = sizeof(wndex);
	wndexDig.style = CS_HREDRAW | CS_VREDRAW;
	wndexDig.hbrBackground = (HBRUSH)COLOR_WINDOW+5;
	wndexDig.hInstance = hInst;
	wndexDig.lpszClassName = diaClassName;
	wndexDig.lpszMenuName = NULL;
	wndexDig.lpfnWndProc = diaWndProc;
	wndexDig.hCursor = NULL;
	wndexDig.hIcon = NULL;
	wndexDig.hIconSm = NULL;
	wndexDig.cbWndExtra = NULL;
	wndexDig.cbClsExtra = NULL;

	RegisterClassEx( &wndexDig );



	//////////////////////////////////////////////////////////////////////////
	//	��������
	//////////////////////////////////////////////////////////////////////////
	hWnd = CreateWindow(wndClassName, "sqbturFight", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInst, NULL);

	ShowWindow( hWnd, nShowCmd );
	UpdateWindow( hWnd );



	//////////////////////////////////////////////////////////////////////////
	//	����Ϣѭ��
	//////////////////////////////////////////////////////////////////////////
	MSG msg;
	while ( GetMessage( &msg, NULL, 0, 0 ) )
	{
		DispatchMessage( &msg );
	}

	return (int)msg.wParam;
}