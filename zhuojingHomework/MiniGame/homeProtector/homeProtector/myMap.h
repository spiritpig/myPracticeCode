#ifndef MYMAP
#define MYMAP

class myMap
{
public:
	myMap(void);
	~myMap(void);

	void init();
	void update();
	void render();

private:
	Sgge *m_pSgge;

	PSTEXTURE m_pBGTex;
	SggeSprite *m_pBGSpr;

	PSTEXTURE m_pTowerTex;
	SggeSprite *m_pTowerSpr;
};

#endif	// END MYMAP