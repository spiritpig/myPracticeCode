#pragma once


// textabmp ��ͼ

class textabmp : public CView
{
	DECLARE_DYNCREATE(textabmp)

protected:
	textabmp();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~textabmp();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	DECLARE_MESSAGE_MAP()

private:
	CBitmap m_Bitmap;
	CDC m_backDc;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnEnUpdate();
	afx_msg void OnPaint();
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
};


