// testPicCtrl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CtestPicCtrlApp:
// �йش����ʵ�֣������ testPicCtrl.cpp
//

class CtestPicCtrlApp : public CWinApp
{
public:
	CtestPicCtrlApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CtestPicCtrlApp theApp;
