#include "AllDefine.h"

#define POS_OFFSET_MAX 200

esGdiEngine *pEngine = NULL;
egeFrameAnimation *pFA = NULL;
BaseObject *pCake = NULL;
BaseObject *pHero = NULL;
bool isPause = false;

int getNewRand()
{
	return (rand()%POS_OFFSET_MAX);// - POS_OFFSET_MAX/2);
}

bool Update()
{
	if( pEngine->KeyDown( 'P' ) )
	{
		isPause = !isPause;
	}

	pFA->Update();
	if( !isPause )
	{
		pCake->Update();
		pCake->onHitObject( pHero );
		pHero->Update();
	}

	return false;
}

bool Render()
{
	pFA->Render( 300, 300 );
	pCake->Render();
	pHero->Render();

	RECT r = { 100, 100, 200, 200 };
	char buffer[1024];
	sprintf( buffer, "%f", pEngine->Time_GetFrameTime() );
	pEngine->DrawText( (HFONT)GetStockObject( SYSTEM_FONT ), buffer, 
		r );

	return true;
}

int WINAPI _tWinMain( IN HINSTANCE hInstance, 
					 IN HINSTANCE hPrevInstance, 
					 IN LPSTR lpCmdLine, 
					 IN int nShowCmd )
{
	timeBeginPeriod( 1 );
	//////////////////////////////////////////////////////////////////////////
	//	初始化引擎
	//////////////////////////////////////////////////////////////////////////
	pEngine = Engine_Create( hInstance );
	pEngine->Engine_Init();
	pEngine->SetClearColor( RGB( 128, 255, 128 ) );
	pEngine->SetRenderFunc( Render );
	pEngine->SetUpdateFunc( Update );


	//////////////////////////////////////////////////////////////////////////
	//	加载资源
	//////////////////////////////////////////////////////////////////////////
	PTEXTURE tex2 = pEngine->Texture_Load( "Image/zombieWalk.bmp" );
 	pFA = new egeFrameAnimation( tex2, 10, 166, 144, 1660, 288,
 		FA_LOOP | FA_FRONT | FA_PINGPONG, RGB( 128, 128, 128 ) );
 	pFA->setFrameRange( 0, 14 );
 	pFA->Play();

	PTEXTURE hcTex = pEngine->Texture_Load( "Image/hotcake.bmp" );
	pCake = new Food( hcTex, true, RGB( 128, 255, 128 ) );
	pCake->setPos( egeVec2D(60.0f, 50.0f) );
	pCake->setVec( egeVec2D(10.0f, -10.0f) );
	pCake->setAccer( egeVec2D(0.0f, 100.0f) );
	pCake->setBorderRange( 60, 60, 640, 540 );

	PTEXTURE heroTex = pEngine->Texture_Load( "Image/hero.bmp" );
	pHero = new Hero( heroTex, true, RGB( 128, 255, 128 ) );
	pHero->setPos( egeVec2D(300.0f, 540.0f) );
	pHero->setVec( egeVec2D(0.0f, 0.0f) );
	pHero->setAccer( egeVec2D(0.0f, 0.0f) );
	pHero->setBorderRange( 60, 60, 640, 540 );

	//////////////////////////////////////////////////////////////////////////
	//	引擎启动
	//////////////////////////////////////////////////////////////////////////
	pEngine->Engine_Start();
	

	//////////////////////////////////////////////////////////////////////////
	//	释放资源
	//////////////////////////////////////////////////////////////////////////
	SAFE_DELETE( pHero );
	if( heroTex )
	{
		pEngine->Texture_Free( heroTex );
	}
	SAFE_DELETE( pCake );
	if( hcTex )
	{
		pEngine->Texture_Free( hcTex );
	}

	SAFE_DELETE( pFA );
	if ( tex2 )
	{
		pEngine->Texture_Free( tex2 );
	}

	Engine_Release();

	return 0;
}