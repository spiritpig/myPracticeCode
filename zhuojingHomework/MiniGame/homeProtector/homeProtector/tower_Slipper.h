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

	static PSTEXTURE m_TowerTex;
};

#endif	// END TOWER_SLIPPER
