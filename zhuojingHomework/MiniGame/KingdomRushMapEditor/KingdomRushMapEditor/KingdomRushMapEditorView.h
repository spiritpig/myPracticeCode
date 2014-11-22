// KingdomRushMapEditorView.h : CKingdomRushMapEditorView ��Ľӿ�
//


#pragma once


class CKingdomRushMapEditorView : public CView
{
protected: // �������л�����
	CKingdomRushMapEditorView();
	DECLARE_DYNCREATE(CKingdomRushMapEditorView)

// ����
public:
	CKingdomRushMapEditorDoc* GetDocument() const;

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
	virtual ~CKingdomRushMapEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	CDC *m_pCDc;
	HDC m_hBackBufferDc;
	HBITMAP m_hBackBufferBmp;
	RECT m_ClientRect;
	bool m_isDown;

	char m_curFileName[1024];
	KingdomRushMap *m_pMap;
	// �жϵ�ǰ�Ƿ������������յ��״̬
	bool m_isSetStart, m_isSetEnd;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClearmap();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSetstart();
	afx_msg void OnSetend();

	void SetPath( const POINT &cursorPos );
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnFileNew();
};

#ifndef _DEBUG  // KingdomRushMapEditorView.cpp �ĵ��԰汾
inline CKingdomRushMapEditorDoc* CKingdomRushMapEditorView::GetDocument() const
   { return reinterpret_cast<CKingdomRushMapEditorDoc*>(m_pDocument); }
#endif

