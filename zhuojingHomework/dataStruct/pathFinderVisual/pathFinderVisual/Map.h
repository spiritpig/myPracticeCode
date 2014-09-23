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

	~Map(void);
private:
	Sgge *m_pSgge;
private:
	char m_Mapdata[ROW][COL];
	char m_initMapdata[ROW][COL];
	int r,c;
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
private:
	bool isFirstFindPath, 
		 isPathFindFinished,
		 startPathFinding;

	PATH_FINDING_METHOD m_curPFMethod;

	POINT m_StartPoint;
	POINT m_EndPoint;

	dfsPathFinder m_DfsPfMan;
	StackArray<dfsNode,ROW*COL> m_curPath_Dfs;

	bfsPathFinder m_BfsPfMan;
	aStarPathFinder m_AStarPfMan;
	StackArray<POINT,ROW*COL> m_curPath_BfsOrAStar;
	
};

#endif