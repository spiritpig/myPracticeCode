// KingdomRushMapEditorView.h : CKingdomRushMapEditorView 类的接口
//


#pragma once


class CKingdomRushMapEditorView : public CView
{
protected: // 仅从序列化创建
	CKingdomRushMapEditorView();
	DECLARE_DYNCREATE(CKingdomRushMapEditorView)

// 属性
public:
	CKingdomRushMapEditorDoc* GetDocument() const;

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
	// 判断当前是否处于设置起点或终点的状态
	bool m_isSetStart, m_isSetEnd;

// 生成的消息映射函数
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

#ifndef _DEBUG  // KingdomRushMapEditorView.cpp 的调试版本
inline CKingdomRushMapEditorDoc* CKingdomRushMapEditorView::GetDocument() const
   { return reinterpret_cast<CKingdomRushMapEditorDoc*>(m_pDocument); }
#endif

