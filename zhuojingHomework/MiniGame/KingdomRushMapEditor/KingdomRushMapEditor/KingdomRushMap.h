#include <list>
using std::list;

#pragma once

class KingdomRushMap
{
public:
	KingdomRushMap(void);
	~KingdomRushMap(void);

	void Init( HDC hInputBackBufferDc, HWND hWnd );
	void Render();
	void AddPath(const Vector2D &pt);
	void ClearPath();
	void SetBackgroundImage( char *filename );
	void SetStartPoint( const Vector2D &p );
	void SetEndPoint( const Vector2D &p );
	// 只有设置了起点和终点以后，才能设置路径
	bool CanSetPath();

	bool SaveMapToFile( char *filename );
	bool OPenMapFromFile( char *filename );

private:
	HWND m_hWnd;
	HPEN m_hPen;
	HDC m_hBgDc;
	HBITMAP m_hBgBmp;
	POINT m_MapSize;


	// 起点终点相关
	HDC m_hStartPointDc;
	HBITMAP m_hStartPointBmp;
	HDC m_hEndPointDc;
	HBITMAP m_hEndPointBmp;
	bool isSetStart, isSetEnd;
	Vector2D m_StartPoint, m_EndPoint;
	Vector2D m_StartPointSize, m_EndPointSize;

	// 路径相关
	HDC m_hMonsterMoveBlockDc;
	HBITMAP m_hMonsterMoveBlockBmp;
	list<Vector2D> m_MonsterMovePath;
	list<Vector2D>::iterator m_MonsterMovePathIter;
};
