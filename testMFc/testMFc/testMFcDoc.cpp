// testMFcDoc.cpp :  CtestMFcDoc 类的实现
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


// CtestMFcDoc 构造/析构

CtestMFcDoc::CtestMFcDoc()
{
	// TODO: 在此添加一次性构造代码

}

CtestMFcDoc::~CtestMFcDoc()
{
}

BOOL CtestMFcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CtestMFcDoc 序列化

void CtestMFcDoc::Serialize(CArchive& ar)
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


// CtestMFcDoc 诊断

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


// CtestMFcDoc 命令
