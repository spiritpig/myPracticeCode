// tabDoc.h :  CtabDoc ��Ľӿ�
//


#pragma once

class CtabDoc : public CDocument
{
protected: // �������л�����
	CtabDoc();
	DECLARE_DYNCREATE(CtabDoc)

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
	virtual ~CtabDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


