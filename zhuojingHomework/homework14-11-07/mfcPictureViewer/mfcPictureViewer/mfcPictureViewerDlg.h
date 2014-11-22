// mfcPictureViewerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CmfcPictureViewerDlg �Ի���
class CmfcPictureViewerDlg : public CDialog
{
// ����
public:
	CmfcPictureViewerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CmfcPictureViewerDlg();

// �Ի�������
	enum { IDD = IDD_MFCPICTUREVIEWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDropFiles(HDROP hDropInfo);

private:
	void _processInputBitmap( LPWSTR filename );

	WCHAR m_pName[1024];
	SCROLLINFO m_HScrollInfo, m_VScrollInfo;

	CDC m_BitmapDc, m_BackDc;
	HBITMAP m_Bitmap, m_BackBitmap;
	BITMAP m_BitmapInfo;
	RECT m_ClientRect;
};
