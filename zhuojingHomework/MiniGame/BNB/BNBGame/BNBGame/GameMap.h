#ifndef GAMEMAP
#define GAMEMAP

class GameMap
{
public:
	GameMap(void);
	~GameMap(void);

	void Init();
	void Update();
	void RenderBack();
	void RenderMid();
	void RenderTop();

	bool IsHitZhangAiWu( int row, int cel );
	void SetBackMap( int row, int cel, BLOCK_KIND bk );
	void SetMidAndTopMap( int row, int cel, BLOCK_KIND bk );
	void ClearMap();

	void SaveMapToFile( char *filename );
	void LoadMapFromFile( char *filename );

private:
	void _SetCurElemRect( char block );

	Sgge *m_pEngine;

	PSTEXTURE m_pBGTex;
	SggeSprite *m_pBGSpr;
	PSTEXTURE m_pBlockElementTex;
	SggeSprite *m_pBlockElementSpr;

	int m_Row, m_Cel;
	char m_pBackMapData[MAP_MAX_ROW][MAP_MAX_CEL];
	char m_pMidMapData[MAP_MAX_ROW][MAP_MAX_CEL];
	char m_pTopMapData[MAP_MAX_ROW][MAP_MAX_CEL];
};

#endif	// END GAMEMAP
