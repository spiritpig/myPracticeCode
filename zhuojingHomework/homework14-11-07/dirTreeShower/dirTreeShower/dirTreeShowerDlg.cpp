// dirTreeShowerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "dirTreeShower.h"
#include "dirTreeShowerDlg.h"
#include ".\dirtreeshowerdlg.h"

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


// CdirTreeShowerDlg 对话框



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


// CdirTreeShowerDlg 消息处理程序

BOOL CdirTreeShowerDlg::OnInitDialog()
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
	DWORD size = 1024;
	GetUserName( buffer, &size);
	_stprintf( buffer, "%s 的电脑", buffer );
	HTREEITEM hRoot = m_DirTreeCtrl.InsertItem( buffer );
	// 添加磁盘信息
	for( int i='A'; i<'Z'+1; ++i )
	{
		_stprintf( buffer, "%c:\\", i );
		if( GetVolumeInformation( buffer, NULL, 0, NULL, NULL, NULL, NULL, 0 ) )
		{
			m_DirTreeCtrl.InsertItem( buffer, hRoot );
		}
	}
	m_DirTreeCtrl.Expand( hRoot, TVE_EXPAND );
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CdirTreeShowerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
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
	// 已经扩展过得目录，直接返回
	if( m_DirTreeCtrl.GetChildItem( item ) != NULL )
	{
		return;
	}

	CString cStrTemp;
	_GetItemPath( item, cStrTemp );
	// 不是目录则返回
	if( cStrTemp.GetAt( cStrTemp.GetLength()-1 ) != '\\' )
	{
		return;
	}

	cStrTemp += "*.*";
	WIN32_FIND_DATA wfd;
	HANDLE hFindFile = FindFirstFile( cStrTemp, &wfd );

	// 无子目录则返回
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
	// TODO: 在此添加控件通知处理程序代码
	_FillDirTree( m_DirTreeCtrl.GetSelectedItem() );

	*pResult = 0;
}

void CdirTreeShowerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString path;
	_GetItemPath( m_DirTreeCtrl.GetSelectedItem(), path );

	OnOK();
}
