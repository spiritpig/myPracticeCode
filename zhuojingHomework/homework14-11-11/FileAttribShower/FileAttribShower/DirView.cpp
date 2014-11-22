// DirView.cpp : 实现文件
//

#include "stdafx.h"
#include "FileAttribShower.h"
#include "FileAttribView.h"
#include "DirView.h"
#include ".\dirview.h"


// CDirView

IMPLEMENT_DYNCREATE(CDirView, CTreeView)

CDirView::CDirView()
{
}

CDirView::~CDirView()
{
}

BEGIN_MESSAGE_MAP(CDirView, CTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnNMDblclk)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTvnSelchanged)
END_MESSAGE_MAP()


// CDirView 诊断

#ifdef _DEBUG
void CDirView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CDirView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG


// CDirView 消息处理程序
int CDirView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	char buffer[1024];
	DWORD size = 1024;
	GetUserName( buffer, &size);
	_stprintf( buffer, "%s 的电脑", buffer );
	m_hRoot = GetTreeCtrl().InsertItem( buffer );
	// 添加磁盘信息
	for( int i='A'; i<'Z'+1; ++i )
	{
		_stprintf( buffer, "%c:\\", i );
		if( GetVolumeInformation( buffer, NULL, 0, NULL, NULL, NULL, NULL, 0 ) )
		{
			GetTreeCtrl().InsertItem( buffer, m_hRoot );
		}
	}
	GetTreeCtrl().Expand( m_hRoot, TVE_EXPAND );

	return 0;
}

void CDirView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	_FillDirTree( GetTreeCtrl().GetSelectedItem() );
}

void CDirView::_FillDirTree( HTREEITEM item )
{
	// 已经扩展过得目录，直接返回
	if( GetTreeCtrl().GetChildItem( item ) != NULL )
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
			GetTreeCtrl().InsertItem( cStrTemp, item );
		}

	} while ( FindNextFile( hFindFile, &wfd ) );

	FindClose( hFindFile );
}

void CDirView::_GetItemPath( HTREEITEM item, CString &retStr )
{
	if( item == NULL )
	{
		return;
	}

	retStr.Empty();
	while ( GetTreeCtrl().GetParentItem( item ) != NULL )
	{
		retStr = GetTreeCtrl().GetItemText( item ) + retStr;
		item = GetTreeCtrl().GetParentItem( item );
	}
}
void CDirView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	if( pNMTreeView->itemOld.hItem != NULL )
	{
		_GetItemPath( pNMTreeView->itemNew.hItem, m_CurPath );

		POSITION pos;
		pos = GetDocument()->GetFirstViewPosition();
		GetDocument()->GetNextView( pos );
		((CFileAttribView *)(GetDocument()->GetNextView( pos )))->ShowSelectedPathAttrib( m_CurPath );
	}
}
