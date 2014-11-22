// textabmp.cpp : 实现文件
//

#include "stdafx.h"
#include "testTextAndBmpView.h"
#include "textabmp.h"
#include ".\textabmp.h"


// textabmp

IMPLEMENT_DYNCREATE(textabmp, CEditView)

textabmp::textabmp()
{
	m_Bitmap.Attach( (HBITMAP)LoadImage( NULL, "25.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE ) );
	m_backDc.CreateCompatibleDC( NULL );
	m_backDc.SelectObject( m_Bitmap );
}

textabmp::~textabmp()
{
	m_Bitmap.Detach();
	m_backDc.DeleteDC();
}

BEGIN_MESSAGE_MAP(textabmp, CEditView)
END_MESSAGE_MAP()


// textabmp 诊断

#ifdef _DEBUG
void textabmp::AssertValid() const
{
	CEditView::AssertValid();
}

void textabmp::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

