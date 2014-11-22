// KingdomRushMapEditorDoc.cpp :  CKingdomRushMapEditorDoc 类的实现
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


// CKingdomRushMapEditorDoc 构造/析构

CKingdomRushMapEditorDoc::CKingdomRushMapEditorDoc()
{
	// TODO: 在此添加一次性构造代码

}

CKingdomRushMapEditorDoc::~CKingdomRushMapEditorDoc()
{
}

BOOL CKingdomRushMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CKingdomRushMapEditorDoc 序列化

void CKingdomRushMapEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CKingdomRushMapEditorDoc 诊断

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


// CKingdomRushMapEditorDoc 命令
