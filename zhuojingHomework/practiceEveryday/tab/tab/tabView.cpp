// tabView.cpp : CtabView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CtabView ����/����

CtabView::CtabView()
{
	// TODO: �ڴ˴���ӹ������

}

CtabView::~CtabView()
{
}

BOOL CtabView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CtabView ����

void CtabView::OnDraw(CDC* /*pDC*/)
{
	CtabDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CtabView ��ӡ

BOOL CtabView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CtabView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CtabView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CtabView ���

#ifdef _DEBUG
void CtabView::AssertValid() const
{
	CView::AssertValid();
}

void CtabView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtabDoc* CtabView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtabDoc)));
	return (CtabDoc*)m_pDocument;
}
#endif //_DEBUG


// CtabView ��Ϣ�������
