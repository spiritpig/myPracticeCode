// dirTreeShowerDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CdirTreeShowerDlg 对话框
class CdirTreeShowerDlg : public CDialog
{
// 构造
public:
	CdirTreeShowerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DIRTREESHOWER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	void _GetItemPath( HTREEITEM item, CString &retStr );
	void _FillDirTree( HTREEITEM item );
	// 目录树控件
	CTreeCtrl m_DirTreeCtrl;
	TCHAR buffer[1024];
public:
	afx_msg void OnNMDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
