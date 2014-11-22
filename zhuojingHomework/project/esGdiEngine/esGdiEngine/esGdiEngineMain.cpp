// esGdiEngine.cpp : 定义 DLL 应用程序的入口点。
//

#ifdef _DEBUG

#include "commonHeader.h"
#include <stdio.h>

esGdiEngine *pEngine = NULL;
egeSprite *pSpr = NULL;
egeFrameAnimation *pRoleAnima = NULL;
egeUiButton *pBTN = NULL;
egeUiManager *pManager = NULL;
char buffer[1024];

bool update()
{
	pRoleAnima->Update();
	pManager->Update();

// 	if( ((egeUiScrollBar *)(pManager->getUiById(333)))->getRate() > 0.0f )
// 	{
// 		pRoleAnima->SetFps( ((egeUiScrollBar *)(pManager->getUiById(333)))->getRate()*30 );
// 	}
// 	else
// 	{
// 		pRoleAnima->SetFps( 0.01 );
// 	}

	buffer[0] = '\0';
	sprintf( buffer, "FPS: %.2f", pEngine->GetFps( 0.5f ) );
	pManager->getUiById( 999 )->SetText( buffer );
	
// 	if ( r > 0 )
// 	{
// 		pRoleAnima->SetFps( r );
// 	}

	return false;
}

bool render()
{
	pSpr->Render( 0, 0 );
	pManager->Render();
	pRoleAnima->Render( 200, 200 );

	return true;
}

int WINAPI _tWinMain( IN HINSTANCE hInstance,
			IN HINSTANCE hPrevInstance,
			IN LPSTR lpCmdLine,
			IN int nShowCmd )
{
	HANDLE hand = CreateMutex(NULL, NULL, "mutexsdsdsd");
	if(::GetLastError() == ERROR_ALREADY_EXISTS)
	{
		MessageBox( NULL, "不能同时运行两个测试程序！", NULL, NULL );
		ReleaseMutex( hand );
		return 0;
	}

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
//	pSpr->setHotSpot( 0.9f, 0.9f );

	PTEXTURE myTexture = pEngine->Texture_Load( "Image/boomDie.bmp" );
	pRoleAnima = new egeFrameAnimation( myTexture, 12,
		166, 144, pEngine->Texture_GetWidth( myTexture ),
		 		pEngine->Texture_GetHeight( myTexture ), 
				FA_LOOP | FA_FRONT | FA_PINGPONG, RGB( 128, 128, 128 ) );
	pRoleAnima->Play();

	pBTN = new egeUiButton( "button", 111, 200, 100, 300, 300,
				"Image/BtnUp.bmp","Image/BtnOn.bmp", "Image/BtnDown.bmp", 
				true, RGB( 128, 128, 128 ), true, RGB( 128, 128, 128 ), 
				true, RGB( 128, 128, 128 ) );
	pBTN->SetPos( 200, 200 );
	pBTN->SetHotSpot( 0.5f, 0.5f );

	pBTN->AddChild( new egeUiButton( "button22", 222, 60, 60, 100, 100,
									NULL, NULL, NULL ) );

	pManager = new egeUiManager();
 	pManager->addUi( pBTN );
	pManager->addUi( new egeUiButton( "button22", 222, 60, 60, 100, 100, NULL, NULL, NULL ) );
	//pManager->addUi( new egeUiEdit( "nihao", 2323, NULL, NULL, 400, 300, 100, 20, 1 ) );
	pManager->addUi( new egeUiScrollBar( "scrollBar", 333, 300, 500, 400, 30, 0.001f ) );
 	pManager->addUi( new egeUiStatic( "static", 999, 600, 100, 100, 100 ) );

	pEngine->setManager( pManager );
	pEngine->Engine_Start();

	//////////////////////////////////////////////////////////////////////////
	//	资源释放
	//////////////////////////////////////////////////////////////////////////
	SAFE_DELETE( pManager );
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

	ReleaseMutex( hand );
	return 0;
}

#endif
