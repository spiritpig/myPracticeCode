// BNBMapEditor.h : BNBMapEditor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CBNBMapEditorApp:
// �йش����ʵ�֣������ BNBMapEditor.cpp
//

class CBNBMapEditorApp : public CWinApp
{
public:
	CBNBMapEditorApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBNBMapEditorApp theApp;
