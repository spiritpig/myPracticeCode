// FileAttribShower.h : FileAttribShower Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CFileAttribShowerApp:
// �йش����ʵ�֣������ FileAttribShower.cpp
//

class CFileAttribShowerApp : public CWinApp
{
public:
	CFileAttribShowerApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFileAttribShowerApp theApp;
