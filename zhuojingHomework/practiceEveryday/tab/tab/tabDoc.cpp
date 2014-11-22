// tabDoc.cpp :  CtabDoc 类的实现
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


// CtabDoc 构造/析构

CtabDoc::CtabDoc()
{
	// TODO: 在此添加一次性构造代码

}

CtabDoc::~CtabDoc()
{
}

BOOL CtabDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CtabDoc 序列化

void CtabDoc::Serialize(CArchive& ar)
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


// CtabDoc 诊断

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


// CtabDoc 命令
