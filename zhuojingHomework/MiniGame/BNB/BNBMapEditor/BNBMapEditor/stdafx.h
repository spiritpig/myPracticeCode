// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// ��Ŀ�ض��İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// �� Windows ��ͷ���ų�����ʹ�õ�����
#endif

// ���������ʹ��������ָ����ƽ̨֮ǰ��ƽ̨�����޸�����Ķ��塣
// �йز�ͬƽ̨����Ӧֵ��������Ϣ����ο� MSDN��
#ifndef WINVER				// ����ʹ�� Windows 95 �� Windows NT 4 ����߰汾���ض����ܡ�
#define WINVER 0x0400		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_WINNT		// ����ʹ�� Windows NT 4 ����߰汾���ض����ܡ�
#define _WIN32_WINNT 0x0400		//Ϊ Windows98 �� Windows 2000 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif						

#ifndef _WIN32_WINDOWS		// ����ʹ�� Windows 98 ����߰汾���ض����ܡ�
#define _WIN32_WINDOWS 0x0410 //Ϊ Windows Me �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#ifndef _WIN32_IE			// ����ʹ�� IE 4.0 ����߰汾���ض����ܡ�
#define _WIN32_IE 0x0400	//Ϊ IE 5.0 �����°汾�ı�Ϊ�ʵ���ֵ��
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ��������������ȫ���Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ���ĺͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����

#include <afxdtctl.h>		// Internet Explorer 4 �����ؼ��� MFC ֧��
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// Windows �����ؼ��� MFC ֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

enum BLOCK_KIND
{
	BK_NONE,
	BK_GRASS1,
	BK_GRASS2,
	BK_GRASS3,
	BK_GRASS4,
	BK_GRASS5,
	BK_ROAD1,
	BK_ROAD2,
	BK_ROAD3,

	BK_HOUSE1 = 10,
	BK_HOUSE2,
	BK_HOUSE3,
	BK_TREE,
	BK_BLOCK1,
	BK_BLOCK2,
	BK_BOX,

	BK_HOUSE1TOP = 20,
	BK_HOUSE2TOP,
	BK_HOUSE3TOP,
	BK_TREETOP,
	BK_BLOCK1TOP,
	BK_BLOCK2TOP,
	BK_BOXTOP
};

enum MAP_DISPLAY_STATE
{
	MDS_BACK,
	MDS_TOPANDMID,
	MDS_ALL
};

#define CLIENT_WIDTH	800
#define CLIENT_HEIGHT	600
#define MAP_MAX_ROW		13
#define MAP_MAX_CEL		15
#define BLOCK_SIZE		40

#define SAFE_DELETE(p) { if(p) { delete p; p=NULL; } }
#define SAFE_DELARR(p) { if(p) { delete []p; p=NULL; } }

#include "GameMap.h"