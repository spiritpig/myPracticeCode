// FileAttribShowerDoc.h :  CFileAttribShowerDoc ��Ľӿ�
//


#pragma once

class CFileAttribShowerDoc : public CDocument
{
protected: // �������л�����
	CFileAttribShowerDoc();
	DECLARE_DYNCREATE(CFileAttribShowerDoc)

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
	virtual ~CFileAttribShowerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


