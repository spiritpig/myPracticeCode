// dirTreeShowerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CdirTreeShowerDlg �Ի���
class CdirTreeShowerDlg : public CDialog
{
// ����
public:
	CdirTreeShowerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DIRTREESHOWER_DIALOG };

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
private:
	void _GetItemPath( HTREEITEM item, CString &retStr );
	void _FillDirTree( HTREEITEM item );
	// Ŀ¼���ؼ�
	CTreeCtrl m_DirTreeCtrl;
	TCHAR buffer[1024];
public:
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
