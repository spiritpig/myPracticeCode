#include <windows.h>
#include <tchar.h>
#include <MMSystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Msimg32.lib")
#include "AllDefine.h"
#include <vld.h>
#pragma comment( lib, "Gdi_Engine.lib" )

GdiEngine g_Ge;
GdiSpriter *g_pSpr=NULL;
GdiFrameAnimation *g_pFa=NULL;
GuiManage *m_pGuiManage=NULL;
GuiDailogBox *pDailog=NULL;
HINSTANCE g_hInst;

int x=0;

void TimerProc(void)
{
	//g_pFa->Render(200,200);
}

void MyGuiProcess(UINT msg,UINT p1,UINT p2)
{
	switch(msg)
	{
	case GUIMSG_BTNCLIKE:
		{
			pDailog->ShowDailog();
		}
		break;
	case GUIMSG_EDITCHANGE:
		{
			MessageBox(0,((GuiObject *)(p2))->GetGuiCtrlName(),0,0);
		}
		break;
	}
}

bool Updata()
{
	x+=10;
	if(x>=700)
	{
		x=0;
	}

	if(g_Ge.Input_KeyUp('1'))
	{
		g_Ge.Engine_SetState(ENGINESTATE_CURSOR,"1.ani");
	}

	if(g_Ge.Input_KeyDown('2'))
	{
		g_Ge.Engine_SetState(ENGINESTATE_CURSOR,"3.ani");
	}

	if(g_Ge.Input_KeyDown('3'))
	{
		g_Ge.Engine_SetState(ENGINESTATE_ICON,"天之道.ico");
	}

	if(g_Ge.Input_KeyDown('4'))
	{
		g_Ge.Engine_SetState(ENGINESTATE_ICON,"贪吃蛇.ico");
	}

	g_pFa->Updata(g_Ge.Timer_GetFrameTime());

	//GuiMsg gm;
	//if(m_pGuiManage->GetMessage(gm))
	//{
	//	switch(gm.guimsg)
	//	{
	//	case GUIMSG_BTNCLIKE:
	//		{
	//			MessageBox(0,0,0,0);
	//		}
	//		break;
	//	case GUIMSG_EDITCHANGE:
	//		{
	//			MessageBox(0,((GuiObject *)(gm.Param2))->GetGuiCtrlName(),0,0);
	//		}
	//		break;
	//	}
	//}

	return false;
}

bool Render()
{
	g_Ge.Engine_Clear(0x00ff0000);

	g_pSpr->Render(0,0,800,600);
	g_pFa->Render(100,100);

	return true;
}

int WINAPI _tWinMain( IN HINSTANCE hInstance, 
					 IN HINSTANCE hPrevInstance, 
					 IN LPSTR lpCmdLine, 
					 IN int nShowCmd )
{
	g_hInst=hInstance;
	g_Ge.Engine_SetState(ENGINESTATE_FULLSCREEN,false);
	g_Ge.Engine_SetState(ENGINESTATE_UPDATEFUNC,Updata);
	g_Ge.Engine_SetState(ENGINESTATE_RENDERFUNC,Render);
	g_Ge.Engine_Init();
	g_Ge.Timer_SetTimer(0,1.0f,TimerProc);

	g_pSpr=g_Ge.Spriter_Load("city.bmp",true,RGB(255,0,255));
	g_pFa=g_Ge.FrameAnimation_Load("BoomDie1.bmp",166,144,6,0,true,RGB(128,128,128));
	g_pFa->SetFramePlayMode(FASTATE_BACK|FASTATE_LOOP|FASTATE_PINGPONG);
	m_pGuiManage=new GuiManage(&g_Ge);

// 	GuiButtonData gbd;
// 	gbd.dwId=100;
// 	gbd.DownImage="downimage.bmp";
// 	gbd.UpImage="upimage.bmp";
// 	gbd.CtrlName="确定";
// 	gbd.Pos.x=10;
// 	gbd.Pos.y=10;
// // 	m_pGuiManage->AddGuiObject(GUI_BUTTON,&gbd);
// 
// 	GuiButton *gb = new GuiButton( &g_Ge );
// 	gbd.Pos.x = 300;
// 	gbd.Pos.y = 300;
// 	gb->Init( m_pGuiManage, &gbd );
// 	gb->Updata(g_Ge.Timer_GetFrameTime());

	GuiDailogBoxData gdbd;
	gdbd.dwId=300;
	gdbd.CtrlName="对话框";
	gdbd.Pos.x=100;
	gdbd.Pos.y=100;
	gdbd.Width=500;
	gdbd.Height=300;
	m_pGuiManage->AddGuiObject(GUI_DAILOGBOX,&gdbd);
	pDailog=(GuiDailogBox *)(m_pGuiManage->GetGuiObject(300));

	GuiStaticTextData gstd;
	gstd.dwId=110;
	gstd.CtrlName="静态文本";
	gstd.Pos.x=10;
	gstd.Pos.y=20;
	gstd.TextColor=RGB(255,255,0);
	pDailog->AddGuiObject(GUI_STATICTEXT,&gstd);

	GuiEditData ged;
	ged.dwId=105;
	ged.BackImage="editback.bmp";
	ged.CtrlName="abcd";
	ged.Pos.x=10;
	ged.Pos.y=100;
	pDailog->AddGuiObject(GUI_EDIT,&ged);

	g_Ge.Engine_SetState(ENGINESTATE_GUIMANAGE,m_pGuiManage);
	g_Ge.Engine_SetState(ENGINESTATE_GUIPROCE,MyGuiProcess);

	g_Ge.Engine_Start();

	g_Ge.FrameAnimation_Free(g_pFa);
	g_Ge.Spriter_Free(g_pSpr);

	return 0;
}
