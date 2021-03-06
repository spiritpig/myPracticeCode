#include "AllDefine.h"

#ifndef AFX_MAP
#define AFX_MAP

class Map
{
public:
	Map(void);
	void Init();
	void Update();
	void Render();
	void changeBlockAttribute( POINT pos );
	void saveMap( char *filename );

	void turnOnPathDisplay()
	{
		isPathDisplay = true;
	}

	void turnOffPathDisplay()
	{
		isPathDisplay = false;
		memcpy(m_Mapdata,m_initMapdata,sizeof(m_Mapdata));
	}

	void setStartPathFinding( bool flag )
	{
		if( !startPathFinding )
		{
			startPathFinding = flag;
		}
	}

	void setCurPathFindingMethod( PATH_FINDING_METHOD pfm )
	{
		if ( !startPathFinding )
		{
			m_curPFMethod = pfm;
		}
	}

	void setEditState( EDIT_STATE es )
	{
		m_curEditState = es;
	}


	~Map(void);

//////////////////////////////////////////////////////////////////////////
//
//	渲染相关部分
//
//////////////////////////////////////////////////////////////////////////
private:
	HWND m_Hwnd;
	Sgge *m_pSgge;

	PSTEXTURE m_pCanWalk;
	SggeSprite *m_pCanWalkSpr;

	PSTEXTURE m_pNoWalk;
	SggeSprite *m_pNoWalkSpr;

	PSTEXTURE m_pWalking;
	SggeSprite *m_pWalkingSpr;

	PSTEXTURE m_pWalked;
	SggeSprite *m_pWalkedSpr;

	PSTEXTURE m_pPath;
	SggeSprite *m_pPathSpr;

	PSTEXTURE m_pStart;
	SggeSprite *m_pStartSpr;

	PSTEXTURE m_pEnd;
	SggeSprite *m_pEndSpr;

//////////////////////////////////////////////////////////////////////////
//
// 数据相关部分
//
//////////////////////////////////////////////////////////////////////////
private:
	char m_Mapdata[ROW][COL];
	char m_initMapdata[ROW][COL];
	int m_MapHeight, m_MapWidth;
	// 遍历地图所需的循环变量
	int r,c;

	bool isPathDisplay,
		 isFirstFindPath, 
		 isPathFindFinished,
		 startPathFinding;


	EDIT_STATE m_curEditState;
	PATH_FINDING_METHOD m_curPFMethod;

	POINT m_StartPoint;
	POINT m_EndPoint;

	dfsPathFinder m_DfsPfMan;
	vector<dfsNode> m_curPath_Dfs;

	bfsPathFinder m_BfsPfMan;
	aStarPathFinder m_AStarPfMan;
	StackArray<POINT,ROW*COL> m_curPath_BfsOrAStar;

	vector<POINT> m_PathData;
};

#endif