// KingdomRushMapEditor.h : KingdomRushMapEditor Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CKingdomRushMapEditorApp:
// �йش����ʵ�֣������ KingdomRushMapEditor.cpp
//

class CKingdomRushMapEditorApp : public CWinApp
{
public:
	CKingdomRushMapEditorApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKingdomRushMapEditorApp theApp;
