#include "commonHeader.h"

#ifndef BASETOWER
#define BASETOWER

class iTower
{
public:
	iTower(void) {}

	virtual void attack() = 0;
	virtual void levelUp() = 0;
	virtual void destory() = 0;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual ~iTower(void) {}

protected:
	virtual void _processInput() = 0;

	HWND m_hWnd;
	Sgge *m_pEngine;

	towerState m_TowerState;
	towerBulletState m_TowerBulletState;
};

#endif	// END BASETOWER
