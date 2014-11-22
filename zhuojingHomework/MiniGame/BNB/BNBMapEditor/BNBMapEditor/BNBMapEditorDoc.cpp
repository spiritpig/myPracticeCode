// BNBMapEditorDoc.cpp :  CBNBMapEditorDoc 类的实现
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


// CBNBMapEditorDoc 构造/析构

CBNBMapEditorDoc::CBNBMapEditorDoc()
{
	// TODO: 在此添加一次性构造代码

}

CBNBMapEditorDoc::~CBNBMapEditorDoc()
{
}

BOOL CBNBMapEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CBNBMapEditorDoc 序列化

void CBNBMapEditorDoc::Serialize(CArchive& ar)
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


// CBNBMapEditorDoc 诊断

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


// CBNBMapEditorDoc 命令
