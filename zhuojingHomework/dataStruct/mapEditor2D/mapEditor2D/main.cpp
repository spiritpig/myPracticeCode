#include "AllDefine.h"

Sgge *g_pSgge=NULL;
Manage *g_MyGame=NULL;

bool Update()
{
	return g_MyGame->Update();
}

bool Render()
{
	return g_MyGame->Render();
}

int WINAPI _tWinMain( IN HINSTANCE hInstance, 
					 IN HINSTANCE hPrevInstance, 
					 IN LPSTR lpCmdLine, 
					 IN int nShowCmd )
{
	g_pSgge=SggeCreate(SGGE_VERSION);
	g_pSgge->Engine_SetState(SGGEES_SHOWLOGO,false);
	g_pSgge->Engine_SetState(SGGEES_UPDATEFUNC,Update);
	g_pSgge->Engine_SetState(SGGEES_RENDERFUNC,Render);
	g_pSgge->Engine_Initiate();

	//////////////////////////////////
	g_MyGame=new Manage;
	g_MyGame->Init();
	//////////////////////////////////


	g_pSgge->Engine_Start();

	//////////////////////////////////
	SAFE_DELETE(g_MyGame);
	//////////////////////////////////

	g_pSgge->Release();
	return 0;
}