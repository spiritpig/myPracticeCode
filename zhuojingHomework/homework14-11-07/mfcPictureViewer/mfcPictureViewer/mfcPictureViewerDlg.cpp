// mfcPictureViewerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcPictureViewer.h"
#include "mfcPictureViewerDlg.h"
#include ".\mfcpictureviewerdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CmfcPictureViewerDlg �Ի���



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


// CmfcPictureViewerDlg ��Ϣ�������

BOOL CmfcPictureViewerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	DragAcceptFiles();
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmfcPictureViewerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������


		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
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
		// ����
		CPaintDC cpc( this );
		cpc.BitBlt( 0, 0, m_ClientRect.right, m_ClientRect.bottom, 
			&m_BackDc, 0, 0, SRCCOPY );

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CmfcPictureViewerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CmfcPictureViewerDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ZeroMemory( &m_HScrollInfo, sizeof(m_HScrollInfo) );
	m_HScrollInfo.cbSize = sizeof( m_HScrollInfo );
	m_HScrollInfo.fMask = SIF_ALL;

	ZeroMemory( &m_VScrollInfo, sizeof(m_VScrollInfo) );
	m_VScrollInfo.cbSize = sizeof( m_VScrollInfo );
	m_VScrollInfo.fMask = SIF_ALL;

	GetClientRect( &m_ClientRect );
	// ��������
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
		// ��ȡ�����в���
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
	// ɾ�����ڵ�λͼ
	if( m_Bitmap != NULL )
	{
		DeleteObject(  m_Bitmap );
	}

	// ��ȡλͼ�ļ�
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
	// TODO: �ڴ˴������Ϣ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DragQueryFileW( hDropInfo, 0, m_pName, 1024 );
	_processInputBitmap( m_pName );

	CDialog::OnDropFiles(hDropInfo);
}
