// tabView.cpp : CtabView 类的实现
//

#include "stdafx.h"
#include "tab.h"

#include "tabDoc.h"
#include "tabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtabView

IMPLEMENT_DYNCREATE(CtabView, CView)

BEGIN_MESSAGE_MAP(CtabView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CtabView 构造/析构

CtabView::CtabView()
{
	// TODO: 在此处添加构造代码

}

CtabView::~CtabView()
{
}

BOOL CtabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CtabView 绘制

void CtabView::OnDraw(CDC* /*pDC*/)
{
	CtabDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CtabView 打印

BOOL CtabView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CtabView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CtabView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CtabView 诊断

#ifdef _DEBUG
void CtabView::AssertValid() const
{
	CView::AssertValid();
}

void CtabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtabDoc* CtabView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtabDoc)));
	return (CtabDoc*)m_pDocument;
}
#endif //_DEBUG


// CtabView 消息处理程序
