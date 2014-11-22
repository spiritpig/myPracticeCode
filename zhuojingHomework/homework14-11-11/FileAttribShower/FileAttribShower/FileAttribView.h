#pragma once


// CFileAttribView ��ͼ

class CFileAttribView : public CListView
{
	DECLARE_DYNCREATE(CFileAttribView)

protected:
	CFileAttribView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


