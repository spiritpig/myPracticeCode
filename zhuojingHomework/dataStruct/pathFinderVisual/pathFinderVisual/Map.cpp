#include ".\map.h"

Map::Map(void)
{
	m_pSgge=SggeCreate(SGGE_VERSION);
	memset(m_Mapdata,0,sizeof(m_Mapdata));

	m_pCanWalk=NULL;
	m_pCanWalkSpr=NULL;

	m_pNoWalk=NULL;
	m_pNoWalkSpr=NULL;

	m_pWalking=NULL;
	m_pWalkingSpr=NULL;

	m_pWalked=NULL;
	m_pWalkedSpr=NULL;

	m_pPath= NULL;
	m_pPathSpr= NULL;

	m_pStart=NULL;
	m_pStartSpr=NULL;

	m_pEnd=NULL;
	m_pEndSpr=NULL;
}

Map::~Map(void)
{
	SAFE_DELETE(m_pEndSpr);
	if(m_pEnd!=NULL)
	{
		m_pSgge->Texture_Free(m_pEnd);
		m_pEnd=NULL;
	}
	SAFE_DELETE(m_pStartSpr);
	if(m_pStart!=NULL)
	{
		m_pSgge->Texture_Free(m_pStart);
		m_pStart=NULL;
	}
	SAFE_DELETE(m_pPathSpr);
	if(m_pPath!=NULL)
	{
		m_pSgge->Texture_Free(m_pPath);
		m_pPath=NULL;
	}
	SAFE_DELETE(m_pWalkedSpr);
	if(m_pWalked!=NULL)
	{
		m_pSgge->Texture_Free(m_pWalked);
		m_pWalked=NULL;
	}
	SAFE_DELETE(m_pWalkingSpr);
	if(m_pWalking!=NULL)
	{
		m_pSgge->Texture_Free(m_pWalking);
		m_pWalking=NULL;
	}
	SAFE_DELETE(m_pNoWalkSpr);
	if(m_pNoWalk!=NULL)
	{
		m_pSgge->Texture_Free(m_pNoWalk);
		m_pNoWalk=NULL;
	}
	SAFE_DELETE(m_pCanWalkSpr);
	if(m_pCanWalk!=NULL)
	{
		m_pSgge->Texture_Free(m_pCanWalk);
		m_pCanWalk=NULL;
	}
	m_pSgge->Release();
}

void Map::Init()
{
	char tempmapdata[ROW][COL]={
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,1,1,1,1,1,1,0 },
		{ 0,1,0,0,0,0,0,0,1,0 },
		{ 0,1,1,0,0,0,0,0,1,0 },
		{ 0,1,0,1,1,1,1,1,1,0 },
		{ 0,1,0,1,0,0,1,1,1,0 },
		{ 0,1,0,1,1,1,0,0,1,0 },
		{ 0,1,0,0,0,0,0,0,1,0 },
		{ 0,1,1,1,0,1,1,0,1,1 },
		{ 1,0,0,0,0,0,1,0,0,0 }
	};

	memcpy(m_Mapdata,tempmapdata,sizeof(m_Mapdata));
	memcpy(m_initMapdata,tempmapdata,sizeof(m_initMapdata));

	SAFE_DELETE(m_pEndSpr);
	if(m_pEnd!=NULL)
	{
		m_pSgge->Texture_Free(m_pEnd);
		m_pEnd=NULL;
	}
	m_pEnd=m_pSgge->Texture_Load("Image\\end.bmp");
	m_pEndSpr=new SggeSprite(m_pEnd,0.0f,0.0f,40.0f,40.0f);
	m_pEndSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pStartSpr);
	if(m_pStart!=NULL)
	{
		m_pSgge->Texture_Free(m_pStart);
		m_pStart=NULL;
	}
	m_pStart=m_pSgge->Texture_Load("Image\\start.bmp");
	m_pStartSpr=new SggeSprite(m_pStart,0.0f,0.0f,40.0f,40.0f);
	m_pStartSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pPathSpr);
	if(m_pPath!=NULL)
	{
		m_pSgge->Texture_Free(m_pPath);
		m_pPath=NULL;
	}
	m_pPath=m_pSgge->Texture_Load("Image\\path.bmp");
	m_pPathSpr=new SggeSprite(m_pPath,0.0f,0.0f,40.0f,40.0f);
	m_pPathSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pWalkedSpr);
	if(m_pWalked!=NULL)
	{
		m_pSgge->Texture_Free(m_pWalked);
		m_pWalked=NULL;
	}
	m_pWalked=m_pSgge->Texture_Load("Image\\walked.bmp");
	m_pWalkedSpr=new SggeSprite(m_pWalked,0.0f,0.0f,40.0f,40.0f);
	m_pWalkedSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pWalkingSpr);
	if(m_pWalking!=NULL)
	{
		m_pSgge->Texture_Free(m_pWalking);
		m_pWalking=NULL;
	}
	m_pWalking=m_pSgge->Texture_Load("Image\\walking.bmp");
	m_pWalkingSpr=new SggeSprite(m_pWalking,0.0f,0.0f,40.0f,40.0f);
	m_pWalkingSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pNoWalkSpr);
	if(m_pNoWalk!=NULL)
	{
		m_pSgge->Texture_Free(m_pNoWalk);
		m_pNoWalk=NULL;
	}
	m_pNoWalk=m_pSgge->Texture_Load("Image\\nowalk.bmp");
	m_pNoWalkSpr=new SggeSprite(m_pNoWalk,0.0f,0.0f,40.0f,40.0f);
	m_pNoWalkSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pCanWalkSpr);
	if(m_pCanWalk!=NULL)
	{
		m_pSgge->Texture_Free(m_pCanWalk);
		m_pCanWalk=NULL;
	}
	m_pCanWalk=m_pSgge->Texture_Load("Image\\canwalk.bmp");
	m_pCanWalkSpr=new SggeSprite(m_pCanWalk,0.0f,0.0f,40.0f,40.0f);
	m_pCanWalkSpr->SetHotSpot(20.0f,20.0f);

	m_StartPoint.x=0;
	m_StartPoint.y=0;

	m_EndPoint.x=9;
	m_EndPoint.y=9;

	isFirstFindPath = true;
	isPathFindFinished = false;
	startPathFinding = false;

	m_curPFMethod = DEPTH_FIRST_SEARCH;
}

void Map::Update()
{
	if( startPathFinding )
	{
		switch( m_curPFMethod )
		{
		case DEPTH_FIRST_SEARCH:
			{
				if( isFirstFindPath  )
				{
					memcpy(m_Mapdata,m_initMapdata,sizeof(m_Mapdata));
					// 事先找到路径
					m_DfsPfMan.findPath( m_Mapdata, m_StartPoint.x, m_StartPoint.y,
						m_EndPoint.x, m_EndPoint.y, m_curPath_Dfs );

					isPathFindFinished = m_DfsPfMan.findPathOneStep( m_Mapdata, 
						m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y, true );

					isFirstFindPath = false;
				}
				else
				{
					if( !isPathFindFinished )
					{
						Sleep( 100 );
						isPathFindFinished = m_DfsPfMan.findPathOneStep( m_Mapdata, 
							m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y );
					}
					else
					{
						static dfsNode node;
						while ( !m_curPath_Dfs.Empty() )
						{
							m_curPath_Dfs.Pop( node );
							m_Mapdata[node.pos.y][node.pos.x] = PATH;
						}

						isFirstFindPath = true;
						isPathFindFinished = false;
						startPathFinding = false;
					}
				}
			}
			break;

		case BREADTH_FIRST_SEARCH:
			{
				if( isFirstFindPath  )
				{
					memcpy(m_Mapdata,m_initMapdata,sizeof(m_Mapdata));
					// 事先找到路径
					m_BfsPfMan.findPath( m_Mapdata, m_StartPoint.x, m_StartPoint.y,
						m_EndPoint.x, m_EndPoint.y, m_curPath_BfsOrAStar  );

					isPathFindFinished = m_BfsPfMan.findPathOneStep( m_Mapdata, 
						m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y, true );

					isFirstFindPath = false;
				}
				else
				{
					if( !isPathFindFinished )
					{
						Sleep( 100 );
						isPathFindFinished = m_BfsPfMan.findPathOneStep( m_Mapdata, 
							m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y );
					}
					else
					{
						static POINT node;
						while ( !m_curPath_BfsOrAStar.Empty() )
						{
							m_curPath_BfsOrAStar.Pop( node );
							m_Mapdata[node.y][node.x] = PATH;
						}

						isFirstFindPath = true;
						isPathFindFinished = false;
						startPathFinding = false;
					}
				}
			}
			break;

		case ASTAR:
			{
				Sleep( 100 );
				if( isFirstFindPath  )
				{
					memcpy(m_Mapdata,m_initMapdata,sizeof(m_Mapdata));
					// 事先找到路径
					m_AStarPfMan.findPath( m_Mapdata, m_StartPoint.x, m_StartPoint.y,
						m_EndPoint.x, m_EndPoint.y, m_curPath_BfsOrAStar  );

					isPathFindFinished = m_AStarPfMan.findPathOneStep( m_Mapdata, 
						m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y, true );

					isFirstFindPath = false;
				}
				else
				{
					if( !isPathFindFinished )
					{
						Sleep( 100 );
						isPathFindFinished = m_AStarPfMan.findPathOneStep( m_Mapdata, 
							m_StartPoint.x, m_StartPoint.y, m_EndPoint.x, m_EndPoint.y );
					}
					else
					{
						static POINT node;
						while ( !m_curPath_BfsOrAStar.Empty() )
						{
							m_curPath_BfsOrAStar.Pop( node );
							m_Mapdata[node.y][node.x] = PATH;
						}

						isFirstFindPath = true;
						isPathFindFinished = false;
						startPathFinding = false;
					}
				}
			}
			break;
		}
 		
	}
}

void Map::Render()
{
	static float offsetX=220.0f;
	static float offsetY=120.0f;

	for (r=0;r<ROW;++r)
	{
		for (c=0;c<COL;++c)
		{
			switch(m_Mapdata[r][c])
			{
			case SPACE:
				{
					m_pCanWalkSpr->Render(offsetX+c*40.0f,offsetY+r*40.0f);
				}
				break;
			case NOWALK:
				{
					m_pNoWalkSpr->Render(offsetX+c*40.0f,offsetY+r*40.0f);
				}
				break;
			case WALKING:
				{
					m_pWalkingSpr->Render(offsetX+c*40.0f,offsetY+r*40.0f);
				}
				break;
			case WALKED:
				{
					m_pWalkedSpr->Render(offsetX+c*40.0f,offsetY+r*40.0f);
				}
				break;
			case PATH:
				{
					m_pPathSpr->Render(offsetX+c*40.0f,offsetY+r*40.0f);
				}
				break;
			}
		}
	}

	m_pStartSpr->Render(offsetX+m_StartPoint.x*40.0f,offsetY+m_StartPoint.y*40.0f);
	m_pEndSpr->Render(offsetX+m_EndPoint.x*40.0f,offsetY+m_EndPoint.y*40.0f);
}
