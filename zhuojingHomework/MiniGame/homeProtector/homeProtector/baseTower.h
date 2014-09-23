#include "commonHeader.h"

#ifndef BASETOWER
#define BASETOWER

class baseTower
{
public:
	baseTower(void) {}

	virtual void attack() = 0;
	virtual void levelUp() = 0;
	virtual void destory() = 0;

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	virtual ~baseTower(void) {}

protected:
	virtual void _processInput() = 0;

	Sgge *m_pEngine;
	towerState m_TowerState;
};

#endif	// END BASETOWER
