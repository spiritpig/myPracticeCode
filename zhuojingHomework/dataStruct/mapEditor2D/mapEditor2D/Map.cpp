#include "AllDefine.h"

// static void readMapFromFile( char * const mapdata, const char * const filename, HWND hWnd )
// {
// 	int mw,mh;
// 	FILE *fp = fopen( filename, "r");
// 	if ( !fp )
// 	{
// 		MessageBox( hWnd, "读取地图错误：文件无法打开", "错误", 0 );
// 	}
// 
// 	fread( &mw, sizeof(int), 1, fp );
// 	fread( &mh, sizeof(int), 1, fp );
// 	fread( mapdata, sizeof(char), mw*mh, fp );
// 	fclose(fp);
// 
// 	MessageBox( hWnd, "读取地图成功！", "成功", 0 );
// }

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
	char tempmapdata[ROW][COL]	={
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
	m_pEndSpr=new SggeSprite(m_pEnd,0.0f,0.0f,CELL_SIZE,CELL_SIZE);
	m_pEndSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pStartSpr);
	if(m_pStart!=NULL)
	{
		m_pSgge->Texture_Free(m_pStart);
		m_pStart=NULL;
	}
	m_pStart=m_pSgge->Texture_Load("Image\\start.bmp");
	m_pStartSpr=new SggeSprite(m_pStart,0.0f,0.0f,CELL_SIZE,CELL_SIZE);
	m_pStartSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pPathSpr);
	if(m_pPath!=NULL)
	{
		m_pSgge->Texture_Free(m_pPath);
		m_pPath=NULL;
	}
	m_pPath=m_pSgge->Texture_Load("Image\\path.bmp");
	m_pPathSpr=new SggeSprite(m_pPath,0.0f,0.0f,CELL_SIZE,CELL_SIZE);
	m_pPathSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pWalkedSpr);
	if(m_pWalked!=NULL)
	{
		m_pSgge->Texture_Free(m_pWalked);
		m_pWalked=NULL;
	}
	m_pWalked=m_pSgge->Texture_Load("Image\\walked.bmp");
	m_pWalkedSpr=new SggeSprite(m_pWalked,0.0f,0.0f,CELL_SIZE,CELL_SIZE);
	m_pWalkedSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pWalkingSpr);
	if(m_pWalking!=NULL)
	{
		m_pSgge->Texture_Free(m_pWalking);
		m_pWalking=NULL;
	}
	m_pWalking=m_pSgge->Texture_Load("Image\\walking.bmp");
	m_pWalkingSpr=new SggeSprite(m_pWalking,0.0f,0.0f,CELL_SIZE,CELL_SIZE);
	m_pWalkingSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pNoWalkSpr);
	if(m_pNoWalk!=NULL)
	{
		m_pSgge->Texture_Free(m_pNoWalk);
		m_pNoWalk=NULL;
	}
	m_pNoWalk=m_pSgge->Texture_Load("Image\\nowalk.bmp");
	m_pNoWalkSpr=new SggeSprite(m_pNoWalk,0.0f,0.0f,CELL_SIZE,CELL_SIZE);
	m_pNoWalkSpr->SetHotSpot(20.0f,20.0f);

	SAFE_DELETE(m_pCanWalkSpr);
	if(m_pCanWalk!=NULL)
	{
		m_pSgge->Texture_Free(m_pCanWalk);
		m_pCanWalk=NULL;
	}
	m_pCanWalk=m_pSgge->Texture_Load("Image\\canwalk.bmp");
	m_pCanWalkSpr=new SggeSprite(m_pCanWalk,0.0f,0.0f,CELL_SIZE,CELL_SIZE);
	m_pCanWalkSpr->SetHotSpot(20.0f,20.0f);

	m_StartPoint.x=STARTPOS.x;
	m_StartPoint.y=STARTPOS.y;

	m_EndPoint.x=ENDPOS.x;
	m_EndPoint.y=ENDPOS.y;

	isPathDisplay = false;
	isFirstFindPath = true;
	isPathFindFinished = false;
	startPathFinding = false;

	m_MapHeight = ROW;
	m_MapWidth = COL;

	m_curEditState = ES_SPACE;
	m_curPFMethod = DEPTH_FIRST_SEARCH;
	m_curPath_Dfs.reserve(m_MapHeight*m_MapWidth);
	m_PathData.reserve(m_MapHeight*m_MapWidth);

	m_Hwnd = GetActiveWindow();
}

void Map::Update()
{
	// 路径搜索开始
	if( startPathFinding )
	{
		switch( m_curPFMethod )
		{
		case DEPTH_FIRST_SEARCH:
			{
				memcpy(m_Mapdata,m_initMapdata,sizeof(m_Mapdata));
				m_DfsPfMan.findPath( m_Mapdata, m_StartPoint.x, m_StartPoint.y,
					m_EndPoint.x, m_EndPoint.y, m_curPath_Dfs );
				startPathFinding = false;

				int index = m_curPath_Dfs.size()-1;
				while( index > -1 )
				{
					m_Mapdata[m_curPath_Dfs[index].pos.y][m_curPath_Dfs[index].pos.x] = PATH;
					--index;
				}
			}
			break;

		case BREADTH_FIRST_SEARCH:
			{
				memcpy(m_Mapdata,m_initMapdata,sizeof(m_Mapdata));
				m_BfsPfMan.findPath( m_Mapdata, m_StartPoint.x, m_StartPoint.y,
					m_EndPoint.x, m_EndPoint.y, m_curPath_BfsOrAStar  );
				startPathFinding = false;

				int index = m_curPath_BfsOrAStar.Size()-1;
				while( index > -1 )
				{
					m_Mapdata[m_curPath_BfsOrAStar[index].y][m_curPath_BfsOrAStar[index].x] = PATH;
					--index;
				}
			}
			break;

		case ASTAR:
			{
				memcpy(m_Mapdata,m_initMapdata,sizeof(m_Mapdata));
				m_AStarPfMan.findPath( m_Mapdata, m_StartPoint.x, m_StartPoint.y,
					m_EndPoint.x, m_EndPoint.y, m_curPath_BfsOrAStar  );
				startPathFinding = false;

				int index = m_curPath_BfsOrAStar.Size()-1;
				while( index > -1 )
				{
					m_Mapdata[m_curPath_BfsOrAStar[index].y][m_curPath_BfsOrAStar[index].x] = PATH;
					--index;
				}
			}
			break;
		}
 		
	}
}

void Map::Render()
{
	static float offsetX=20.0f;
	static float offsetY=20.0f;

	for (r=0;r<m_MapHeight;++r)
	{
		for (c=0;c<m_MapWidth;++c)
		{
			switch(m_Mapdata[r][c])
			{
			case SPACE:
				{
					m_pCanWalkSpr->Render(offsetX+c*CELL_SIZE,offsetY+r*CELL_SIZE);
				}
				break;
			case NOWALK:
				{
					m_pNoWalkSpr->Render(offsetX+c*CELL_SIZE,offsetY+r*CELL_SIZE);
				}
				break;
			case WALKING:
				{
					m_pWalkingSpr->Render(offsetX+c*CELL_SIZE,offsetY+r*CELL_SIZE);
				}
				break;
			case WALKED:
				{
					m_pWalkedSpr->Render(offsetX+c*CELL_SIZE,offsetY+r*CELL_SIZE);
				}
				break;
			case PATH:
				{
					m_pPathSpr->Render(offsetX+c*CELL_SIZE,offsetY+r*CELL_SIZE);
				}
				break;
			}
		}
	}

	m_pStartSpr->Render(offsetX+m_StartPoint.x*CELL_SIZE,offsetY+m_StartPoint.y*CELL_SIZE);
	m_pEndSpr->Render(offsetX+m_EndPoint.x*CELL_SIZE,offsetY+m_EndPoint.y*CELL_SIZE);
}

void Map::saveMap( char *filename )
{
	if ( !isPathDisplay )
	{
		FILE *fp = fopen( filename, "w");
		if ( !fp )
		{
			MessageBox( m_Hwnd, "保存地图错误：文件无法创建", "错误", 0 );
		}

		fwrite( &m_MapWidth, sizeof(int), 1, fp );
		fwrite( &m_MapHeight, sizeof(int), 1, fp );
		fwrite( m_initMapdata, sizeof(char), m_MapHeight*m_MapWidth, fp );
		fwrite( &m_PathData[0], sizeof(POINT), m_PathData.size(), fp );

		fclose(fp);

		MessageBox( m_Hwnd, "保存地图成功！", "成功", 0 );
	}
	else
	{
		MessageBox( m_Hwnd, "正在显示路径，无法保存！", "错误", 0 );
	}
}

void Map::changeBlockAttribute( POINT pos )
{
	if ( pos.x < 0 || 
		 pos.x > m_MapWidth*CELL_SIZE ||
		 pos.y < 0 || 
		 pos.y > m_MapHeight*CELL_SIZE )
	{
		return;
	}

	if ( !isPathDisplay )
	{
		pos.x /= (long)CELL_SIZE;
		pos.y /= (long)CELL_SIZE;
		switch( m_curEditState )
		{
		case ES_SPACE:
			{
				m_Mapdata[pos.y][pos.x] = SPACE;
				m_initMapdata[pos.y][pos.x] = SPACE;
			}
			break;

		case ES_WALL:
			{
				m_Mapdata[pos.y][pos.x] = NOWALK;
				m_initMapdata[pos.y][pos.x] = NOWALK;
			}
			break;

		case ES_START:
			{
				m_StartPoint.x = pos.x;
				m_StartPoint.y = pos.y;
				m_Mapdata[pos.y][pos.x] = SPACE;
				m_initMapdata[pos.y][pos.x] = SPACE;
			}
			break;

		case ES_END:
			{
				m_EndPoint.x = pos.x;
				m_EndPoint.y = pos.y;
				m_Mapdata[pos.y][pos.x] = SPACE;
				m_initMapdata[pos.y][pos.x] = SPACE;
			}
			break;
		}
	}
	else
	{
		MessageBox( m_Hwnd, "正在显示路径，无法改变格子属性！", "错误", 0 );
	}
}
