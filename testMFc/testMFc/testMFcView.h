// testMFcView.h : CtestMFcView ��Ľӿ�
//


#pragma once


class CtestMFcView : public CView
{
protected: // �������л�����
	CtestMFcView();
	DECLARE_DYNCREATE(CtestMFcView)

// ����
public:
	CtestMFcDoc* GetDocument() const;

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
	virtual ~CtestMFcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // testMFcView.cpp �ĵ��԰汾
inline CtestMFcDoc* CtestMFcView::GetDocument() const
   { return reinterpret_cast<CtestMFcDoc*>(m_pDocument); }
#endif

