// tabView.h : CtabView ��Ľӿ�
//


#pragma once


class CtabView : public CView
{
protected: // �������л�����
	CtabView();
	DECLARE_DYNCREATE(CtabView)

// ����
public:
	CtabDoc* GetDocument() const;

// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CtabView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

protected:
	CEdit cd;
	Cpicture
};

#ifndef _DEBUG  // tabView.cpp �ĵ��԰汾
inline CtabDoc* CtabView::GetDocument() const
   { return reinterpret_cast<CtabDoc*>(m_pDocument); }
#endif

