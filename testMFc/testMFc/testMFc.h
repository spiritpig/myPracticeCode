// testMFc.h : testMFc Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CtestMFcApp:
// �йش����ʵ�֣������ testMFc.cpp
//

class CtestMFcApp : public CWinApp
{
public:
	CtestMFcApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CtestMFcApp theApp;
