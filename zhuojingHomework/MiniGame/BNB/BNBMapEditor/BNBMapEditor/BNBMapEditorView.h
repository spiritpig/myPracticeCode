// BNBMapEditorView.h : CBNBMapEditorView 类的接口
//


#pragma once


class CBNBMapEditorView : public CView
{
protected: // 仅从序列化创建
	CBNBMapEditorView();
	DECLARE_DYNCREATE(CBNBMapEditorView)

// 属性
public:
	CBNBMapEditorDoc* GetDocument() const;

// 操作
public:

// 重写
	public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
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

// 生成的消息映射函数
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

#ifndef _DEBUG  // BNBMapEditorView.cpp 的调试版本
inline CBNBMapEditorDoc* CBNBMapEditorView::GetDocument() const
   { return reinterpret_cast<CBNBMapEditorDoc*>(m_pDocument); }
#endif

