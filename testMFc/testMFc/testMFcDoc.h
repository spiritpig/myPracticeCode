// testMFcDoc.h :  CtestMFcDoc ��Ľӿ�
//


#pragma once

class CtestMFcDoc : public CDocument
{
protected: // �������л�����
	CtestMFcDoc();
	DECLARE_DYNCREATE(CtestMFcDoc)

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
	virtual ~CtestMFcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


