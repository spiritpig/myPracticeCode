// testMFcView.cpp : CtestMFcView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CtestMFcView ����/����

CtestMFcView::CtestMFcView()
{
	// TODO: �ڴ˴���ӹ������

}

CtestMFcView::~CtestMFcView()
{
}

BOOL CtestMFcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CtestMFcView ����

void CtestMFcView::OnDraw(CDC* /*pDC*/)
{
	CtestMFcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CtestMFcView ��ӡ

BOOL CtestMFcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CtestMFcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CtestMFcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CtestMFcView ���

#ifdef _DEBUG
void CtestMFcView::AssertValid() const
{
	CView::AssertValid();
}

void CtestMFcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestMFcDoc* CtestMFcView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestMFcDoc)));
	return (CtestMFcDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestMFcView ��Ϣ�������
