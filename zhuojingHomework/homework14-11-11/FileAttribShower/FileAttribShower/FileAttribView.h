#pragma once


// CFileAttribView 视图

class CFileAttribView : public CListView
{
	DECLARE_DYNCREATE(CFileAttribView)

protected:
	CFileAttribView();           // 动态创建所使用的受保护的构造函数
	virtual ~CFileAttribView();

public:
	void ShowSelectedPathAttrib( CString &path );
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


