// resourcePackager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CresourcePackagerApp:
// �йش����ʵ�֣������ resourcePackager.cpp
//

class CresourcePackagerApp : public CWinApp
{
public:
	CresourcePackagerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CresourcePackagerApp theApp;
