// BNBMapEditorDoc.cpp :  CBNBMapEditorDoc ���ʵ��
//

#include "stdafx.h"
#include "BNBMapEditor.h"

#include "BNBMapEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBNBMapEditorDoc

IMPLEMENT_DYNCREATE(CBNBMapEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CBNBMapEditorDoc, CDocument)
END_MESSAGE_MAP()


// CBNBMapEditorDoc ����/����

CBNBMapEditorDoc::CBNBMapEditorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CBNBMapEditorDoc::~CBNBMapEditorDoc()
{
}

BOOL CBNBMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CBNBMapEditorDoc ���л�

void CBNBMapEditorDoc::Serialize(CArchive& ar)
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


// CBNBMapEditorDoc ���

#ifdef _DEBUG
void CBNBMapEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBNBMapEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBNBMapEditorDoc ����
