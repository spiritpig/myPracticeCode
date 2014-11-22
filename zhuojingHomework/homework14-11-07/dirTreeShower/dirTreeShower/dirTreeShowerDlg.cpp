// dirTreeShowerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "dirTreeShower.h"
#include "dirTreeShowerDlg.h"
#include ".\dirtreeshowerdlg.h"

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


// CdirTreeShowerDlg �Ի���



CdirTreeShowerDlg::CdirTreeShowerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CdirTreeShowerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CdirTreeShowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_DirTreeCtrl);
}

BEGIN_MESSAGE_MAP(CdirTreeShowerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnNMDblclkTree1)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CdirTreeShowerDlg ��Ϣ�������

BOOL CdirTreeShowerDlg::OnInitDialog()
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
	DWORD size = 1024;
	GetUserName( buffer, &size);
	_stprintf( buffer, "%s �ĵ���", buffer );
	HTREEITEM hRoot = m_DirTreeCtrl.InsertItem( buffer );
	// ��Ӵ�����Ϣ
	for( int i='A'; i<'Z'+1; ++i )
	{
		_stprintf( buffer, "%c:\\", i );
		if( GetVolumeInformation( buffer, NULL, 0, NULL, NULL, NULL, NULL, 0 ) )
		{
			m_DirTreeCtrl.InsertItem( buffer, hRoot );
		}
	}
	m_DirTreeCtrl.Expand( hRoot, TVE_EXPAND );
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CdirTreeShowerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CdirTreeShowerDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CdirTreeShowerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CdirTreeShowerDlg::_GetItemPath( HTREEITEM item, CString &retStr )
{
	if( item == NULL )
	{
		return;
	}

	retStr.Empty();
	while ( m_DirTreeCtrl.GetParentItem( item ) != NULL )
	{
		retStr = m_DirTreeCtrl.GetItemText( item ) + retStr;
		item = m_DirTreeCtrl.GetParentItem( item );
	}
}

void CdirTreeShowerDlg::_FillDirTree( HTREEITEM item )
{
	// �Ѿ���չ����Ŀ¼��ֱ�ӷ���
	if( m_DirTreeCtrl.GetChildItem( item ) != NULL )
	{
		return;
	}

	CString cStrTemp;
	_GetItemPath( item, cStrTemp );
	// ����Ŀ¼�򷵻�
	if( cStrTemp.GetAt( cStrTemp.GetLength()-1 ) != '\\' )
	{
		return;
	}

	cStrTemp += "*.*";
	WIN32_FIND_DATA wfd;
	HANDLE hFindFile = FindFirstFile( cStrTemp, &wfd );

	// ����Ŀ¼�򷵻�
	if( hFindFile == INVALID_HANDLE_VALUE )
	{
		return;
	}

	do 
	{
		if( _tcscmp( wfd.cFileName, _T( "." ) ) == 0 ||
			_tcscmp( wfd.cFileName, _T( ".." ) ) == 0 )
		{
			continue;
		}

		cStrTemp = wfd.cFileName;
		if ( wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
		{
			cStrTemp += '\\'; 
		}
		m_DirTreeCtrl.InsertItem( cStrTemp, item );

	} while ( FindNextFile( hFindFile, &wfd ) );

	FindClose( hFindFile );
}

void CdirTreeShowerDlg::OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	_FillDirTree( m_DirTreeCtrl.GetSelectedItem() );

	*pResult = 0;
}

void CdirTreeShowerDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString path;
	_GetItemPath( m_DirTreeCtrl.GetSelectedItem(), path );

	OnOK();
}
