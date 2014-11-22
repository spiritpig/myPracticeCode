// BNBMapEditorView.h : CBNBMapEditorView ��Ľӿ�
//


#pragma once


class CBNBMapEditorView : public CView
{
protected: // �������л�����
	CBNBMapEditorView();
	DECLARE_DYNCREATE(CBNBMapEditorView)

// ����
public:
	CBNBMapEditorDoc* GetDocument() const;

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
	virtual ~CBNBMapEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GameMap *m_pMap;
	HBITMAP m_hBackBufferBmp;
	HDC m_hBackBufferDc;
	RECT m_ClientRect;
	BLOCK_KIND m_CurBK;
	MAP_DISPLAY_STATE m_CurMds;
	bool m_isLeftMouseDown, m_isRightMouseDown;
	CString m_CurFileName;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCommandRange( UINT Id );
	afx_msg void OnClearmap();
	afx_msg void OnDisplayground();
	afx_msg void OnDisplayobject();
	afx_msg void OnDisplayall();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnFileNew();
};

#ifndef _DEBUG  // BNBMapEditorView.cpp �ĵ��԰汾
inline CBNBMapEditorDoc* CBNBMapEditorView::GetDocument() const
   { return reinterpret_cast<CBNBMapEditorDoc*>(m_pDocument); }
#endif

