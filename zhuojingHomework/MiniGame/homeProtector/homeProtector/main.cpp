#include "commonHeader.h"

Sgge *g_pSgge=NULL;
GameManager *g_pMyGame=NULL;

bool update()
{
	return g_pMyGame->update();
}

bool render()
{
	return g_pMyGame->render();
}

int WINAPI WinMain( IN HINSTANCE hInstance, 
					 IN HINSTANCE hPrevInstance, 
					 IN LPSTR lpCmdLine, 
					 IN int nShowCmd )
{
	g_pSgge=SggeCreate( SGGE_VERSION );
	g_pSgge->Engine_SetState( SGGEES_LOG, "ÈÕÖ¾.txt" );
	g_pSgge->Engine_SetState( SGGEES_SHOWLOGO, false );
	g_pSgge->Engine_SetState( SGGEES_USESOUND, true );
	g_pSgge->Engine_SetState( SGGEES_USEJOYSTICK, true );
	g_pSgge->Engine_SetState( SGGEES_NOFOCUSACTIVE, true );
	g_pSgge->Engine_SetState( SGGEES_SCREENWIDTH, SCREEN_WIDTH );
	g_pSgge->Engine_SetState( SGGEES_SCREENHEIGHT, SCREEN_HEIGHT );
	g_pSgge->Engine_SetState( SGGEES_UPDATEFUNC, update );
	g_pSgge->Engine_SetState( SGGEES_RENDERFUNC, render );
	g_pSgge->Engine_Initiate();

	g_pMyGame=new GameManager;
	g_pMyGame->init();

	g_pSgge->Engine_Start();

	SAFE_DELETE(g_pMyGame);

	g_pSgge->Release();
	return 0;
}