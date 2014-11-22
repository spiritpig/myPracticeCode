// mfcFileReaderDlg.h : 头文件
//

#pragma once


// CmfcFileReaderDlg 对话框
class CmfcFileReaderDlg : public CDialog
{
// 构造
public:
	CmfcFileReaderDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CmfcFileReaderDlg();

// 对话框数据
	enum { IDD = IDD_MFCFILEREADER_DIALOG };

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
public:
	afx_msg void OnBnClickedOpenfile();
	afx_msg void OnBnClickedFontset();

	CMyColorDlg *m_myColorDlg;
	char *m_TextBuffer;
	RECT m_ClientRect;
	LOGFONT m_TextFontLog;
	COLORREF m_BgColor;
	COLORREF m_TextColor;
	afx_msg void OnBnClickedFontcolor();
	afx_msg void OnBnClickedBgcolor();
	afx_msg void OnBnClickedFight();
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
