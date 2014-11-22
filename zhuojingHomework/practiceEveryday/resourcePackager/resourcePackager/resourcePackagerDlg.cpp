// resourcePackagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "resourcePackager.h"
#include "resourcePackagerDlg.h"
#include ".\resourcepackagerdlg.h"

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


// CresourcePackagerDlg �Ի���



CresourcePackagerDlg::CresourcePackagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CresourcePackagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CresourcePackagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_FileList);
}

BEGIN_MESSAGE_MAP(CresourcePackagerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPENFILE, OnBnClickedOpenfile)
	ON_BN_CLICKED(IDC_CLEARLIST, OnBnClickedClearlist)
	ON_BN_CLICKED(IDC_PACK, OnBnClickedPack)
END_MESSAGE_MAP()


// CresourcePackagerDlg ��Ϣ�������

BOOL CresourcePackagerDlg::OnInitDialog()
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
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CresourcePackagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CresourcePackagerDlg::OnPaint() 
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
HCURSOR CresourcePackagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CresourcePackagerDlg::OnBnClickedOpenfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char filter[] = "All Files(*.*)|*.*||";
	CFileDialog cflg( TRUE, NULL, NULL, OFN_READONLY | OFN_ALLOWMULTISELECT, filter );

	static char buffer[655350];
	cflg.m_ofn.lpstrFile = buffer;
	cflg.m_ofn.nMaxFile = 655350;

	if ( cflg.DoModal() == IDOK )
	{
		int maxLen = 0, tempLen;
		CDC *pDc = GetDC();

		CString curPath;
		POSITION pos = cflg.GetStartPosition();
		while ( pos != NULL )
		{
			curPath = cflg.GetNextPathName( pos );
			m_FileList.AddString( curPath.GetBuffer() );

			tempLen = (pDc->GetTextExtent( curPath )).cx;
			if ( maxLen < tempLen )
			{
				maxLen = tempLen;
			}
		}
		m_FileList.SetHorizontalExtent( maxLen );

		ReleaseDC(pDc);
	}
}

void CresourcePackagerDlg::OnBnClickedClearlist()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_FileList.ResetContent();
}

char* CresourcePackagerDlg::GetFilename( char *path )
{
	int index = (int)strlen( path )-1;
	while ( index > -1 && path[index] != '//' )
	{
		--index;
	}

	return (path + index + 1);
}

void CresourcePackagerDlg::OnBnClickedPack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
