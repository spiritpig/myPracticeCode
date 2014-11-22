// MyEditView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NotepadEM.h"
#include "NotepadEMDoc.h"
#include "MyEditView.h"
#include ".\myeditview.h"


// CMyEditView

IMPLEMENT_DYNCREATE(CMyEditView, CEditView)

CMyEditView::CMyEditView()
{
}

CMyEditView::~CMyEditView()
{
}

BEGIN_MESSAGE_MAP(CMyEditView, CEditView)
	ON_WM_CREATE()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMyEditView ���

#ifdef _DEBUG
void CMyEditView::AssertValid() const
{
	CEditView::AssertValid();
}

void CMyEditView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG


// CMyEditView ��Ϣ�������

int CMyEditView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	DragAcceptFiles( TRUE );

	return 0;
}

void CMyEditView::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if( ((CNotepadEMDoc *)GetDocument())->IsModified() )
	{
		((CNotepadEMDoc *)GetDocument())->OnFileSaveAs();
	}

	TCHAR dropFileBuffer[1024];
	DragQueryFile( hDropInfo, 0, dropFileBuffer, 1024 );
	if ( _tcscmp( _getFileExtension( dropFileBuffer ), _T("txt") ) )
	{
		// ��ȡ������ļ�����
		((CNotepadEMDoc *)GetDocument())->SetTitle( dropFileBuffer );
		((CNotepadEMDoc *)GetDocument())->OnOpenDocument( dropFileBuffer );
	}

	CEditView::OnDropFiles(hDropInfo);
}

TCHAR* CMyEditView::_getFileExtension( TCHAR *filename )
{
	size_t index = _tcslen( filename )-1;
	while ( index > -1 && filename[index] != '.' )
	{
		--index;
	}

	return (&filename[index+1]);
}