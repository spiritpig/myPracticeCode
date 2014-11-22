#include "commonHeader.h"

Sgge *g_pSgge = NULL;
Manage *g_pGame = NULL;

bool Update()
{
	return g_pGame->update();
}

bool Render()
{
	return g_pGame->render();
}

int WINAPI WinMain( IN HINSTANCE hInstance, 
					  IN HINSTANCE hPrevInstance, 
					  IN LPSTR lpCmdLine, 
					  IN int nShowCmd )
{
	g_pSgge=SggeCreate(SGGE_VERSION);
	g_pSgge->Engine_SetState(SGGEES_SHOWLOGO,false);
	g_pSgge->Engine_SetState(SGGEES_TITEL,"PlaneWar");
	g_pSgge->Engine_SetState(SGGEES_SCREENWIDTH,MAP_WIDTH);
	g_pSgge->Engine_SetState(SGGEES_SCREENHEIGHT, MAP_HEIGHT);
	g_pSgge->Engine_SetState(SGGEES_UPDATEFUNC,Update);
	g_pSgge->Engine_SetState(SGGEES_RENDERFUNC,Render);
	g_pSgge->Engine_Initiate();
	
	/////////ÓÎÏ·³õÊ¼»¯/////////
	g_pGame = new Manage;
	g_pGame->init();
	///////////////////////////

	g_pSgge->Engine_Start();

	////////////////////////////
	SAFE_DELETE( g_pGame );
	////////////////////////////

	g_pSgge->Release();

	return 0;
}