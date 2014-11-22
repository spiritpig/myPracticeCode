#pragma once


// CMyEditView ��ͼ

class CMyEditView : public CEditView
{
	DECLARE_DYNCREATE(CMyEditView)

protected:
	CMyEditView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


