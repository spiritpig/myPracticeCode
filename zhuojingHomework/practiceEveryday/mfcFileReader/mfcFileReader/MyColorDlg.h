#pragma once
#include "resource.h"
#include "afxwin.h"


// CMyColorDlg �Ի���

class CMyColorDlg : public CDialog
{
	DECLARE_DYNAMIC(CMyColorDlg)

public:
	CMyColorDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyColorDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	RECT m_ColorImageRect;
	CStatic m_ColorImage;
	COLORREF m_SelectColor;
public:
	COLORREF getCurrentColor()
	{
		return m_SelectColor;
	}
private:
	CEdit m_edit;
};
