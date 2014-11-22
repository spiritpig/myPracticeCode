#ifndef KINGDOMRUSHMAP
#define KINGDOMRUSHMAP

class KingdomRushMap
{
public:
	KingdomRushMap(void);
	~KingdomRushMap(void);

	void Init( char *filename );
	void Render();
	void SetBackgroundImage( char *filename );

private:
	bool _LoadMapFromFile( char *filename );

	Sgge *m_pEngine;
	PSTEXTURE m_pBgTex;
	SggeSprite *m_pBgSpr;
	POINT m_MapSize;

	// 起点终点相关
	PSTEXTURE m_pStartPointTex;
	SggeSprite *m_pStartPointSpr;
	PSTEXTURE m_pEndPointTex;
	SggeSprite *m_pEndPointSpr;
	bool isSetStart, isSetEnd;
	Vector2D m_StartPoint, m_EndPoint;
	Vector2D m_StartPointSize, m_EndPointSize;

	// 路径相关
	PSTEXTURE m_pMonsterMoveBlockTex;
	SggeSprite *m_pMonsterMoveBlockSpr;
	list<Vector2D> m_MonsterMovePath;
	list<Vector2D>::iterator m_MonsterMovePathIter;
};

#endif	// END KINGDOMRUSHMAP
