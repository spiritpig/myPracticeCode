// mfcDirShower.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CmfcDirShowerApp:
// �йش����ʵ�֣������ mfcDirShower.cpp
//

class CmfcDirShowerApp : public CWinApp
{
public:
	CmfcDirShowerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmfcDirShowerApp theApp;
