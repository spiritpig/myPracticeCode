#include "commonHeader.h"

#ifndef TOWER_SLIPPER
#define TOWER_SLIPPER

class tower_Slipper : public baseTower
{
public:
	tower_Slipper(void);
	virtual ~tower_Slipper(void);

	virtual void attack();
	virtual void levelUp();
	virtual void destory();

	virtual void init();
	virtual void update();
	virtual void render();

private:
	virtual void _processInput();
	bool _isBulletValid( const vector2 &v2 );

	HWND m_hWnd;

	towerState m_TowerState;
	towerBulletState m_TowerBulletState;

	static PSTEXTURE m_pTowerBulletTex;
	static size_t m_BulletTexUseCount;
	SggeSprite *m_pTowerBulletSpr;

	static PSTEXTURE m_pTowerTex;
	static size_t m_TexUseCount;
	SggeSprite *m_pTowerSpr;
};

#endif	// END TOWER_SLIPPER
