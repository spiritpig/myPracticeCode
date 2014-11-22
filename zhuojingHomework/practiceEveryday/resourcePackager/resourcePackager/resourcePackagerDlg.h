// resourcePackagerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CresourcePackagerDlg 对话框
class CresourcePackagerDlg : public CDialog
{
// 构造
public:
	CresourcePackagerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RESOURCEPACKAGER_DIALOG };

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
	CListBox m_FileList;
	PackFileHeader *m_pPackFileHeader;
	PackFileInfo *m_pPackFileInfo;
public:
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnBnClickedClearlist();

protected:
	char* GetFilename( char *path );
public:
	afx_msg void OnBnClickedPack();
};
