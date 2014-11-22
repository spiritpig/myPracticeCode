// testMFcView.cpp : CtestMFcView 类的实现
//

#include "stdafx.h"
#include "testMFc.h"

#include "testMFcDoc.h"
#include "testMFcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestMFcView

IMPLEMENT_DYNCREATE(CtestMFcView, CView)

BEGIN_MESSAGE_MAP(CtestMFcView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CtestMFcView 构造/析构

CtestMFcView::CtestMFcView()
{
	// TODO: 在此处添加构造代码

}

CtestMFcView::~CtestMFcView()
{
}

BOOL CtestMFcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CtestMFcView 绘制

void CtestMFcView::OnDraw(CDC* /*pDC*/)
{
	CtestMFcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CtestMFcView 打印

BOOL CtestMFcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CtestMFcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CtestMFcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CtestMFcView 诊断

#ifdef _DEBUG
void CtestMFcView::AssertValid() const
{
	CView::AssertValid();
}

void CtestMFcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestMFcDoc* CtestMFcView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestMFcDoc)));
	return (CtestMFcDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestMFcView 消息处理程序
