// testMFcDoc.cpp :  CtestMFcDoc ���ʵ��
//

#include "stdafx.h"
#include "testMFc.h"

#include "testMFcDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestMFcDoc

IMPLEMENT_DYNCREATE(CtestMFcDoc, CDocument)

BEGIN_MESSAGE_MAP(CtestMFcDoc, CDocument)
END_MESSAGE_MAP()


// CtestMFcDoc ����/����

CtestMFcDoc::CtestMFcDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CtestMFcDoc::~CtestMFcDoc()
{
}

BOOL CtestMFcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CtestMFcDoc ���л�

void CtestMFcDoc::Serialize(CArchive& ar)
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


// CtestMFcDoc ���

#ifdef _DEBUG
void CtestMFcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CtestMFcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CtestMFcDoc ����
