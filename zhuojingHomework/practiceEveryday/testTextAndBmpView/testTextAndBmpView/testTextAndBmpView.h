// testTextAndBmpView.h : testTextAndBmpView Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CtestTextAndBmpViewApp:
// �йش����ʵ�֣������ testTextAndBmpView.cpp
//

class CtestTextAndBmpViewApp : public CWinApp
{
public:
	CtestTextAndBmpViewApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtestTextAndBmpViewApp theApp;
