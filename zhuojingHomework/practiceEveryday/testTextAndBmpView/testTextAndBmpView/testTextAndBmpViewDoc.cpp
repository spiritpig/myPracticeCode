// testTextAndBmpViewDoc.cpp :  CtestTextAndBmpViewDoc ���ʵ��
//

#include "stdafx.h"
#include "testTextAndBmpView.h"

#include "testTextAndBmpViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestTextAndBmpViewDoc

IMPLEMENT_DYNCREATE(CtestTextAndBmpViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CtestTextAndBmpViewDoc, CDocument)
END_MESSAGE_MAP()


// CtestTextAndBmpViewDoc ����/����

CtestTextAndBmpViewDoc::CtestTextAndBmpViewDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CtestTextAndBmpViewDoc::~CtestTextAndBmpViewDoc()
{
}

BOOL CtestTextAndBmpViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CtestTextAndBmpViewDoc ���л�

void CtestTextAndBmpViewDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CtestTextAndBmpViewDoc ���

#ifdef _DEBUG
void CtestTextAndBmpViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtestTextAndBmpViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CtestTextAndBmpViewDoc ����
