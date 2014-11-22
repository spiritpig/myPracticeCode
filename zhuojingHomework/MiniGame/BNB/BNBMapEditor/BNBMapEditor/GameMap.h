#ifndef GAMEMAP
#define GAMEMAP

class GameMap
{
public:
	GameMap( HDC hBackBuffer );
	~GameMap(void);

	void RenderBG();
	void RenderBack();
	void RenderMidAndTop();

	void SetBackMap( int row, int cel, BLOCK_KIND bk );
	void SetMidAndTopMap( int row, int cel, BLOCK_KIND bk );
	void ClearMidAndTopMap( int row, int cel );
	void ClearMap();

	void SaveMapToFile( char *filename );
	void LoadMapFromFile( char *filename );

private:
	HDC m_hBackBuffer;

	HDC m_hBGDc;
	HBITMAP m_hBGBmp;
	HDC m_hBlockElementDc;
	HBITMAP m_hBlockElementBmp;

	int m_Row, m_Cel;
	COLORREF m_MaskColor;
	char **m_pBackMapData;
	char **m_pMidMapData;
	char **m_pTopMapData;
};

#endif	// END GAMEMAP
