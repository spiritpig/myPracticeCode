// NotepadEMDoc.cpp :  CNotepadEMDoc 类的实现
//

#include "stdafx.h"
#include "NotepadEM.h"

#include "NotepadEMDoc.h"
#include ".\notepademdoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNotepadEMDoc

IMPLEMENT_DYNCREATE(CNotepadEMDoc, CDocument)

BEGIN_MESSAGE_MAP(CNotepadEMDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
END_MESSAGE_MAP()


// CNotepadEMDoc 构造/析构

CNotepadEMDoc::CNotepadEMDoc()
{
	// TODO: 在此添加一次性构造代码

}

CNotepadEMDoc::~CNotepadEMDoc()
{
}

BOOL CNotepadEMDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CNotepadEMDoc 序列化

void CNotepadEMDoc::Serialize(CArchive& ar)
{
	POSITION pos = GetFirstViewPosition();
	CEditView *pEditView = (CEditView *)GetNextView( pos );
	CString buffer;

	if( pEditView != NULL )
	{
		if (ar.IsStoring())
		{
			pEditView->GetWindowText( buffer );
			if( _tcscmp( _getFileExtension( ar.GetFile()->GetFileName().GetBuffer() ), _T("txt") ) )
			{
				ar.Write( buffer.GetBuffer(), buffer.GetLength()+1 );
			}
		}
		else
		{
			CFile *pFile = ar.GetFile();
			if( _tcscmp( _getFileExtension( pFile->GetFileName().GetBuffer() ), _T("txt") ) )
			{
				pFile->Read( buffer.GetBuffer( (UINT)pFile->GetLength()+1 ), 
												(UINT)pFile->GetLength() );
				// 添加\0防止文件结尾产生奇怪的字符
				(buffer.GetBuffer())[pFile->GetLength()] = _T('\0');
				pEditView->SetWindowText( buffer );
			}
		}
	}
}


// CNotepadEMDoc 诊断

#ifdef _DEBUG
void CNotepadEMDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNotepadEMDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}

TCHAR* CNotepadEMDoc::_getFileExtension( TCHAR *filename )
{
	size_t index = _tcslen( filename )-1;
	while ( index > -1 && filename[index] != _T('.') )
	{
		--index;
	}

	return (&filename[index+1]);
}

#endif //_DEBUG


// CNotepadEMDoc 命令

void CNotepadEMDoc::OnFileOpen()
{
	static TCHAR BASED_CODE szFilter[] = _T("Text Files (*.txt)|*.txt|Bitmap (*.bmp)|*.bmp|")
										_T("All Files (*.*)|*.*||");
	// TODO: 在此添加命令处理程序代码
	CFileDialog cflg( TRUE, NULL, NULL, OFN_HIDEREADONLY, 
		szFilter );
	if( cflg.DoModal() == IDOK )
	{
		OnOpenDocument( cflg.GetFileName().GetBuffer() );
		SetTitle( cflg.GetFileName() );
	}
}

void CNotepadEMDoc::OnFileSave()
{
	if ( !IsModified() )
	{
		return;
	}

	if ( m_strPathName.IsEmpty() )
	{
		static TCHAR BASED_CODE szFilter[] = _T("Text Files (*.txt)|*.txt|Bitmap (*.bmp)|*.bmp|")
											_T("All Files (*.*)|*.*||");

		CFileDialog cflg( FALSE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
			szFilter );

		if( cflg.DoModal() == IDOK )
		{
			if( OnSaveDocument( cflg.GetFileName().GetBuffer() ) )
			{
				m_strPathName = cflg.GetPathName();
				SetTitle( m_strPathName );
			}
		}
	}
	else
	{
		OnSaveDocument( m_strPathName.GetBuffer() );
	}
}

void CNotepadEMDoc::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	static TCHAR BASED_CODE szFilter[] = _T("Text Files (*.txt)|*.txt|Bitmap (*.bmp)|*.bmp|"
		_T("All Files (*.*)|*.*||"));

	CFileDialog cflg( FALSE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, 
		szFilter );

	if( cflg.DoModal() == IDOK )
	{
		if( OnSaveDocument( cflg.GetFileName().GetBuffer() ) )
		{
			m_strPathName = cflg.GetPathName();
			SetTitle( m_strPathName );
		}
	}
}
