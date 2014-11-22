// FileAttribView.cpp : 实现文件
//

#include "stdafx.h"
#include "FileAttribShower.h"
#include "FileAttribView.h"
#include ".\fileattribview.h"


// CFileAttribView

IMPLEMENT_DYNCREATE(CFileAttribView, CListView)

CFileAttribView::CFileAttribView()
{
}

CFileAttribView::~CFileAttribView()
{
}

BEGIN_MESSAGE_MAP(CFileAttribView, CListView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CFileAttribView 诊断

#ifdef _DEBUG
void CFileAttribView::AssertValid() const
{
	CListView::AssertValid();
}

void CFileAttribView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

#endif //_DEBUG

void CFileAttribView::ShowSelectedPathAttrib( CString &path )
{
	GetListCtrl().DeleteAllItems();

	path += "*.*";
	char tempItemText[1024] = "\0";
	WIN32_FIND_DATA wfd;
	HANDLE hFindFile = FindFirstFile( path, &wfd );
	SYSTEMTIME st;


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

		path = wfd.cFileName;
		if ( !(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
		{
			GetListCtrl().InsertItem( 0, path );

			// 插入修改日期
			FileTimeToSystemTime( &wfd.ftLastWriteTime, &st );
			sprintf( tempItemText, "%d年%d月%d日 %d:%d:%d", st.wYear,
				st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );
			GetListCtrl().SetItemText( 0, 1, tempItemText );

			// 插入文件属性
			sprintf( tempItemText, "%c  %c %c %c", 
				(wfd.dwFileAttributes & FILE_ATTRIBUTE_ARCHIVE) ? 'A' : ' ',
				(wfd.dwFileAttributes & FILE_ATTRIBUTE_READONLY) ? 'R' : ' ', 
				(wfd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ? 'H' : ' ', 
				(wfd.dwFileAttributes & FILE_ATTRIBUTE_SYSTEM) ? 'S' : ' ' );
			GetListCtrl().SetItemText( 0, 2, tempItemText );

			// 插入文件大小, 为了准确算出大小超过4GB的文件的大小，需要特殊处理。
			sprintf( tempItemText, "%d KB", 
				(DWORD)((((INT64)wfd.nFileSizeHigh<<(8*sizeof(DWORD))) +(wfd.nFileSizeLow))/1024) );
			GetListCtrl().SetItemText( 0, 3, tempItemText );
		}

	} while ( FindNextFile( hFindFile, &wfd ) );

	FindClose( hFindFile );
}

// CFileAttribView 消息处理程序

int CFileAttribView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	GetListCtrl().ModifyStyle(LVS_LIST,LVS_REPORT);
	GetListCtrl().InsertColumn(0,"文件名",LVCFMT_LEFT,180);
	GetListCtrl().InsertColumn(1,"修改日期",LVCFMT_LEFT,180);
	GetListCtrl().InsertColumn(2,"文件属性",LVCFMT_LEFT,60);
	GetListCtrl().InsertColumn(3,"大小",LVCFMT_RIGHT,120);

	return 0;
}
