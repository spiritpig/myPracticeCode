// BNBMapEditorView.cpp : CBNBMapEditorView 类的实现
//

#include "stdafx.h"
#include "BNBMapEditor.h"

#include "BNBMapEditorDoc.h"
#include "BNBMapEditorView.h"
#include ".\bnbmapeditorview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBNBMapEditorView

IMPLEMENT_DYNCREATE(CBNBMapEditorView, CView)

BEGIN_MESSAGE_MAP(CBNBMapEditorView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_COMMAND_RANGE(ID_ADDGRASS1,ID_ADDBOX,OnCommandRange)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_CLEARMAP, OnClearmap)
	ON_COMMAND(ID_DISPLAYGROUND, OnDisplayground)
	ON_COMMAND(ID_DISPLAYOBJECT, OnDisplayobject)
	ON_COMMAND(ID_DISPLAYALL, OnDisplayall)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
END_MESSAGE_MAP()

// CBNBMapEditorView 构造/析构

CBNBMapEditorView::CBNBMapEditorView()
{
	// TODO: 在此处添加构造代码
	m_hBackBufferBmp = NULL;
	m_hBackBufferDc = CreateCompatibleDC( NULL );
	m_pMap = new GameMap( m_hBackBufferDc );
	m_isLeftMouseDown = false;
	m_isRightMouseDown = false;
	m_CurBK = BK_GRASS1;
	m_CurMds = MDS_ALL;
	m_CurFileName = "未命名.mpd";
}

CBNBMapEditorView::~CBNBMapEditorView()
{
	SAFE_DELETE( m_pMap );
	DeleteObject( m_hBackBufferBmp );
	DeleteDC( m_hBackBufferDc );
}

BOOL CBNBMapEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CBNBMapEditorView 绘制

void CBNBMapEditorView::OnDraw(CDC* /*pDC*/)
{
	CBNBMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CBNBMapEditorView 打印

BOOL CBNBMapEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CBNBMapEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CBNBMapEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CBNBMapEditorView 诊断

#ifdef _DEBUG
void CBNBMapEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CBNBMapEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBNBMapEditorDoc* CBNBMapEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBNBMapEditorDoc)));
	return (CBNBMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CBNBMapEditorView 消息处理程序

int CBNBMapEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码	
	return 0;
}

void CBNBMapEditorView::OnTimer(UINT nIDEvent)
{
	static POINT pt;
	if ( m_isLeftMouseDown  )
	{
		GetCursorPos( &pt );
		ScreenToClient( &pt );

		pt.x = (pt.x - 20)/BLOCK_SIZE;
		pt.y = (pt.y - 40)/BLOCK_SIZE;

		if ( m_CurBK < BK_HOUSE1 )
		{
			m_pMap->SetBackMap( pt.y, pt.x, m_CurBK );
		}
		else
		{
			m_pMap->SetMidAndTopMap( pt.y, pt.x, m_CurBK );
		}
	}
	else
	{
		if ( m_isRightMouseDown  )
		{
			GetCursorPos( &pt );
			ScreenToClient( &pt );

			pt.x = (pt.x - 20)/BLOCK_SIZE;
			pt.y = (pt.y - 40)/BLOCK_SIZE;

			m_pMap->ClearMidAndTopMap( pt.y, pt.x );
		}
	}

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pMap->RenderBG();
	switch( m_CurMds )
	{
	case MDS_ALL:
		{
			m_pMap->RenderBack();
			m_pMap->RenderMidAndTop();
		}
		break;

	case MDS_BACK:
		{
			m_pMap->RenderBack();
		}
		break;

	case MDS_TOPANDMID:
		{
			m_pMap->RenderMidAndTop();
		}
		break;
	}

	HDC hdc = ::GetDC( m_hWnd );
	BitBlt( hdc, 0, 0, m_ClientRect.right, m_ClientRect.bottom, 
		m_hBackBufferDc, 0, 0, SRCCOPY );
	::ReleaseDC( m_hWnd, hdc );

	CView::OnTimer(nIDEvent);
}

void CBNBMapEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	SetTimer( 1, 17, NULL );

	GetClientRect( &m_ClientRect );

	HDC hdc = ::GetDC( m_hWnd );
	if( m_hBackBufferBmp )
	{
		DeleteObject( m_hBackBufferBmp );
	}
	m_hBackBufferBmp = CreateCompatibleBitmap( hdc, m_ClientRect.right, 
			m_ClientRect.bottom );
	SelectObject( m_hBackBufferDc, m_hBackBufferBmp );
	::ReleaseDC( m_hWnd, hdc );
}

void CBNBMapEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isLeftMouseDown = true;

	CView::OnLButtonDown(nFlags, point);
}

void CBNBMapEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isLeftMouseDown = false;

	CView::OnLButtonUp(nFlags, point);
}

void CBNBMapEditorView::OnCommandRange( UINT Id )
{
	if ( Id >= ID_ADDGRASS1 && Id <= ID_ADDROAD3 )
	{
		m_CurBK = (BLOCK_KIND)((int)BK_GRASS1 + Id-ID_ADDGRASS1);
	}

	if ( Id >= ID_ADDHOUSE1 && Id <= ID_ADDBOX )
	{
		m_CurBK = (BLOCK_KIND)((int)BK_HOUSE1 + Id-ID_ADDHOUSE1);
	}
}
void CBNBMapEditorView::OnClearmap()
{
	// TODO: 在此添加命令处理程序代码
	m_pMap->ClearMap();
}

void CBNBMapEditorView::OnDisplayground()
{
	// TODO: 在此添加命令处理程序代码
	m_CurMds = MDS_BACK;
}

void CBNBMapEditorView::OnDisplayobject()
{
	// TODO: 在此添加命令处理程序代码
	m_CurMds = MDS_TOPANDMID;
}

void CBNBMapEditorView::OnDisplayall()
{
	// TODO: 在此添加命令处理程序代码
	m_CurMds = MDS_ALL;
}

void CBNBMapEditorView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	static char filter[] = "Map Data Files(*.mpd)|*.mpd||";
	CFileDialog cflg( TRUE, "mpd", "未命名.mpd", OFN_READONLY, filter );

	if ( cflg.DoModal() == IDOK )
	{
		m_CurFileName = cflg.GetPathName();
		m_pMap->LoadMapFromFile( m_CurFileName.GetBuffer() );

		GetParent()->SetWindowText( m_CurFileName.GetBuffer() );
	}
}

void CBNBMapEditorView::OnFileSave()
{
	if( strcmp( m_CurFileName.GetBuffer(), "未命名.mpd" ) == 0 )
	{
		static char filter[] = "Map Data Files(*.mpd)|*.mpd||";
		CFileDialog cflg( FALSE, "mpd", "未命名.mpd", 
			OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter );

		if ( cflg.DoModal() == IDOK )
		{
			m_CurFileName = cflg.GetPathName();
			m_pMap->SaveMapToFile( m_CurFileName.GetBuffer() );

			GetParent()->SetWindowText( m_CurFileName.GetBuffer() );
		}
	}
	else
	{
		m_pMap->SaveMapToFile( m_CurFileName.GetBuffer() );
	}
}

void CBNBMapEditorView::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	static char filter[] = "Map Data Files(*.mpd)|*.mpd||";
	CFileDialog cflg( FALSE, "mpd", m_CurFileName.GetBuffer(), 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter );

	if ( cflg.DoModal() == IDOK )
	{
		m_CurFileName = cflg.GetPathName();
		m_pMap->SaveMapToFile( m_CurFileName.GetBuffer() );

		GetParent()->SetWindowText( m_CurFileName.GetBuffer() );
	}
}

void CBNBMapEditorView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isRightMouseDown = true;

	CView::OnRButtonDown(nFlags, point);
}

void CBNBMapEditorView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_isRightMouseDown = false;

	CView::OnRButtonUp(nFlags, point);
}

void CBNBMapEditorView::OnFileNew()
{
	// TODO: 在此添加命令处理程序代码
	m_pMap->ClearMap();
}
