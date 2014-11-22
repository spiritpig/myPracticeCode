// testTextAndBmpViewDoc.cpp :  CtestTextAndBmpViewDoc 类的实现
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


// CtestTextAndBmpViewDoc 构造/析构

CtestTextAndBmpViewDoc::CtestTextAndBmpViewDoc()
{
	// TODO: 在此添加一次性构造代码

}

CtestTextAndBmpViewDoc::~CtestTextAndBmpViewDoc()
{
}

BOOL CtestTextAndBmpViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CtestTextAndBmpViewDoc 序列化

void CtestTextAndBmpViewDoc::Serialize(CArchive& ar)
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


// CtestTextAndBmpViewDoc 诊断

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


// CtestTextAndBmpViewDoc 命令
