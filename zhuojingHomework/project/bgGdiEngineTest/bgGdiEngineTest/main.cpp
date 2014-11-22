#include "EingeDefine.h"

//#define CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

GdiEinge *g_pGdiEinge=NULL;
PSTEXTURE pbacktex;
PSTEXTURE pbacktex1;
Sprite *pspr;

PSTEXTURE proletex;
FrameAnimate *pFa;

UiManage *pUiManage;
UiStaticText *pst;
UiSrocllBar *psb;
UiButton *pedit;//(2223, "文字", NULL, NULL, NULL, 100, 100 );

float x=100.0f;
float y=100.0f;
int dir=1;

PSMUSIC music;
PSMUSIC music1;

bool Update()
{
	if(g_pGdiEinge->KeyDown('1'))
	{
		//pspr->SetTexture(pbacktex);
		//g_pGdiEinge->Eingne_SetState(EINGNES_FULLSCREEN,true);
		g_pGdiEinge->Eingne_SetState(EINGNES_TITLENAME,"植物大战");
	}

	if(g_pGdiEinge->KeyDown('2'))
	{
		//pspr->SetTexture(pbacktex1);
		//g_pGdiEinge->Eingne_SetState(EINGNES_FULLSCREEN,false);
		g_pGdiEinge->Eingne_SetState(EINGNES_TITLENAME,"XXXXXXXX");
	}

	if(g_pGdiEinge->KeyDown('3'))
	{
		g_pGdiEinge->MusicPlay(music1);
	}

	if(g_pGdiEinge->KeyPress('W'))
	{
		//if(dir!=0)
		//{
		//	pFa->SetFrameRange(4,6);
		//	pFa->SetCurrentFrame(4);
		//}
		dir=0;
		y-=g_pGdiEinge->GetFrameTime()*100;
	}

	if(g_pGdiEinge->KeyPress('S'))
	{
		//if(dir!=1)
		//{
		//	pFa->SetFrameRange(0,2);
		//	pFa->SetCurrentFrame(0);
		//}
		dir=1;
		y+=g_pGdiEinge->GetFrameTime()*100;
	}

	if(g_pGdiEinge->KeyPress('A'))
	{
		//if(dir!=2)
		//{
		//	pFa->SetFrameRange(2,4);
		//	pFa->SetCurrentFrame(2);
		//}
		dir=2;
		x-=g_pGdiEinge->GetFrameTime()*100;
	}

	if(g_pGdiEinge->KeyPress('D'))
	{
		//if(dir!=3)
		//{
		//	pFa->SetFrameRange(6,8);
		//	pFa->SetCurrentFrame(6);
		//}
		dir=3;
		x+=g_pGdiEinge->GetFrameTime()*100;
	}

// 
// 	pUiManage->Update();
// 
// 	UiMsg uimsg;
// 	if(pUiManage->PeekUiMessage(uimsg))
// 	{
// 		switch(uimsg.msg)
// 		{
// 		case UIAN_SETFOUCE:
// 			{
// 				switch(uimsg.pUiObject->GetType())
// 				{
// 				case UT_BUTTON:
// 					{
// 					}
// 					break;
// 				case UT_EDIT:
// 					{
// 					}
// 					break;
// 				case UT_SRCOLLBAR:
// 					{
// 					}
// 					break;
// 				case UT_STATICTEXT:
// 					{
// 					}
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 		switch(uimsg.Id)
// 		{
// 		case 222:
// 			{
// 				switch(uimsg.msg)
// 				{
// 				case UIEN_TEXTCHANGE:
// 					{
// 					}
// 					break;
// 				}
// 			}
// 			break;
// 		case 333:
// 			{
// 				switch(uimsg.msg)
// 				{
// 				case UISBN_MOVE:
// 					{
// 						pFa->SetFps(*((float *)(&(uimsg.fParam)))*30+5);
// 					}
// 					break;
// 				}
// 			}
// 			break;
// 		}
// 	}

	pedit->Update();

	pFa->Update();

	return false;
}

bool Render()
{
	g_pGdiEinge->Render_Clear(RGB(255,0,0));

	pspr->Render(320,240);
	pFa->Render((int)x,(int)y);
	pedit->Render();

	/*pUiManage->Render();*/

	return true;
}

int WINAPI _tWinMain( HINSTANCE hInstance, 
					 HINSTANCE hPrevInstance, 
					 LPSTR lpCmdLine, 
					 int nShowCmd )
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(64);
	g_pGdiEinge=GdiEingeCreate(hInstance);

	g_pGdiEinge->Eingne_SetState(EINGNES_UPDATEFUNC,Update);
	g_pGdiEinge->Eingne_SetState(EINGNES_RENDERFUNC,Render);
	g_pGdiEinge->Eingne_SetState(EINGNES_SCREENWIDTH,640);
	g_pGdiEinge->Eingne_SetState(EINGNES_SCREENHIGH,480);

	g_pGdiEinge->Eingne_Init();

	//pUiManage=new UiManage;

/*	pUiManage->AddUiCtrls(new UiButton(123,"确定",NULL,NULL,NULL,100,100,100,100,pUiManage));*/

	pedit=new UiButton( 123, "button", NULL, NULL, NULL, 0, 0, 100, 200, NULL );
// 		(222,"文字","editback.bmp","editframe.bmp",400,100,25,0,0,pUiManage,
// 		true,RGB(128,128,128),true,RGB(128,128,128));
//	pUiManage->AddUiCtrls(pedit);

// 	HFONT hfont=CreateFont(20,10,0,0,100,0,0,0,GB2312_CHARSET,OUT_DEFAULT_PRECIS,
// 		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"叶根友毛笔行书2.0版");
// 	pedit->SetFont(hfont);

//	pst=new UiStaticText(UIID_STATIC,"静态文本测试",100,150,150,30,pUiManage,pedit);

// 	psb=new UiSrocllBar(333,"确定",300,400,400,50,pUiManage);
// 	psb->SetLeftBtnInfor("scrollbtn\\lbtnup.bmp","scrollbtn\\lbtnon.bmp","scrollbtn\\lbtndown.bmp",
// 		true,RGB(128,128,128),true,RGB(128,128,128),true,RGB(128,128,128));
// 	psb->SetRightBtnInfor("scrollbtn\\rbtnup.bmp","scrollbtn\\rbtnon.bmp","scrollbtn\\rbtndown.bmp",
// 		true,RGB(128,128,128),true,RGB(128,128,128),true,RGB(128,128,128));
// 	psb->SetScrollBtnInfor("scrollbtn\\sbtnup.bmp","scrollbtn\\sbtnon.bmp","scrollbtn\\sbtndown.bmp",
// 		true,RGB(128,128,128),true,RGB(128,128,128),true,RGB(128,128,128));
// 	psb->SetScrollBackInfor("scrollbtn\\Scrollback.bmp",true,RGB(128,128,128));
// 	pUiManage->AddUiCtrls(psb);

	//pUiManage->DeleteUiCtrls(pUiManage->GetUiCtrls(222));
	//pUiManage->DeleteUiCtrls(pUiManage->GetUiCtrls(UIID_STATIC));

//	g_pGdiEinge->SetUiManage(pUiManage);

	pbacktex=g_pGdiEinge->LoadTexture("city.BMP");
	pbacktex1=g_pGdiEinge->LoadTexture("Place.bmp");
	pspr=new Sprite(pbacktex,0,0,g_pGdiEinge->GetTextureWidth(pbacktex),
		g_pGdiEinge->GetTextureHeight(pbacktex));
	pspr->SetHotSpot(0.5f,0.5f);

	proletex=g_pGdiEinge->LoadTexture("BoomDie.bmp");
	pFa=new FrameAnimate(proletex,166,144,0,5,true,RGB(128,128,128));
	pFa->Play();
	pFa->SetFrameRange(0,20);
	pFa->SetCurrentFrame(19);
	pFa->SetHotSpot(0.5f,0.5f);
	pFa->SetMode(FAMODE_BACK|FAMODE_LOOP|FAMODE_PINGPONG);

	music=g_pGdiEinge->LoadMusic("ZombiesOnYourLawn.wav");
	g_pGdiEinge->MusicVolume(music,3000);
	g_pGdiEinge->MusicPlay(music);
	music1=g_pGdiEinge->LoadMusic("effcet_sfx_sandan.wav");

	g_pGdiEinge->Eingne_Start();

	//SAFE_DELETE(pUiManage);
	SAFE_DELETE( pedit );
	g_pGdiEinge->MusicFree(music1);
	g_pGdiEinge->MusicFree(music);
	SAFE_DELETE(pFa);
	g_pGdiEinge->TextureFree(proletex);
	SAFE_DELETE(pspr);
	g_pGdiEinge->TextureFree(pbacktex); 
	g_pGdiEinge->TextureFree(pbacktex1);

	g_pGdiEinge->Release();
	return 0;
}

// crtIsValidHeapPointer