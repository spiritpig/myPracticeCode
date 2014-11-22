// mfcPictureViewerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcPictureViewer.h"
#include "mfcPictureViewerDlg.h"
#include ".\mfcpictureviewerdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CmfcPictureViewerDlg 对话框



CmfcPictureViewerDlg::CmfcPictureViewerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmfcPictureViewerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CmfcPictureViewerDlg::~CmfcPictureViewerDlg()
{
	if ( m_Bitmap != NULL )
	{
		DeleteObject( m_Bitmap );
	}
	m_BitmapDc.DeleteDC();

	if( m_BackBitmap != NULL )
	{
		DeleteObject( m_BackBitmap );
	}
	m_BackDc.DeleteDC();
}

void CmfcPictureViewerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcPictureViewerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CmfcPictureViewerDlg 消息处理程序

BOOL CmfcPictureViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	DragAcceptFiles();
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CmfcPictureViewerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmfcPictureViewerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文


		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		m_BackDc.FillRect( &m_ClientRect, &CBrush( RGB( 128, 255, 128 ) ) );
		if( m_Bitmap != NULL )
		{
			m_BackDc.BitBlt( 0, 0, m_BitmapInfo.bmWidth, m_BitmapInfo.bmHeight, 
				&m_BitmapDc, m_HScrollInfo.nPos, m_VScrollInfo.nPos, SRCCOPY );
		}
		// 翻屏
		CPaintDC cpc( this );
		cpc.BitBlt( 0, 0, m_ClientRect.right, m_ClientRect.bottom, 
			&m_BackDc, 0, 0, SRCCOPY );

		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CmfcPictureViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CmfcPictureViewerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	ZeroMemory( &m_HScrollInfo, sizeof(m_HScrollInfo) );
	m_HScrollInfo.cbSize = sizeof( m_HScrollInfo );
	m_HScrollInfo.fMask = SIF_ALL;

	ZeroMemory( &m_VScrollInfo, sizeof(m_VScrollInfo) );
	m_VScrollInfo.cbSize = sizeof( m_VScrollInfo );
	m_VScrollInfo.fMask = SIF_ALL;

	GetClientRect( &m_ClientRect );
	// 背景缓冲
	CDC *cdc = GetDC();
	m_BackDc.CreateCompatibleDC( NULL );
	m_BackBitmap = CreateCompatibleBitmap( cdc->m_hDC, 
		m_ClientRect.right, m_ClientRect.bottom );
	m_BackDc.SelectObject( m_BackBitmap );
	ReleaseDC( cdc );
	
	m_Bitmap = NULL;
	m_BitmapDc.CreateCompatibleDC( NULL );

	if( _tcslen( theApp.m_lpCmdLine ) > 0 )
	{
		int argc = -1;
		LPWSTR *argv;
		// 读取命令行参数
		if( sizeof( TCHAR ) == sizeof( CHAR ) )
		{
			MultiByteToWideChar( CP_ACP, NULL, (LPCSTR)theApp.m_lpCmdLine, -1, m_pName, 1024 );
			argv = CommandLineToArgvW( m_pName, &argc );
		}
		else
		{
			argv = CommandLineToArgvW( (LPWSTR)theApp.m_lpCmdLine, &argc );
		}

		_processInputBitmap( argv[0] );
	}

	return 0;
}

void CmfcPictureViewerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	switch( nSBCode )
	{
	case SB_LEFT:
		{
			m_HScrollInfo.nPos = m_HScrollInfo.nMin;
			SetScrollPos( SB_HORZ, m_HScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;
	case SB_RIGHT:
		{
			m_HScrollInfo.nPos = m_HScrollInfo.nMax;
			SetScrollPos( SB_HORZ, m_HScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;

	case SB_LINELEFT:
		{
			m_HScrollInfo.nPos = max( m_HScrollInfo.nPos-1, 0 );
			SetScrollPos( SB_HORZ, m_HScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;
	case SB_LINERIGHT:
		{
			m_HScrollInfo.nPos = min( m_HScrollInfo.nPos+1, m_HScrollInfo.nMax );
			SetScrollPos( SB_HORZ, m_HScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;

	case SB_PAGELEFT:
		{
			m_HScrollInfo.nPos = max( m_HScrollInfo.nPos-SCROLLBAR_PAGE_STEP, 0 );
			SetScrollPos( SB_HORZ, m_HScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;
	case SB_PAGERIGHT:
		{
			m_HScrollInfo.nPos = min( m_HScrollInfo.nPos+SCROLLBAR_PAGE_STEP,
				m_HScrollInfo.nMax );
			SetScrollPos( SB_HORZ, m_HScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;

	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
			m_HScrollInfo.nPos = nPos;
			SetScrollPos( SB_HORZ, nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CmfcPictureViewerDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	switch( nSBCode )
	{
	case SB_LEFT:
		{
			m_VScrollInfo.nPos = m_VScrollInfo.nMin;
			SetScrollPos( SB_VERT, m_VScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;
	case SB_RIGHT:
		{
			m_VScrollInfo.nPos = m_VScrollInfo.nMax;
			SetScrollPos( SB_VERT, m_VScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;

	case SB_LINELEFT:
		{
			m_VScrollInfo.nPos = max( m_VScrollInfo.nPos-1, 0 );
			SetScrollPos( SB_VERT, m_VScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;
	case SB_LINERIGHT:
		{
			m_VScrollInfo.nPos = min( m_VScrollInfo.nPos+1, m_VScrollInfo.nMax );
			SetScrollPos( SB_VERT, m_VScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;

	case SB_PAGELEFT:
		{
			m_VScrollInfo.nPos = max( m_VScrollInfo.nPos-SCROLLBAR_PAGE_STEP, 0 );
			SetScrollPos( SB_VERT, m_VScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;
	case SB_PAGERIGHT:
		{
			m_VScrollInfo.nPos = min( m_VScrollInfo.nPos+SCROLLBAR_PAGE_STEP, 
				m_VScrollInfo.nMax );
			SetScrollPos( SB_VERT, m_VScrollInfo.nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;

	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		{
			m_VScrollInfo.nPos = nPos;
			SetScrollPos( SB_VERT, nPos );
			InvalidateRect( &m_ClientRect );
		}
		break;
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CmfcPictureViewerDlg::_processInputBitmap( LPWSTR filename )
{
	// 删除存在的位图
	if( m_Bitmap != NULL )
	{
		DeleteObject(  m_Bitmap );
	}

	// 读取位图文件
	m_Bitmap = (HBITMAP)::LoadImageW( theApp.m_hInstance, filename, 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	if( m_Bitmap != NULL )
	{
		SelectObject( m_BitmapDc, m_Bitmap );
		GetObject( m_Bitmap, sizeof(BITMAP), &m_BitmapInfo );

		m_HScrollInfo.nPos = 0;
		m_HScrollInfo.nMin = 0;
		m_HScrollInfo.nMax = m_BitmapInfo.bmWidth-m_ClientRect.right;
		m_HScrollInfo.nPage = (m_HScrollInfo.nMax-m_HScrollInfo.nMin)/SCROLLBAR_PAGE_STEP;
		SetScrollInfo( SB_HORZ, &m_HScrollInfo );

		m_VScrollInfo.nPos = 0;
		m_VScrollInfo.nMin = 0;
		m_VScrollInfo.nMax = m_BitmapInfo.bmHeight-m_ClientRect.bottom;
		m_VScrollInfo.nPage = (m_VScrollInfo.nMax-m_VScrollInfo.nMin)/SCROLLBAR_PAGE_STEP;
		SetScrollInfo( SB_VERT, &m_VScrollInfo );
	}

	InvalidateRect( &m_ClientRect );
}


void CmfcPictureViewerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	GetClientRect( &m_ClientRect );
	DeleteObject( m_BackBitmap );

	CDC *cdc = GetDC();
	m_BackBitmap = CreateCompatibleBitmap( cdc->m_hDC, 
		m_ClientRect.right, m_ClientRect.bottom );
	m_BackDc.SelectObject( m_BackBitmap );
	ReleaseDC( cdc );

	m_HScrollInfo.nPos = 0;
	m_HScrollInfo.nMin = 0;
	m_HScrollInfo.nMax = m_BitmapInfo.bmWidth-m_ClientRect.right;
	m_HScrollInfo.nPage = (m_HScrollInfo.nMax-m_HScrollInfo.nMin)/SCROLLBAR_PAGE_STEP;
	SetScrollInfo( SB_HORZ, &m_HScrollInfo );

	m_VScrollInfo.nPos = 0;
	m_VScrollInfo.nMin = 0;
	m_VScrollInfo.nMax = m_BitmapInfo.bmHeight-m_ClientRect.bottom;
	m_VScrollInfo.nPage = (m_VScrollInfo.nMax-m_VScrollInfo.nMin)/SCROLLBAR_PAGE_STEP;
	SetScrollInfo( SB_VERT, &m_VScrollInfo );

	InvalidateRect( &m_ClientRect );
}
BOOL CmfcPictureViewerDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CmfcPictureViewerDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DragQueryFileW( hDropInfo, 0, m_pName, 1024 );
	_processInputBitmap( m_pName );

	CDialog::OnDropFiles(hDropInfo);
}
