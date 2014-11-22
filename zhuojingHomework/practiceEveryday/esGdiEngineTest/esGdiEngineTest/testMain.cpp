// esGdiEngine.cpp : 定义 DLL 应用程序的入口点。
//

#include "commonHeader.h"

esGdiEngine *pEngine = NULL;
egeSprite *pSpr = NULL;
egeFrameAnimation *pRoleAnima = NULL;

bool update()
{
	pRoleAnima->Update();
	return false;
}

bool render()
{
	pSpr->Render( 0, 0 );
	pRoleAnima->Render( 200, 200 );

	return true;
}

int WINAPI _tWinMain( IN HINSTANCE hInstance, 
					 IN HINSTANCE hPrevInstance, 
					 IN LPSTR lpCmdLine, 
					 IN int nShowCmd )
{
	pEngine = Engine_Create( hInstance );
	pEngine->Engine_Init();

	pEngine->SetUpdateFunc( update );
	pEngine->SetRenderFunc( render );
	pEngine->SetTitle( "烧饼的TEST" );
	pEngine->SetClearColor( RGB( 128, 255, 128 ) );

	PTEXTURE tex = pEngine->Texture_Load( "Image/bg.bmp" );
	pSpr = new egeSprite( tex, 0, 0, 
		pEngine->Texture_GetWidth( tex ),
		pEngine->Texture_GetHeight( tex ), false );
	pSpr->setHotSpot( 0, 0 );

	PTEXTURE myTexture = pEngine->Texture_Load( "Image/boomDie.bmp" );
	pRoleAnima = new egeFrameAnimation( myTexture, 12,
		166, 144, pEngine->Texture_GetWidth( myTexture ),
		pEngine->Texture_GetHeight( myTexture ), 
		FA_LOOP | FA_BACK | FA_NOPINGPONG, RGB( 128, 128, 128 ) );
	pRoleAnima->Play();
	// 	pRoleSpr = new egeSprite( myTexture, 0, 0, 
	// 		pEngine->Texture_GetWidth( myTexture ),
	// 		pEngine->Texture_GetHeight( myTexture ), 
	// 		true, RGB( 0, 255, 0 ));
	// 	pRoleSpr->setHotSpot( 32, 32 );
	// 	pRoleSpr->setTextureRect( 32, 32, 32, 32 );

	pEngine->Engine_Start();

	//////////////////////////////////////////////////////////////////////////
	//	资源释放
	//////////////////////////////////////////////////////////////////////////
	SAFE_DELETE( pRoleAnima );
	if ( myTexture )
	{
		pEngine->Texture_Free( myTexture );
	}
	SAFE_DELETE( pSpr );
	if ( tex )
	{
		pEngine->Texture_Free( tex );
	}
	Engine_Release();

	return 0;
}


