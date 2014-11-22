// KingdomRushMapEditorView.cpp : CKingdomRushMapEditorView ���ʵ��
//

#include "stdafx.h"
#include "KingdomRushMapEditor.h"

#include "KingdomRushMapEditorDoc.h"
#include "KingdomRushMapEditorView.h"
#include ".\kingdomrushmapeditorview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKingdomRushMapEditorView

IMPLEMENT_DYNCREATE(CKingdomRushMapEditorView, CView)

BEGIN_MESSAGE_MAP(CKingdomRushMapEditorView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_CLEARMAP, OnClearmap)
	ON_WM_DROPFILES()
	ON_COMMAND(ID_SETSTART, OnSetstart)
	ON_COMMAND(ID_SETEND, OnSetend)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
END_MESSAGE_MAP()

// CKingdomRushMapEditorView ����/����

CKingdomRushMapEditorView::CKingdomRushMapEditorView()
{
	// TODO: �ڴ˴���ӹ������
	m_pCDc = NULL;
	m_hBackBufferDc = CreateCompatibleDC( NULL );
	m_pMap = new KingdomRushMap;
	m_pMap->Init( m_hBackBufferDc, this->m_hWnd );
	m_isDown = false;
	m_isSetStart = false;
	m_isSetEnd = false;

	strcpy( m_curFileName, "δ����.mpd" );
}

CKingdomRushMapEditorView::~CKingdomRushMapEditorView()
{
	SAFE_DELETE( m_pMap );
	DeleteDC( m_hBackBufferDc );
}

BOOL CKingdomRushMapEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CKingdomRushMapEditorView ����

void CKingdomRushMapEditorView::OnDraw(CDC* /*pDC*/)
{
	CKingdomRushMapEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}


// CKingdomRushMapEditorView ��ӡ

BOOL CKingdomRushMapEditorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CKingdomRushMapEditorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CKingdomRushMapEditorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CKingdomRushMapEditorView ���

#ifdef _DEBUG
void CKingdomRushMapEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CKingdomRushMapEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKingdomRushMapEditorDoc* CKingdomRushMapEditorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKingdomRushMapEditorDoc)));
	return (CKingdomRushMapEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CKingdomRushMapEditorView ��Ϣ�������

void CKingdomRushMapEditorView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	if ( m_hBackBufferBmp != NULL )
	{
		DeleteObject( m_hBackBufferBmp );
	}
	
	// �����µĺ�̨������λͼ
	m_pCDc = GetDC();
	GetClientRect( &m_ClientRect );
	m_hBackBufferBmp = CreateCompatibleBitmap( m_pCDc->m_hDC, 
		m_ClientRect.right, m_ClientRect.bottom );
	SelectObject( m_hBackBufferDc, m_hBackBufferBmp );
	ReleaseDC( m_pCDc );
}

void CKingdomRushMapEditorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	POINT cursorPos;
	GetCursorPos( &cursorPos );
	ScreenToClient( &cursorPos );
	Vector2D pos( (float)(cursorPos.x), (float)(cursorPos.y) );
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isDown = true;
	if ( m_isSetStart &&
		pos.x >= 0 && pos.x <= 700 &&
		pos.y >= 0 && pos.y <= 590 )
	{
		m_pMap->SetStartPoint( pos );
		m_isSetStart = false;
		m_isDown = false;
	}
	else
	{
		if( m_isSetEnd &&
			pos.x >= 0 && pos.x <= 700 &&
			pos.y >= 0 && pos.y <= 590 )
		{
			m_pMap->SetEndPoint( pos );
			m_isSetEnd = false;
			m_isDown = false;
		}
	}
}

int CKingdomRushMapEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	SetTimer( 0, 17, NULL );

	//DragAcceptFiles( TRUE );

	return 0;
}

void CKingdomRushMapEditorView::OnTimer(UINT nIDEvent)
{	
	POINT pos;
	GetCursorPos( &pos );
	ScreenToClient( &pos );
	// ·�������
	if( m_isDown )
	{
		SetPath( pos );
	}

	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_pMap->Render();
	m_pCDc = GetDC();
	BitBlt( m_pCDc->m_hDC, 0, 0, m_ClientRect.right, m_ClientRect.bottom,
		m_hBackBufferDc, 0, 0, SRCCOPY );
	ReleaseDC( m_pCDc );

	CView::OnTimer(nIDEvent);
}

void CKingdomRushMapEditorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_isDown = false;
}

void CKingdomRushMapEditorView::OnClearmap()
{
	// TODO: �ڴ���������������
	m_pMap->ClearPath();
}

void CKingdomRushMapEditorView::OnDropFiles(HDROP hDropInfo)
{
	char buffer[1024];
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DragQueryFile( hDropInfo, 0, buffer, 1024 );
	m_pMap->SetBackgroundImage( buffer );
	MessageBox( buffer );

	CView::OnDropFiles(hDropInfo);
}

void CKingdomRushMapEditorView::OnSetstart()
{
	// TODO: �ڴ���������������
	m_isSetStart = true;
}

void CKingdomRushMapEditorView::OnSetend()
{
	// TODO: �ڴ���������������
	m_isSetEnd = true;
}

void CKingdomRushMapEditorView::SetPath( const POINT &cursorPos )
{
	Vector2D pos( (float)cursorPos.x, (float)cursorPos.y );
	if ( pos.x < 0 || pos.x > 700 ||
		pos.y < 0 || pos.y > 590 )
	{
		m_isDown = false;
	}
	else
	{
		if( m_pMap->CanSetPath() )
		{
			m_pMap->AddPath( pos );
		}
		else
		{
			//MessageBox( "�������������յ�", "��ʾ", NULL ); 
			m_isDown = false;
		}
	}
}

void CKingdomRushMapEditorView::OnFileOpen()
{
	static char BASED_CODE szFilter[] = "Map Files (*.mpd)|*.mpd|All Files (*.*)|*.*||";
	// TODO: �ڴ���������������
	CFileDialog cflg( TRUE, ".mpd", m_curFileName, OFN_READONLY, szFilter);

	if ( cflg.DoModal() == IDOK )
	{
		if( !m_pMap->OPenMapFromFile( cflg.GetPathName().GetBuffer() ) )
		{
			MessageBox("���ļ�ʧ��,��ȷ���ļ������Ժ��!","��ʾ",MB_OK|MB_ICONINFORMATION);
		}
		else
		{
			strcpy( m_curFileName, cflg.GetPathName().GetBuffer() );
			GetParent()->SetWindowText( m_curFileName );
		}
	}
}

void CKingdomRushMapEditorView::OnFileSave()
{
	if( strcmp( m_curFileName, "δ����.mpd" ) == 0 )
	{
		static char BASED_CODE szFilter[] = "Map Files (*.mpd)|*.mpd|All Files (*.*)|*.*||";
		// TODO: �ڴ���������������
		CFileDialog cflg( TRUE, ".mpd", m_curFileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);

		if ( cflg.DoModal() == IDOK )
		{
			if( !m_pMap->SaveMapToFile( cflg.GetPathName().GetBuffer() ) )
			{
				MessageBox("���ļ�ʧ��,��ȷ���ļ������Ժ��!","��ʾ",MB_OK|MB_ICONINFORMATION);
			}
			else
			{
				strcpy( m_curFileName, cflg.GetPathName().GetBuffer() );
				GetParent()->SetWindowText( m_curFileName );
			}
		}
	}
	else
	{
		if( !m_pMap->SaveMapToFile( m_curFileName ) )
		{
			MessageBox("���ļ�ʧ��,��ȷ���ļ������Ժ��!","��ʾ",MB_OK|MB_ICONINFORMATION);
		}
	}
}

void CKingdomRushMapEditorView::OnFileSaveAs()
{
	static char BASED_CODE szFilter[] = "Map Files (*.mpd)|*.mpd|All Files (*.*)|*.*||";
	// TODO: �ڴ���������������
	CFileDialog cflg( TRUE, ".mpd", m_curFileName, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter);

	if ( cflg.DoModal() == IDOK )
	{
		if( !m_pMap->SaveMapToFile( cflg.GetPathName().GetBuffer() ) )
		{
			MessageBox("���ļ�ʧ��,��ȷ���ļ������Ժ��!","��ʾ",MB_OK|MB_ICONINFORMATION);
		}
		else
		{
			strcpy( m_curFileName, cflg.GetPathName().GetBuffer() );
			GetParent()->SetWindowText( m_curFileName );
		}
	}
}

void CKingdomRushMapEditorView::OnFileNew()
{
	m_pMap->ClearPath();
	strcpy( m_curFileName, "δ����.mpd" );
	GetParent()->SetWindowText( m_curFileName );
}
