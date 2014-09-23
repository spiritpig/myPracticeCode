#include "commonHeader.h"

#ifndef MYMAP_AFX
#define MYMAP_AFX

class myMap
{
public:
	myMap();
	~myMap();

	void init();
	void update();
	void render();

	float getMapLen();

private:
	void _processInput();

private:
	Sgge *m_pSgge;
	PSTEXTURE m_pMapBackTextrue;
	SggeSprite *m_pMapBackSpr;

	vector2d m_bgPos1;
	vector2d m_bgPos2;
	float m_mapLen;
};

#endif // END MYMAP_AFX