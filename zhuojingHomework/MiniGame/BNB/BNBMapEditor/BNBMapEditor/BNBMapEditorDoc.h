// BNBMapEditorDoc.h :  CBNBMapEditorDoc ��Ľӿ�
//


#pragma once

class CBNBMapEditorDoc : public CDocument
{
protected: // �������л�����
	CBNBMapEditorDoc();
	DECLARE_DYNCREATE(CBNBMapEditorDoc)

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
	virtual ~CBNBMapEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


