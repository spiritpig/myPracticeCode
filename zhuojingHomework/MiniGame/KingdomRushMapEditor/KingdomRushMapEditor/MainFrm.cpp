// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "KingdomRushMapEditor.h"

#include "MainFrm.h"
#include ".\mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	// TODO: 如果不需要工具栏可停靠，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式
	cs.style &= ~( WS_THICKFRAME | WS_MAXIMIZEBOX );

	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame 消息处理程序


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	int screenWidth = GetSystemMetrics( SM_CXSCREEN );
	int screenHeight = GetSystemMetrics( SM_CYSCREEN );

	RECT clientRect, tempBarRect;

	LONG toolBarHeight = 0,statusBarHeight = 0;
	if ( m_wndToolBar.m_hWnd )
	{
		m_wndToolBar.GetClientRect( &tempBarRect );
		toolBarHeight = tempBarRect.bottom-tempBarRect.top;
		m_wndStatusBar.GetClientRect( &tempBarRect );
		statusBarHeight = tempBarRect.bottom-tempBarRect.top;

		clientRect.left = (screenWidth-700)/2;
		clientRect.right = (screenWidth-700)/2 + 700;
		clientRect.top = (screenHeight-600-toolBarHeight-statusBarHeight)/2;
		clientRect.bottom = (screenHeight-600-toolBarHeight-statusBarHeight)/2 
			+ 600 + toolBarHeight + statusBarHeight;

		AdjustWindowRect( &clientRect, GetStyle(),
			::GetMenu( this->m_hWnd ) !=  NULL );

		MoveWindow( &clientRect );
	}
}
