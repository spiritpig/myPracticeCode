// dirTreeShower.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CdirTreeShowerApp:
// �йش����ʵ�֣������ dirTreeShower.cpp
//

class CdirTreeShowerApp : public CWinApp
{
public:
	CdirTreeShowerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CdirTreeShowerApp theApp;
