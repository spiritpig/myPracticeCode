// tabDoc.cpp :  CtabDoc ���ʵ��
//

#include "stdafx.h"
#include "tab.h"

#include "tabDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtabDoc

IMPLEMENT_DYNCREATE(CtabDoc, CDocument)

BEGIN_MESSAGE_MAP(CtabDoc, CDocument)
END_MESSAGE_MAP()


// CtabDoc ����/����

CtabDoc::CtabDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CtabDoc::~CtabDoc()
{
}

BOOL CtabDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CtabDoc ���л�

void CtabDoc::Serialize(CArchive& ar)
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


// CtabDoc ���

#ifdef _DEBUG
void CtabDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtabDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CtabDoc ����
