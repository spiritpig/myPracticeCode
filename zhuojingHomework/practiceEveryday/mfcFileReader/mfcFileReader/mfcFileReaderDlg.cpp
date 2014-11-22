// mfcFileReaderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "mfcFileReader.h"
#include "mfcFileReaderDlg.h"
#include ".\mfcfilereaderdlg.h"

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


// CmfcFileReaderDlg �Ի���



CmfcFileReaderDlg::CmfcFileReaderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CmfcFileReaderDlg::IDD, pParent)
{
	ZeroMemory( &m_TextFontLog, sizeof( LOGFONT ) );
	m_TextFontLog.lfHeight = 15;
	strcpy( m_TextFontLog.lfFaceName, "����");
	m_TextBuffer = NULL;
	m_TextColor = RGB( 0, 0, 0 );
	m_BgColor = RGB( 128, 255, 128 );  

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_myColorDlg = new CMyColorDlg( this );
}

void CmfcFileReaderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfcFileReaderDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPENFIEL, OnBnClickedOpenfile)
	ON_BN_CLICKED(IDC_FONTSET, OnBnClickedFontset)
	ON_BN_CLICKED(IDC_FONTCOLOR, OnBnClickedFontcolor)
	ON_BN_CLICKED(IDC_BGCOLOR, OnBnClickedBgcolor)
	ON_BN_CLICKED(IDC_FIGHT, OnBnClickedFight)
END_MESSAGE_MAP()


// CmfcFileReaderDlg ��Ϣ�������

BOOL CmfcFileReaderDlg::OnInitDialog()
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

	m_myColorDlg->Create( IDD_DIALOG1, this );

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CmfcFileReaderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CmfcFileReaderDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CFont font;
		font.CreateFontIndirect( &m_TextFontLog );

		CPaintDC cpdc( this);
		cpdc.SetTextColor( m_TextColor );
		cpdc.SelectObject( font );

		GetClientRect( &m_ClientRect );
		cpdc.FillRect( &m_ClientRect, &CBrush( m_BgColor ) );
		
		m_ClientRect.top = 40;
		cpdc.SetBkMode( TRANSPARENT );
		cpdc.DrawText( m_TextBuffer, &m_ClientRect, DT_LEFT|DT_TOP );

		CDialog::OnPaint();

		font.DeleteObject();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CmfcFileReaderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmfcFileReaderDlg::OnBnClickedOpenfile()
{
	CFileDialog cfg( TRUE, NULL, NULL, OFN_READONLY|OFN_FILEMUSTEXIST, 
		"�ı��ļ�(*.txt)|*.txt|�����ļ�(*.*)|*.*||", NULL, NULL );

	if( cfg.DoModal() == IDOK )
	{
		FILE *fp = fopen( cfg.GetPathName(), "r" );
		fseek( fp, 0, SEEK_END );

		static int len;
		len = ftell( fp );
		rewind(fp);


		if( m_TextBuffer != NULL )
		{
			delete [] m_TextBuffer;
		}
		m_TextBuffer = new char[len+1];
		fread( m_TextBuffer, sizeof( char ), len, fp );
		fclose( fp );

		GetClientRect( &m_ClientRect );
		m_ClientRect.top += 35;
		InvalidateRect( &m_ClientRect );
	}
}

CmfcFileReaderDlg::~CmfcFileReaderDlg()
{
	if( m_TextBuffer != NULL ) 
	{
		delete [] m_TextBuffer;
	}
	if ( m_myColorDlg != NULL )
	{
		delete m_myColorDlg;
	}
}

void CmfcFileReaderDlg::OnBnClickedFontset()
{
	CFontDialog cfong( &m_TextFontLog );

	if( cfong.DoModal() == IDOK )
	{
		cfong.GetCurrentFont( &m_TextFontLog );
		m_TextColor = cfong.GetColor();

		GetClientRect( &m_ClientRect );
		m_ClientRect.top += 35;
		InvalidateRect( &m_ClientRect );
	}
}

void CmfcFileReaderDlg::OnBnClickedFontcolor()
{
	m_myColorDlg->ShowWindow( SW_SHOWNORMAL );
	m_myColorDlg->UpdateWindow();

// 	CColorDialog ccd;
// 	if( ccd.DoModal() == IDOK )
// 	{
// 		m_TextColor = ccd.GetColor();
// 		GetClientRect( &m_ClientRect );
// 		m_ClientRect.top += 35;
// 		InvalidateRect( &m_ClientRect );
// 	}
}

void CmfcFileReaderDlg::OnBnClickedBgcolor()
{
	CColorDialog ccd;
	if( ccd.DoModal() == IDOK )
	{
		m_BgColor = ccd.GetColor();

		GetClientRect( &m_ClientRect );
		InvalidateRect( &m_ClientRect );
	}
}

void CmfcFileReaderDlg::OnBnClickedFight()
{
	SendMessage( WM_CLOSE );
}

LRESULT CmfcFileReaderDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch ( message )
	{
	case WM_TEXTCOLORCHANGE:
		{
			m_TextColor = m_myColorDlg->getCurrentColor();
			GetClientRect( &m_ClientRect );
			m_ClientRect.top += 35;
			InvalidateRect( &m_ClientRect );
		}
		break;
	}

	return CDialog::WindowProc(message, wParam, lParam);
}
