// NotepadEMDoc.h :  CNotepadEMDoc ��Ľӿ�
//


#pragma once

class CNotepadEMDoc : public CDocument
{
protected: // �������л�����
	CNotepadEMDoc();
	DECLARE_DYNCREATE(CNotepadEMDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CNotepadEMDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
	TCHAR* _getFileExtension( TCHAR *filename );
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
};


