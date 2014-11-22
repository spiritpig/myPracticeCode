#include "StdAfx.h"
#include ".\kingdomrushmap.h"
using namespace std;

static HDC hBackBufferDc = NULL;

KingdomRushMap::KingdomRushMap(void)
{
	m_hBgDc = CreateCompatibleDC(  NULL );
	m_hBgBmp = (HBITMAP)LoadImage( NULL, "Image//background//bg1.bmp", 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	SelectObject( m_hBgDc, m_hBgBmp );

	m_hMonsterMoveBlockDc = CreateCompatibleDC( NULL );
	m_hMonsterMoveBlockBmp= (HBITMAP)LoadImage( NULL, "Image//monsterMoveBlock.bmp", 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	SelectObject( m_hMonsterMoveBlockDc, m_hMonsterMoveBlockBmp );

	m_MapSize.x = 700;
	m_MapSize.y = 600;

	m_hStartPointDc = CreateCompatibleDC( NULL );
	m_hStartPointBmp= (HBITMAP)LoadImage( NULL, "Image//startPoint.bmp", 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	SelectObject( m_hStartPointDc, m_hStartPointBmp );

	m_hEndPointDc = CreateCompatibleDC( NULL );
	m_hEndPointBmp= (HBITMAP)LoadImage( NULL, "Image//endPoint.bmp", 
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE );
	SelectObject( m_hEndPointDc, m_hEndPointBmp );

	m_StartPointSize.x = 80;
	m_StartPointSize.y = 40;
	m_EndPointSize.x = 80;
	m_EndPointSize.y = 40;
	m_StartPoint.x = 0;
	m_StartPoint.y = 0;
	m_EndPoint.x = 0;
	m_EndPoint.y = 0;

	m_MonsterMovePath.clear();
	m_hPen = CreatePen( PS_SOLID, 5, RGB( 0, 162, 232 ) );

	isSetStart = false;
	isSetEnd = false;
}

KingdomRushMap::~KingdomRushMap(void)
{
	DeleteObject( m_hPen );

	DeleteObject( m_hStartPointBmp );
	DeleteDC( m_hStartPointDc );
	DeleteObject( m_hEndPointBmp );
	DeleteDC( m_hEndPointDc);

	DeleteObject( m_hMonsterMoveBlockBmp );
	DeleteDC( m_hMonsterMoveBlockDc );

	DeleteObject( m_hBgBmp );
	DeleteDC( m_hBgDc );

	hBackBufferDc = NULL;
}

void KingdomRushMap::Init( HDC hInputBackBufferDc, HWND hWnd )
{
	m_hWnd = hWnd;
	hBackBufferDc = hInputBackBufferDc;
	SelectObject( hBackBufferDc, m_hPen );
}

void KingdomRushMap::Render()
{
	// 绘制背景图
	BitBlt( hBackBufferDc, 0, 0, m_MapSize.x, m_MapSize.y, m_hBgDc, 0, 0, SRCCOPY );

	// 绘制起点
	if( isSetStart )
	{
		TransparentBlt( hBackBufferDc, (int)(m_StartPoint.x - m_StartPointSize.x/2),
			(int)(m_StartPoint.y - m_StartPointSize.y/2), 
			(int)(m_StartPointSize.x), (int)(m_StartPointSize.y),
			m_hStartPointDc, 0, 0, (int)m_StartPointSize.x, (int)m_StartPointSize.y, 
			RGB( 255, 255, 255 ) );
	}

	// 绘制路径
	if ( m_MonsterMovePath.size() > 0 && 
		 isSetStart && isSetEnd )
	{
		MoveToEx( hBackBufferDc, (int)(m_StartPoint.x), (int)(m_StartPoint.y), NULL );
		for ( m_MonsterMovePathIter = m_MonsterMovePath.begin(); 
			m_MonsterMovePathIter != m_MonsterMovePath.end(); 
			++m_MonsterMovePathIter )
		{
			LineTo( hBackBufferDc, (int)(m_MonsterMovePathIter->x), 
				(int)(m_MonsterMovePathIter->y) );
		}
		LineTo( hBackBufferDc, (int)(m_EndPoint.x), (int)(m_EndPoint.y) );
	}

	// 绘制终点
	if( isSetEnd )
	{
		TransparentBlt( hBackBufferDc, (int)(m_EndPoint.x - m_EndPointSize.x/2),
			(int)(m_EndPoint.y - m_EndPointSize.y/2), 
			(int)(m_EndPointSize.x), (int)(m_EndPointSize.y),
			m_hEndPointDc, 0, 0, (int)(m_EndPointSize.x), (int)(m_EndPointSize.y), 
			RGB( 255, 255, 255 ) );
	}
}

void KingdomRushMap::AddPath( const Vector2D &pt )
{
	m_MonsterMovePath.push_back( pt );
}

void KingdomRushMap::ClearPath()
{
	isSetStart = false;
	isSetEnd = false;
	m_MonsterMovePath.clear();
}

void KingdomRushMap::SetBackgroundImage( char *filename )
{
	if( m_hBgBmp != NULL )
	{
		DeleteObject( m_hBgBmp );
	}
	m_hBgBmp = (HBITMAP)LoadImage( NULL, filename, IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE );
	SelectObject( m_hBgDc, m_hBgBmp );
}

void KingdomRushMap::SetStartPoint( const Vector2D &p )
{
	m_StartPoint = p;
	isSetStart = true;
}

void KingdomRushMap::SetEndPoint( const Vector2D &p )
{
	m_EndPoint = p;
	isSetEnd = true;
}

bool KingdomRushMap::CanSetPath()
{
	return (isSetStart && isSetEnd);
}

bool KingdomRushMap::SaveMapToFile( char *filename )
{
	if( filename == NULL )
	{
		MessageBox( m_hWnd, "文件名不能为空！", "警告",  MB_ICONWARNING | MB_OK );
		return false;
	}

	FILE *fp = fopen( filename, "wb" );
	if ( !fp )
	{
		MessageBox( m_hWnd, "创建文件失败！", "提示",  MB_ICONWARNING | MB_OK );
		return false;
	}
	
	fwrite( &m_StartPoint, sizeof( Vector2D ), 1, fp );
	fwrite( &m_EndPoint, sizeof( Vector2D ), 1, fp );

	int len = (int)m_MonsterMovePath.size();
	fwrite( &len, sizeof(int), 1, fp );
	for ( m_MonsterMovePathIter = m_MonsterMovePath.begin(); 
		m_MonsterMovePathIter != m_MonsterMovePath.end();
		++m_MonsterMovePathIter )
	{
		fwrite( &(*m_MonsterMovePathIter), sizeof( Vector2D ), 1, fp );
	}

	fclose( fp );
	return true;
}

bool KingdomRushMap::OPenMapFromFile( char *filename )
{
	if( filename == NULL )
	{
		MessageBox( m_hWnd, "文件名不能为空！", "警告",  MB_ICONWARNING | MB_OK );
		return false;
	}

	FILE *fp = fopen( filename, "rb" );
	if ( !fp )
	{
		MessageBox( m_hWnd, "打开文件失败！", "提示",  MB_ICONWARNING | MB_OK );
		return false;
	}

	isSetStart = true;
	isSetEnd = true;
	fread( &m_StartPoint, sizeof( Vector2D ), 1, fp );
	fread( &m_EndPoint, sizeof( Vector2D ), 1, fp );

	int pathLen;
	fread( &pathLen, sizeof(int), 1, fp );

	Vector2D pt;
	for ( int i=0; i<pathLen; ++i )
	{
		fread( &pt, sizeof( Vector2D ), 1, fp );
		m_MonsterMovePath.push_back( pt );
	}

	fclose( fp );
	return true;
}

