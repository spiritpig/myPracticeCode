#pragma once


// CMyEditView 视图

class CMyEditView : public CEditView
{
	DECLARE_DYNCREATE(CMyEditView)

protected:
	CMyEditView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMyEditView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDropFiles(HDROP hDropInfo);

private:
	TCHAR* _getFileExtension( TCHAR *filename );
};


