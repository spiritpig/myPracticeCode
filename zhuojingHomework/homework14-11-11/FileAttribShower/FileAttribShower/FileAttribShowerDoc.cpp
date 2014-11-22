// FileAttribShowerDoc.cpp :  CFileAttribShowerDoc 类的实现
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


// CFileAttribShowerDoc 构造/析构

CFileAttribShowerDoc::CFileAttribShowerDoc()
{
	// TODO: 在此添加一次性构造代码

}

CFileAttribShowerDoc::~CFileAttribShowerDoc()
{
}

BOOL CFileAttribShowerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CFileAttribShowerDoc 序列化

void CFileAttribShowerDoc::Serialize(CArchive& ar)
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


// CFileAttribShowerDoc 诊断

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


// CFileAttribShowerDoc 命令
