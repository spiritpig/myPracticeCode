// mfcFileReader.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CmfcFileReaderApp:
// �йش����ʵ�֣������ mfcFileReader.cpp
//

class CmfcFileReaderApp : public CWinApp
{
public:
	CmfcFileReaderApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmfcFileReaderApp theApp;
