// FileAttribShowerDoc.cpp :  CFileAttribShowerDoc ���ʵ��
//

#include "stdafx.h"
#include "FileAttribShower.h"

#include "FileAttribShowerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileAttribShowerDoc

IMPLEMENT_DYNCREATE(CFileAttribShowerDoc, CDocument)

BEGIN_MESSAGE_MAP(CFileAttribShowerDoc, CDocument)
END_MESSAGE_MAP()


// CFileAttribShowerDoc ����/����

CFileAttribShowerDoc::CFileAttribShowerDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CFileAttribShowerDoc::~CFileAttribShowerDoc()
{
}

BOOL CFileAttribShowerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CFileAttribShowerDoc ���л�

void CFileAttribShowerDoc::Serialize(CArchive& ar)
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


// CFileAttribShowerDoc ���

#ifdef _DEBUG
void CFileAttribShowerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFileAttribShowerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFileAttribShowerDoc ����
