// KingdomRushMapEditorDoc.h :  CKingdomRushMapEditorDoc ��Ľӿ�
//


#pragma once

class CKingdomRushMapEditorDoc : public CDocument
{
protected: // �������л�����
	CKingdomRushMapEditorDoc();
	DECLARE_DYNCREATE(CKingdomRushMapEditorDoc)

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
	virtual ~CKingdomRushMapEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


