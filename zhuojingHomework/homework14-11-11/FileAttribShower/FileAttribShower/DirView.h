#pragma once


// CDirView 视图

class CDirView : public CTreeView
{
	DECLARE_DYNCREATE(CDirView)

protected:
	CDirView();           // 动态创建所使用的受保护的构造函数
	virtual ~CDirView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);

private:
	void _FillDirTree( HTREEITEM item );
	void _GetItemPath( HTREEITEM item, CString &retStr );

	CString m_CurPath;
	HTREEITEM m_hRoot;
public:
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


