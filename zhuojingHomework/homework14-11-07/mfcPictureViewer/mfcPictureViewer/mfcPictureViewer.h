// mfcPictureViewer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CmfcPictureViewerApp:
// �йش����ʵ�֣������ mfcPictureViewer.cpp
//

class CmfcPictureViewerApp : public CWinApp
{
public:
	CmfcPictureViewerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CmfcPictureViewerApp theApp;
