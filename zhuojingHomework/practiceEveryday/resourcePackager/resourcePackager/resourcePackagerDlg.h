// resourcePackagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CresourcePackagerDlg �Ի���
class CresourcePackagerDlg : public CDialog
{
// ����
public:
	CresourcePackagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RESOURCEPACKAGER_DIALOG };

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
