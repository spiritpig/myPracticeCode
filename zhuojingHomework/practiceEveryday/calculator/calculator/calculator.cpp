// calculator.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "calculator.h"
#define MAX_LOADSTRING 100
#define MAX_OP_NUM 4
#define FLOAT_PERCENT	0.01f

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
HWND hWnd = NULL;
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

//////////////////////////////////////////////////////////////////////////
// ���������
//////////////////////////////////////////////////////////////////////////
HWND hNum[10];
HWND hOp[MAX_OP_NUM];
HWND hEqual, hClear, 
	 hClearCur, hBackSpace,
	 hSign;
HWND hEdit;

char strBuffer[1024];
CALC_STATE curCalcState = CS_LEFT;
CALC_OPERATOR curOP = COP_ADD, tempOp = COP_ADD;
float leftNum = 0.0f, rightNum = 0.0f;

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
void				InitCalculatorControl();
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
void				calcResultByOperator();
void				getCurOp( short wmId, CALC_OPERATOR &cop );
bool				isFloatEqualToZero( float f );

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: �ڴ˷��ô��롣
	MSG msg;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CALCULATOR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	
	InitCalculatorControl();

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
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_CALCULATOR);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
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
      CW_USEDEFAULT, 0, 200, 320, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void InitCalculatorControl()
{
	hEdit = CreateWindowEx( WS_EX_STATICEDGE, "edit", "0.00", 
		WS_CHILD | WS_VISIBLE | ES_RIGHT | ES_READONLY,
		5, 5, 175, 40, hWnd, (HMENU)ID_EDIT, hInst, NULL  );
	
	hClear = CreateWindow( "button", "C", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		5, 50, 40, 40, hWnd, (HMENU)IDBTN_CLEAR, hInst, NULL  );

	hClearCur = CreateWindow( "button", "CE", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		50, 50, 40, 40, hWnd, (HMENU)IDBTN_CLEARCUR, hInst, NULL  );

	hBackSpace = CreateWindow( "button", "��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		95, 50, 40, 40, hWnd, (HMENU)IDBTN_BACKSPACE, hInst, NULL  );
	// ��ʼ�� ���ְ�ť
	for ( int i=1; i<10; ++i )
	{
		sprintf( strBuffer, "%d", i );
		hNum[i] = CreateWindow( "button", strBuffer, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			45*((i-1)%3)+5, 45*((i-1)/3)+95, 40, 40, hWnd, (HMENU)(IDBTN_NUM0+i), hInst, NULL  );
	}
	hNum[0] = CreateWindow( "button", "0", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		5, 230, 85, 40, hWnd, (HMENU)IDBTN_NUM0, hInst, NULL  );


	// ��ʼ�� �������ť
	hOp[0] = CreateWindow( "button", "+", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		140, 50, 40, 40, hWnd, (HMENU)IDBTN_OP_ADD, hInst, NULL  );
	hOp[1] = CreateWindow( "button", "-", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		140, 95, 40, 40, hWnd, (HMENU)IDBTN_OP_SUB, hInst, NULL  );
	hOp[2] = CreateWindow( "button", "*", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		140, 140, 40, 40, hWnd, (HMENU)IDBTN_OP_MUL, hInst, NULL  );
	hOp[3] = CreateWindow( "button", "/", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		140, 185, 40, 40, hWnd, (HMENU)IDBTN_OP_DIV, hInst, NULL  );

	// ���������
	hSign = CreateWindow( "button", "��", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		95, 230, 40, 40, hWnd, (HMENU)IDBTN_SIGN, hInst, NULL  );

	// ���������
	hEqual = CreateWindow( "button", "=", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		140, 230, 40, 40, hWnd, (HMENU)IDBTN_EQUAL, hInst, NULL  );
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
			DestroyWindow( hEqual );
			DestroyWindow( hSign );

			for ( int j=0; j<MAX_OP_NUM; ++j )
			{
				DestroyWindow( hOp[j] );
			}
			for ( int i=0; i<10; ++i )
			{
				DestroyWindow( hNum[i] );
			}

			DestroyWindow( hBackSpace );
			DestroyWindow( hClearCur );
			DestroyWindow( hClear );
			DestroyWindow( hEdit );

			return DefWindowProc( hWnd, message, wParam, lParam );
		}
		break;

	case WM_COMMAND:
		{
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 

			if( wmId <= IDBTN_BACKSPACE ) 
			{
				// �����˵�ѡ��:
				switch (wmId)
				{
				case IDBTN_CLEAR:
					{
						leftNum = 0.0f;
						rightNum = 0.0f;
						curCalcState = CS_LEFT;
						SetWindowText( hEdit, "0.00" );
					}
					break;

				case IDBTN_CLEARCUR:
					{
						(curCalcState == CS_LEFT) ? 
							(leftNum = 0.0f) : (rightNum = 0.0f);
						SetWindowText( hEdit, "0.00" );
					}
					break;

				case IDBTN_BACKSPACE:
					{
						if( curCalcState == CS_LEFT )
						{
							leftNum /= 10.0f;
							if ( isFloatEqualToZero( leftNum ) )
							{
								leftNum = (int)leftNum;
							}
							//isFloatEqualToZero( leftNum ) ? 0.0f : leftNum/10.0f; 
							sprintf( strBuffer, "%.2f", leftNum );
							SetWindowText( hEdit, strBuffer );
						}
						else
						if( curCalcState == CS_RIGHT )
						{
							rightNum /= 10.0f;//isFloatEqualToZero( rightNum ) ? 0.0f : rightNum/10.0f; 
							if ( isFloatEqualToZero( rightNum ) )
							{
								rightNum = (int)rightNum;
							}
							sprintf( strBuffer, "%.2f", rightNum);
							SetWindowText( hEdit, strBuffer );
						}
					}
					break;

				case IDBTN_SIGN:
					{
						if( curCalcState == CS_RIGHT )
						{
							rightNum = -rightNum;//isFloatEqualToZero( rightNum ) ? 0.0f : rightNum/10.0f; 
							sprintf( strBuffer, "%.2f", rightNum);
							SetWindowText( hEdit, strBuffer );
						}
						else
						{
							leftNum = -leftNum;
							sprintf( strBuffer, "%.2f", leftNum );
							SetWindowText( hEdit, strBuffer );
						}
					}
					break;

				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
			// ���������
			else
			{
				switch( curCalcState )
				{
				case CS_LEFT:
					{
						if ( wmId >= IDBTN_NUM0 && wmId < IDBTN_NUM0+10 )
						{
							leftNum = leftNum*10.0f + (float)(wmId - IDBTN_NUM0);
							sprintf( strBuffer, "%.2f", leftNum );
							SetWindowText( hEdit, strBuffer );
							break;
						}
						else
						{
							if ( wmId != IDBTN_EQUAL )
							{
								curCalcState = CS_OPERATOR;
								getCurOp( wmId, curOP );
							}
							rightNum = 0.0f;
						}
					}
					break;
				
				case CS_OPERATOR:
					{
						if ( wmId >= IDBTN_NUM0 && wmId < IDBTN_NUM0+10 )
						{
							rightNum = rightNum*10.0f + (float)(wmId - IDBTN_NUM0);
							sprintf( strBuffer, "%.2f", rightNum );
							SetWindowText( hEdit, strBuffer );
							curCalcState = CS_RIGHT;
							break;
						}
						else
						{
							if( wmId != IDBTN_EQUAL )
							{
								getCurOp( wmId, curOP );
								rightNum = 0.0f;
							}
							else
							{
								curCalcState = CS_RIGHT;
							}
						}
					}
					break;

				case CS_RIGHT:
					{
						if ( wmId >= IDBTN_NUM0 && wmId < IDBTN_NUM0+10 )
						{
							rightNum = rightNum*10.0f + (float)(wmId - IDBTN_NUM0);
							sprintf( strBuffer, "%.2f", rightNum );
							SetWindowText( hEdit, strBuffer );
							break;
						}
						// �в���������£��Ĳ������͵Ⱥ����붼
						// ��������
						else
						{
							tempOp = curOP;
							// ���������͵Ⱥ�
							getCurOp( wmId, tempOp );
							calcResultByOperator();
							curOP = tempOp;

							// ���ǵȺŵĻ������Ǿͼ�����
							if( wmId != IDBTN_EQUAL )
							{
								rightNum = 0.0f;
								curCalcState = CS_OPERATOR;
							}
						}
					}
					break;
					
				case CS_EQUAL:
					{
						if ( wmId >= IDBTN_NUM0 && wmId < IDBTN_NUM0+10 )
						{
							rightNum = (float)(wmId - IDBTN_NUM0);
							sprintf( strBuffer, "%.2f", rightNum );
							SetWindowText( hEdit, strBuffer );
							curCalcState = CS_RIGHT;
							break;
						}
						else
						if( wmId != IDBTN_EQUAL )
						{
							curCalcState = CS_OPERATOR;
							getCurOp( wmId, curOP );
							rightNum = 0.0f;
						}
						else
						{
							calcResultByOperator();
						}
					}
					break;
				}
			}
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

void calcResultByOperator()
{
	switch( curOP )
	{
	case COP_ADD:
		{
			leftNum += rightNum;
		}
		break;
	case COP_SUB:
		{
			leftNum -= rightNum;
		}
		break;
	case COP_MUL:
		{
			leftNum *= rightNum;
		}
		break;
	case COP_DIV:
		{
			if ( isFloatEqualToZero( rightNum ) )
			{
				SetWindowText( hEdit, "��������Ϊ0" );
				curCalcState = CS_RIGHT;
				return;
			}
			else
			{
				leftNum /= rightNum;
			}
		}
		break;
	}

	sprintf( strBuffer, "%.2f", leftNum );
	SetWindowText( hEdit, strBuffer );
	curCalcState = CS_EQUAL;
}

void getCurOp( short wmId, CALC_OPERATOR &cop )
{
	switch( wmId )
	{
	case IDBTN_OP_ADD:
		{
			cop = COP_ADD;
		}
		break;

	case IDBTN_OP_SUB:
		{
			cop = COP_SUB;
		}
		break;
	case IDBTN_OP_MUL:
		{
			cop = COP_MUL;
		}
		break;
	case IDBTN_OP_DIV:
		{
			cop = COP_DIV;
		}
		break;
	}
}

bool isFloatEqualToZero( float f )
{
	if( (f > -FLOAT_PERCENT) &&
		(f < FLOAT_PERCENT) )
	{
		return true;
	}
	return false;
}
