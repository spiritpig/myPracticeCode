// KingdomRushMapEditorDoc.cpp :  CKingdomRushMapEditorDoc ���ʵ��
//

#include "stdafx.h"
#include "KingdomRushMapEditor.h"

#include "KingdomRushMapEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKingdomRushMapEditorDoc

IMPLEMENT_DYNCREATE(CKingdomRushMapEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CKingdomRushMapEditorDoc, CDocument)
END_MESSAGE_MAP()


// CKingdomRushMapEditorDoc ����/����

CKingdomRushMapEditorDoc::CKingdomRushMapEditorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CKingdomRushMapEditorDoc::~CKingdomRushMapEditorDoc()
{
}

BOOL CKingdomRushMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CKingdomRushMapEditorDoc ���л�

void CKingdomRushMapEditorDoc::Serialize(CArchive& ar)
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


// CKingdomRushMapEditorDoc ���

#ifdef _DEBUG
void CKingdomRushMapEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CKingdomRushMapEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CKingdomRushMapEditorDoc ����
