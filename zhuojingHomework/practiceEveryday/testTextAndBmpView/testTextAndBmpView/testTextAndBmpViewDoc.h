// testTextAndBmpViewDoc.h :  CtestTextAndBmpViewDoc ��Ľӿ�
//


#pragma once

class CtestTextAndBmpViewDoc : public CDocument
{
protected: // �������л�����
	CtestTextAndBmpViewDoc();
	DECLARE_DYNCREATE(CtestTextAndBmpViewDoc)

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
	virtual ~CtestTextAndBmpViewDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


