// NotepadEM.h : NotepadEM Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CNotepadEMApp:
// �йش����ʵ�֣������ NotepadEM.cpp
//

class CNotepadEMApp : public CWinApp
{
public:
	CNotepadEMApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CNotepadEMApp theApp;
