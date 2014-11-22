// mfcFileReaderDlg.h : ͷ�ļ�
//

#pragma once


// CmfcFileReaderDlg �Ի���
class CmfcFileReaderDlg : public CDialog
{
// ����
public:
	CmfcFileReaderDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CmfcFileReaderDlg();

// �Ի�������
	enum { IDD = IDD_MFCFILEREADER_DIALOG };

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
