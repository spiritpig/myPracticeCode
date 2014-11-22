// MyColorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "mfcFileReader.h"
#include "MyColorDlg.h"
#include ".\mycolordlg.h"


// CMyColorDlg 对话框

IMPLEMENT_DYNAMIC(CMyColorDlg, CDialog)
CMyColorDlg::CMyColorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyColorDlg::IDD, pParent)
{
	m_SelectColor = RGB( 0, 0, 0 );
}

CMyColorDlg::~CMyColorDlg()
{
}

void CMyColorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLORIMAGE, m_ColorImage);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}


BEGIN_MESSAGE_MAP(CMyColorDlg, CDialog)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


void CMyColorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_ColorImage.GetWindowRect( &m_ColorImageRect );

	if( point.x >= m_ColorImageRect.left && point.x <= m_ColorImageRect.right &&
		point.y >= m_ColorImageRect.top && point.y <= m_ColorImageRect.bottom )
	{
		HDC hdc = ::GetDC( m_hWnd );
		m_SelectColor = GetPixel( hdc, point.x, point.y );
		char buffer[1024];
		sprintf( buffer, "%0xd", (UINT)m_SelectColor );
		m_edit.SetWindowText( buffer );

		::ReleaseDC( m_hWnd, hdc );
	}

	CDialog::OnLButtonDown(nFlags, point);
}

LRESULT CMyColorDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
	case WM_LBUTTONDOWN:
		{
			m_ColorImage.GetClientRect( &m_ColorImageRect );
			POINT pt = { LOWORD( lParam ), HIWORD( lParam ) };

			if( PtInRect( &m_ColorImageRect, pt ) )
			{
				CClientDC cdc(this);
				m_SelectColor = cdc.GetPixel( pt );
				char buffer[1024];
				sprintf( buffer, "%0xd", (UINT)m_SelectColor );
				m_edit.SetWindowText( buffer );
				m_pParentWnd->SendMessage( WM_TEXTCOLORCHANGE, 0, 0 );
			}
		}
		break;
	}

	return CDialog::WindowProc( message, wParam, lParam );
}